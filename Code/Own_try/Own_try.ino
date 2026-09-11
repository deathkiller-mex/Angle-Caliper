#include <Wire.h>
#include <AS5600.h>     // Install the "AS5600 by Rob Tillaart" library
#include <U8g2lib.h>    // Install the "U8g2" graphics library

// Start the LCD screen
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// Start the AS5600 sensor
AS5600 as5600;


void setup() {

  //Power everything

  Wire.begin(D4, D5);
  u8g2.begin();
  as5600.begin();

  //Read Battery Level
  Serial.begin(115200);
  pinMode(A0, INPUT); // Set battery pin as input

}

void loop() {

//Get battery level
  uint32_t Vbat = 0;
  for(int i = 0; i < 16; i++) {
  Vbat = Vbat + analogReadMilliVolts(A0);
  }

// Calculation for battery percentage

const float Vo = 3000;
const float Vt = 4200;

float batper = (Vbat-Vo)/(Vt-Vo)*100;

// Calculations to get the DEG measurements
  float rawAngle = as5600.readAngle();
  float Deg = (rawAngle/4096.0)*360;
  float Rad = (Deg*PI)/180;

//clears the memory ("blank canvas")
  u8g2.clearBuffer();  

  //Deg
  u8g2.setFont(u8g2_font_ncenB14_tr); 
  u8g2.setCursor(0,15);
  u8g2.print(Deg,5);
  u8g2.print(" \xB0");     // The hex code for a deg

  //RAD
  u8g2.setFont(u8g2_font_ncenB08_tr); 
  u8g2.setCursor(0, 31);
  u8g2.print(Rad, 5);  // Print radians with 2 decimal places
  u8g2.print(" rad"); //rad "symbol"

  //Show battery level
  u8g2.setFont(u8g2_font_ncenB08_tr); 
  u8g2.setCursor(120,31 );
  u8g2.print(batper);
  

  
// Push to screen

  u8g2.sendBuffer();           
  delay(100);  


}