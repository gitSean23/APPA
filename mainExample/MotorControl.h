/*
 * Library to control a rover
 * Made for the Momo(unofficial name) rover flying on the Appa rocket in the FAR competition
 * Created by Romsev Charles
 * February 23 2022
*/
#ifndef MotorControl_h
#define MotorControl_h


class MotorControl{

    public:
        MotorControl(); //Does nothing, constructor is empty
        MotorControl(int enablePin, int pin1, int pin2); //initializes motors with these 3 pins
        void decelerate(); //slows motor speed to 0
        void decelerate(int target); //slows down motor to passed target speed
        void accelerate(); //makes motor accelerate to as fast as possible (255)
        void accelerate(int target); //accelerates motor to target speed from 0
        void motorForwards(); //configures motor to be able to go forward
        void motorBackwards(); //reverses polarity to configure motor to go backwards
        
    protected:
        int _enablePin;
        int _pin1;
        int _pin2;

};



#endif
