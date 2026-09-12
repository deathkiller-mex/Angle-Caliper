# Angle-Caliper
Angle Caliper

# CAD

Go into the CAD folder to download the whathever files u need (.step, .stl, .f3z) for the case and parts needed for the caliper: 
* Main case top: 
![alt text](<top cover up.png>) ![alt text](<top cover down.png>)


* Main case bottom cover: 
![alt text](<bottom cover down.png>) ![alt text](<bottom cover.png>)


* Lid: 
![alt text](lid.png)


* Magnet cover: 
![alt text](<magnet cover.png>)

* Finished Assembly:
![alt text](<whole assmbly 2.png>) ![alt text](<bottom cover assembled down.png>) ![alt text](<bottom cover assembled up.png>) ![alt text](<whole assembly.png>)


# Shematic

This is the wiring diagram to follow: make sure everything is wired exactly like this and\or if u change something like a pin, REMEMBER TO CHANGE THE CODE TOO!!
![alt text](shematic.png)

# Assembly

Follow this vid on how to assemble the caliper and where each component goes.
<video controls src="angle caliper v12.avi" title="Title"></video>

# Code
 
* For the code you'll need Arduino IDE and follow this steps.

1. Either download the caliper_code.io file from the code folder or, copy the following code into Arduino IDE

// Start of code: 
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
// End of code.

2. Choose the XIAO-C3 board
3. Now u can either verify the code or just uploud.
4. Once it finishes uploading u can disconnect the XIAO from the laptop.
5. Now to verify everything works properly: 
    - The screen should be on displaying the DEG, RAD, and Battery levels.
    - The Angles displayed should change as u move the magnet around the chip (AS5600). NOTE: The angle readings will not be accurate till the top case is placed since the magnet must be perfectly centered around the AS5600 chip.
6. If everything works u can finish it up and screw the lid and place the top cover.
7. And that's it!! Enjoy ur compact angle caliper.

# BOM

|Part|Amount|Cost|Link|
|:--:|:----:|:--:|:--:|
|AS5600|1|$0.00|Aliexpress|
|Lipo 3.7V 4000mAh|1|$0.00|Aliexpress|
|XIAO|1|$0.00|Aliexpress|
|Threads|1|$0.00|Aliexpress|
|Screws|1|$0.00|Aliexpress|
|Total|1|$0.00|Aliexpress|