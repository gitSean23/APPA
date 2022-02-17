/* Compass example for the Nano 33 BLE (Sense)
 * You need version 2.0 or higher of the LMS9DS1 library to run this example 
 * 
 * The compass must be calibrated for the magnetic disturbance of the setup and the environment.
 * Run the DIY calibration program first and copy/paste the Magnetometer calibration data below where it's indicated.
 * 
 * Written by Femme Verbeek 
 *     6 June 2020  
 * Released to the public domain
*/

#include <Arduino_LSM9DS1.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <SPI.h>

#define SCREEN_WIDTH 128                                  
#define SCREEN_HEIGHT 32 

int red_light_pin= 6;
int green_light_pin = 9;
int blue_light_pin = 5;



Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
boolean viewInSerialPlotter=false;                                   // true optimises for serial plotter, false for serial monitor

void setup() {
     Serial.begin(115200);
     if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))  // Address 0x3C for most of these displays, if doesn't work try 0x3D 
  { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);                                   
  } 
   pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);

    // Warmup code
    RGB_color(255, 0, 0);       // Red
  delay(700);
  RGB_color(0, 255, 0);        // Green
  delay(700);
   RGB_color(0, 0, 255);       // Blue
   delay(700);
  RGB_color(0, 0, 0);
  delay(500);

  // Display settings
  display.setTextSize(2);             
  display.setTextColor(SSD1306_WHITE);            
  display.clearDisplay();                         
  Wire.begin();
  
     delay(1000);
     
     if (!IMU.begin()) {               // initialize the magnetometer
        Serial.println("Failed to initialize IMU!");  
        while (1); }


        
/*****************   For a proper functioning of the compass the magnetometer needs to be calibrated    ********************
*****************   Replace the lines below by the output of the DIY_Calibration_Magnetometer sketch   ********************/
   IMU.setMagnetFS(0);
   IMU.setMagnetODR(8);
   IMU.setMagnetOffset(29.419556, -24.602051, 32.031250);
   IMU.setMagnetSlope (1.436859, 1.552535, 1.385790);
/******************************************************************************************************************************     
****  FS  Full Scale        range (0=±400 | 1=±800 | 2=±1200 | 3=±1600  (µT)                                              *****     
****  ODR Output Data Rate  range (6,7,8)=(40,80,400)Hz | not available on all chips (0..5): (0.625,1.25,2.5,5.0,10,20)Hz *****
*******************************************************************************************************************************/     

   IMU.magnetUnit = MICROTESLA;  //   GAUSS   MICROTESLA   NANOTESLA
   if (viewInSerialPlotter) Serial.println(" Heading \t Inclination \t Strength \t mag.X \t mag.Y \t mag.Z ");
   delay(1000)  ;
}
void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}

void loop ()
{  float magY,magX,magZ;
   doNMeasurements (50,magX,magY,magZ);                                  //Average measurements to reduce noise
   float heading= atan2(magY,magX)*180/PI +180;
   float fieldStrength = sqrt(magX*magX +magY*magY+magZ*magZ);
   float inclination = atan(-magZ/sqrt(magX*magX +magY*magY)) *180/PI;    // by definition a positive inclination means the Z component is negative

  Serial.print("Heading ");
   dump(heading,"°  Inclination ");
   dump(inclination,"° Intensity ");
   dump(fieldStrength,"µT  X ");
   dump(magX,"µT  Y ");
   dump(magY,"µT  Z ");
   dump(magZ,"µT");
   Serial.println();
   
   display.clearDisplay(); 
    display.setCursor(0,0); 
    display.println("HEAD: ");
    display.print(heading);
     display.display();
     if (heading <60 && heading > 55)
     {RGB_color(0, 255, 0);} 
     
     else { RGB_color(255, 0, 0);}
}

void dump (float Value, char txt[])
{
  Serial.print(Value);
  Serial.print('\t');
}

void doNMeasurements(unsigned int N, float& averX, float& averY, float& averZ) 
{    float x, y, z;
     averX=0; averY =0; averZ =0;
     for (int i=1;i<=N;i++)
     { while (!IMU.magnetAvailable());
        IMU.readMagnet(x, y, z);
        averX += x; averY += y;  averZ += z;
     } 
     averX /= N;    averY /= N;  averZ /= N;
}
 
