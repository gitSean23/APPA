#include <Wire.h>
#include <SPI.h>
#include<SD.h>
#include <Adafruit_BMP280.h>

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (7)

Adafruit_BMP280 bmp; // I2C
//Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
//Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

File cardFile;

void setup() {
  Serial.begin(9600);
  Serial.println(F("BMP280 test"));
  SD.begin(BMP_CS);
  cardFile = SD.open("SDTest.rtf", FILE_WRITE); //Opens the file

  //if (!bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID)) {
  if (!bmp.begin()) {
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
}

void loop() {
    delay(2000);
    
    readTemp("far");
    cardFile = SD.open("SDTest.rtf", FILE_WRITE);
    cardFile.println(logTemp("far"));
    readPress("pa");

    //Serial.print(F("Approx altitude = "));
    //Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
    //Serial.println(" m");

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
