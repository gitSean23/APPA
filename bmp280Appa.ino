#include <Wire.h>
#include <SPI.h>
#include<SD.h>
#include <Adafruit_BMP280.h>

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (7)
#define PIN_LED   (5)

unsigned long timePassed;

float alt[50];
float acc[50]; 

int altCount = 0;
int accCount = 0;

bool apogee = false;
bool *apogeeptr = &apogee; 
int count = 0;

Adafruit_BMP280 bmp; // I2C
//Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
//Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

File cardFile;

void setup() {
  Serial.begin(9600); //Sets up the serial port
  Serial.println("Initializing SD"); 
  if(!SD.begin(BMP_CS)){
    Serial.println("Initialization unsuccessful");
    while(true);
  }
  Serial.println("SD initialization successful!");
  SD.begin(BMP_CS); //SD Card starts up
  cardFile = SD.open("SDTest.rtf", FILE_WRITE); //Opens the file

  //if (!bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID)) {
  if (!bmp.begin()) { //Checks if a bmp sensor exists
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  timePassed = millis(); //Setting up the elapsed time
}

void loop() {
    delay(2000);
    
    readTemp("far"); //Prints the temperature in farenheit 
    cardFile = SD.open("SDTest.rtf", FILE_WRITE); //Sets up a text file to write in
    logTemp("far");//Takes the value of the temperatures and writes it into the text file
    alt[altCount] = logTemp("far");
    readPress("pa"); //Prints the pressure in pascals

    //Serial.print(F("Approx altitude = "));
    //Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
    //Serial.println(" m");

    EDL(false, true); //Calls the edl function
    altCount++; 
    accCount++;

    Serial.println();
    delay(2000);
}

//Reads temperature @param option 
void readTemp(String option){
  if (option == "far"){
    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature()*(9/5)+32);
    Serial.println(" *F");
  }
}

 //Logs temperature to SD card @param option @return float temp
 float logTemp(String option){
    if(option == "far"){
      float fTemp = bmp.readTemperature()*(9/5)+32;
      cardFile.print("Temperature: ");
      cardFile.print(fTemp);
      cardFile.println(" *F");
      cardFile.close();
      return fTemp;
    }

    else if(option == "cel"){
      float cTemp = bmp.readTemperature();
      cardFile.print("Temperature: ");
      cardFile.print(cTemp);
      cardFile.println(" *C");
      cardFile.close();
      return cTemp;
    }

    else if(option == "kel"){
      float kTemp = bmp.readTemperature()+273.15;
      cardFile.print("Temperature: ");
      cardFile.print(kTemp);
      cardFile.println(" K");
      cardFile.close();
      return kTemp;
    }

    else{
      Serial.println("Option not available");
      cardFile.close();
  }
 }

//Reads pressure @param option 
void readPress(String option){
  if (option == "mil"){
    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure()/100);
    Serial.println(" Milibar");
}
  else if(option == "pa"){
    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");
  }

  else if(option == "bar"){
    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure()*100000);
    Serial.println(" Barr");
  }
}



int EDL(bool landed, bool activated){
  if(bmp.readAltitude() <= 50.00){ //Ignition
    Serial.println("Event --> Ignition");
    return 1;
  }

  else if (bmp.readAltitude() >= 65.00 && alt[altCount] < 65.00){ //Liftoff
    Serial.println("Event --> Liftoff!");
    return 2;
  }

  else if (bmp.readAltitude() >= 115.00 && alt[count] < 115.00) { //Motor Burnout
    Serial.println("Event --> Burnout");
    return 3;
  }

  else if(bmp.readAltitude() >= 205.00 && alt[count] < 205.00){ //Ejection Charge
    Serial.println("Event --> Ejection Charge");
    return 4;
  }

  else if ((bmp.readAltitude() == 300.00) && alt[count] > 300.00){
    Serial.println("Event --> Main Parachute Deployment");
    return 5;
  }

  else if (bmp.readAltitude() <= 50.00 && alt[count] > 50.00){
    Serial.println("Event --> Landed!");
    return 6;
  }

  return 0;
}

//int safety(){
  //if(bmp.readPressure() == 
  //if pressure is too high
      //print (too high);
      //blink red LED
      //adjust velocity value

  //else
    //print (pressure is fine)
    //blink green LED
//}
