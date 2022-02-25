#include "Arduino.h"
#include <NewPing.h>    //used for ultrasonic sensor
#include <avr/sleep.h>  //used for sleep mode OPTIONAL
#include "Rover.h"
#include "DistanceSensor.h"
#include "pins.h"



#define MAXDISTANCE 300  //max dist sensor will attempt to read, any farther comes in as 0
// #define ARRIVALPOINT 5 //distance at which rover will stop from the obstacle  in cm
unsigned long time = 0;//starting at 0 seconds so we can check interval

// MotorControl motorA(enA, in1, in2); //left motor
// MotorControl motorB(enB, in3, in4); //right motor

NewPing sonar(trigPin, echoPin, MAXDISTANCE); //attach sensor to get ready to read
void sensorSetup() {
  
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  //set the type of sleep mode we want

  // pinMode(LED_BUILTIN,OUTPUT);
  //Serial.begin(9600);  //uncomment to print distance
  Serial.println("Initialized...");
  delay(2000);  //give some time to initialize

  
}


//checks distance given to see if we've arrived, once we're at the specified distance stops motor and puts arduino to sleep
void checkArrived(Rover rover, int arrivalDistance, int interval) {
  
  
  //wanted to use this method instead of delay(INTERVAL) as it doesn't halt the program as it runs, you can write code underneath it and it wont interfere
  if (millis() >= (time + interval)){ //wait til 1 second has passed to do another sonar reading

    float distance = sonar.ping_cm(); //gets the distance of the ping using the library we imported
    Serial.println(distance);
    
    //checks if we've arrived at our point, also checks if its not 0 because that is a garbage value
    if (distance <= arrivalDistance && distance != 0){
      rover.slower(0);
      delay(1000);
      sleep_mode();
    }

    time = millis(); //update the time to current time so we keep consistent interval in next iteration
    
  }

}
