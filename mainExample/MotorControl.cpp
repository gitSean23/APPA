#include "Arduino.h"
#include "MotorControl.h"

MotorControl::MotorControl(int enablePin, int pin1, int pin2){
  _enablePin = enablePin;
  _pin1 = pin1;
  _pin2 = pin2;

  pinMode(this->_enablePin, OUTPUT);
  pinMode(this->_pin1, OUTPUT);
  pinMode(this->_pin2, OUTPUT);

  this->motorForward();

}

//configures motor to go forward
void MotorControl::motorForward(){
  digitalWrite(this->_pin1, HIGH);
  digitalWrite(this->_pin2, LOW);
}

//configures for motor to go backwards
void MotorControl::motorBackwards(){
  digitalWrite(this->_pin1, LOW);
  digitalWrite(this->_pin2, HIGH);
}

//decelerate motor from full speed(255) to stopped (0)
void MotorControl::decelerate(){

  for (int motorspeed = 255; motorspeed > 0; motorspeed--){
    analogWrite(this->_enablePin, motorspeed);
  }
  
}

//decelerate motor from full speed (255) to a TARGET speed
void MotorControl::decelerate(int target){

  for (int motorspeed = 255; motorspeed > target; motorspeed--){
    analogWrite(this->_enablePin, motorspeed);
  }
}  

//accelerate motor from stop to full speed
void MotorControl::accelerate(){

  for (int motorspeed = 0; motorspeed < 255; motorspeed++){
    analogWrite(this->_enablePin, motorspeed);
  }
  
}

//accelerate motor from stop to TARGET speed
void MotorControl::accelerate(int target){

  for (int motorspeed = 0; motorspeed < target; motorspeed++){
    analogWrite(this->_enablePin, motorspeed);
  }
    
}
