#include "MotorControl.h"
#include "Rover.h"


//default constructor, empty
Rover::Rover(){

}

//configures rover with motor pins
Rover::Rover(int enableA, int pin1, int pin2, int enableB, int pin3, int pin4){

  MotorControl motora(enableA, pin1, pin2); //initialize left wheel
  MotorControl motorb(enableB, pin3, pin4); //initialize right wheel
  
  //does this beacause _vars are not configured with pins
  this->_motorA = motora;
  this->_motorB = motorb;



}

//accelerates rover to full speed(255)
void Rover::faster(){
    this->_motorA.accelerate();
    this->_motorB.accelerate();
}

//accelerates rover to passed target speed
void Rover::faster(int target){
    this->_motorA.accelerate(target);
    this->_motorB.accelerate(target);
}

//slows rover down to 0
void Rover::slower(){
    this->_motorA.decelerate();
    this->_motorB.decelerate();
}

//slows rover down to passed target speed
void Rover::slower(int target){
    this->_motorA.decelerate(target);
    this->_motorB.decelerate(target);
}

//configures rover to go left by making one forwards, and the other backwards then runs them at full speed
void Rover::left(){
    this->_motorA.motorBackwards();
    this->_motorB.motorForwards();
    this->_motorA.accelerate();
    this->_motorB.accelerate();
}

//configures rover to go right by making one forwards, and the other backwards then runs them at full speed
void Rover::right(){
    this->_motorB.motorBackwards();
    this->_motorA.motorForwards();
    this->_motorB.accelerate();
    this->_motorA.accelerate();
}

