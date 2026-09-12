# Angle-Caliper
Angle Caliper

# CAD

Go into the CAD folder to download whatever files u need (.step, .stl, .f3z) for the case and parts needed for the caliper: 
* Main case top: 
<img width="247" height="313" alt="top cover up" src="https://github.com/user-attachments/assets/58f769b3-c59a-4bde-b86c-d21afad06efa" />



* Main case bottom cover: 
<img width="398" height="326" alt="bottom cover" src="https://github.com/user-attachments/assets/22f5c379-b0d1-44a8-8165-c21e458e269e" />


* Lid: 
<img width="229" height="177" alt="lid" src="https://github.com/user-attachments/assets/b7edf869-6bfc-460b-a0f9-8cbb16a117e0" />



* Magnet cover: 
<img width="302" height="185" alt="magnet cover" src="https://github.com/user-attachments/assets/286c6fa0-1cfa-43ab-aaa2-45d91c69d166" />



* Finished Assembly:
<img width="484" height="328" alt="whole assmbly 2" src="https://github.com/user-attachments/assets/b2b7c8f6-95ba-4796-a045-b890d95acebe" />
<img width="485" height="263" alt="whole assembly" src="https://github.com/user-attachments/assets/46d7c35d-a040-4dd5-b5dd-7b2a8193b61e" />




# Schematic

This is the wiring diagram to follow: make sure everything is wired exactly like this and\or if u change something like a pin, REMEMBER TO CHANGE THE CODE TOO!!
<img width="400" height="248" alt="shematic" src="https://github.com/user-attachments/assets/943deebc-d049-4519-b631-bcd7059a1965" />


# Assembly

Follow this vid on how to assemble the caliper and where each component goes.
https://github.com/user-attachments/assets/a8357a40-0c6c-4dcd-b7e9-901ac03b5d02




# Code

* Libraries used
  - Wire: https://docs.arduino.cc/language-reference/en/functions/communication/wire/
  - u8g2: https://github.com/olikraus/u8g2
  - AS5600: https://github.com/RobTillaart/AS5600/blob/master/AS5600.h
 
* For the code, you'll need the Arduino IDE and follow these steps.

1. Either download the caliper_code.io file from the code folder or copy the following code into the Arduino IDE

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
3. Now u can either verify the code or just upload.
4. Once it finishes uploading u can disconnect the XIAO from the laptop.
5. Now to verify everything works properly: 
    - The screen should be on, displaying the DEG, RAD, and Battery levels.
    - The Angles displayed should change as u move the magnet around the chip (AS5600). NOTE: The angle readings will not be accurate till the top case is placed since the magnet must be perfectly centered around the AS5600 chip.
6. If everything works u can finish it up, screw the lid, and place the top cover.
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
