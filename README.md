# Angle-Caliper
I got this idea because when 3D designing different parts, they often have angles, and these are often hard to accurately replicate, and the market angle finders are too big for small parts.
![image.png](https://cdn.hackclub.com/01a0637a-a47c-7141-a5c6-4cd5a03e4590/image.png)
![image.png](https://cdn.hackclub.com/01a0637a-de55-7341-9a75-3a09ccc14c0a/image.png)
![image.png](https://cdn.hackclub.com/01a0637b-0821-7ff6-a93b-1bb18854db6d/image.png)
These are just some online examples, and all of them have the same issue: they are way too big, and some (the last example) find angles based on Earth instead of on the part. 
So after using a digital caliper for almost 1-2 years and finding it incredibly useful and even indispensable, I've decided to take its digital and convenience factor but to find angles. 
So this is what I did. 
* To measure the angles, I choose and AS5600 due to its precision and small build.
* For the main brain, I chose the XIAO. I chose this brain since it has a built-in charger module as well as a power regulator to operate safely. Tho components to do this job could've been added, keeping it all in one component made the build more compact, which is the end goal.

For now, I've given the build some small arms for testing, but for the future I might add interchangeable removable arms to adapt to the situation and need. 


# CAD

Go into the CAD folder to download all the files needed to build the caliper (.step, .stl, or .f3z) for the case and parts needed for the caliper: 
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
    - The Angles displayed should change as u move the magnet around the chip (AS5600). NOTE: The angle readings will not be accurate till the top case is placed, since the magnet must be perfectly centered around the AS5600 chip.
6. If everything works u can finish it up, screw the lid, and place the top cover.
7. And that's it!! Enjoy ur compact angle caliper.

# BOM

|Part|Amount|Cost|Link|
|:--:|:----:|:--:|:--:|
|AS5600|1|$1.77|[Aliexpress](https://www.aliexpress.com/item/3256808447376776.html?spm=a2g0o.cart.0.0.39a838da8GZzve&mp=1&pdp_npi=6%40dis%21USD%21USD%201.77%21USD%201.77%21%21USD%201.77%21%21%21%402101e7a317892615307562638e1015%2112000058634370611%21ct%21US%216359134517%21%211%210%21)|
|Lipo 3.7V 4000mAh|1|$7.49|[Aliexpress](https://www.aliexpress.com/item/3256812605734224.html?spm=a2g0o.cart.0.0.39a838da8GZzve&mp=1&pdp_npi=6%40dis%21USD%21USD%208.92%21USD%207.49%21%21USD%207.49%21%21%21%402101e7a317892614730068148e1015%2112000059371698515%21ct%21US%216359134517%21%211%210%21)|
|XIAO|1|$9.81|[Aliexpress](https://www.aliexpress.us/item/3256805951491414.html?spm=a2g0o.cart.similar_items.1.39a838da8GZzve&utparam-url=scene%3Aimage_search%7Cquery_from%3Acart_soldout_item%7Cx_object_id%3A1005006137806166%7C_p_origin_prod%3A&algo_pvid=3a43fc97-2929-498d-854e-c946a11dff4b&algo_exp_id=3a43fc97-2929-498d-854e-c946a11dff4b&pdp_ext_f=%7B%22order%22%3A%22312%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%219.81%219.81%21%21%2165.52%2165.52%21%402101e7a317892615953965562e1015%2112000052210886097%21sea%21US%216359134517%21X%211%210%21n_tag%3A-29919%3Bd%3Ad6460094%3Bm03_new_user%3A-29895&gatewayAdapt=4itemAdapt)|
|Threaded inserts and screws|1|$3.10|[Aliexpress](https://www.aliexpress.us/item/3256805741240431.html?spm=a2g0o.productlist.main.41.57b64CLw4CLw4d&algo_pvid=b3e3c5da-66c9-47f0-8bbb-818d9ba33ca5&algo_exp_id=b3e3c5da-66c9-47f0-8bbb-818d9ba33ca5-40&pdp_ext_f=%7B%22order%22%3A%2292%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%213.10%213.10%21%21%2120.70%2120.70%21%402101c4b817892616810608620e1036%2112000034885853182%21sea%21US%216359134517%21X%211%210%21n_tag%3A-29919%3Bd%3Ad6460094%3Bm03_new_user%3A-29895&curPageLogUid=suiafjuPIYKs&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005005927555183%7C_p_origin_prod%3A)|
|Total| |$22.17||
