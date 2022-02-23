/*
 * Example of how this code would get implemented into unified code of the arduino
*/

#include "DistanceSensor.h" //library for distance checker
#include "MotorControl.h" //library for motor control
#include "pins.h" //where all our pins are defined
#define arrivalDistance 5 //distance we want to check we're at to stop in centimeteres
#define intervalMS      100 //how many times to check milliseconds

MotorControl motor1(enA, in1, in2); //left motor
MotorControl motor2(enB, in3, in4); //right motor
void setup()
{
    sensorSetup();
    motor2.accelerate();
    motor1.accelerate();
}

void loop()
{
    
    checkArrived(arrivalDistance, intervalMS);

}
