#include <Wire.h>
#include <AS5600.h>     // You will need to install the "AS5600 by Rob Tillaart" library
#include <U8g2lib.h>    // You will need to install the "U8g2" graphics library

// Initialize the 0.91" 128x32 OLED screen
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// Initialize the AS5600 sensor
AS5600 as5600;

void setup() {
  // Start the I2C bus on the XIAO ESP32-C3 default pins (SDA = D4, SCL = D5)
  Wire.begin(D4, D5);

  // Power up the screen
  u8g2.begin();

  // Power up the sensor
  as5600.begin(); 
}

void loop() {
  // 1. Read the Sensor
  // The AS5600 outputs a digital number between 0 and 4095 (12-bit sensor)
  float rawAngle = as5600.readAngle();

  // 2. Do the Math
  // Convert 0-4095 range into 0-360 degrees
  float degrees = (rawAngle / 4096.0) * 360.0;
  
  // Convert degrees to radians (degrees * Pi / 180)
  float radians = degrees * (PI / 180.0);

  // 3. Update the OLED Screen
  u8g2.clearBuffer(); // Clear the screen's memory before drawing

  // Draw Degrees (Large Font)
  u8g2.setFont(u8g2_font_ncenB14_tr); 
  u8g2.setCursor(0, 15);
  u8g2.print(degrees, 1);  // Print degrees with 1 decimal place
  u8g2.print(" \xB0");     // The hex code for a degree symbol in U8g2

  // Draw Radians (Smaller Font) underneath
  u8g2.setFont(u8g2_font_ncenB08_tr); 
  u8g2.setCursor(0, 31);
  u8g2.print(radians, 2);  // Print radians with 2 decimal places
  u8g2.print(" rad");

  u8g2.sendBuffer(); // Push the drawn memory to the physical screen

  // Wait a tiny bit before taking the next reading to prevent screen flickering
  delay(100); 
}