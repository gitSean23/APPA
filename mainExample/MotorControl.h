/*
 * Library to control motors 
 * Made for the Momo(unofficial name) rover flying on the Appa rocket in the FAR competition
 * Created by Romsev Charles
 * February 23 2022
*/
#ifndef MotorControl_h
#define MotorControl_h


class MotorControl{

    public:
        MotorControl(int enablePin, int pin1, int pin2);
        void decelerate();
        void decelerate(int target);
        void accelerate();
        void accelerate(int target);
        void motorForward();
        void motorBackwards();
        
    private:
        int _enablePin;
        int _pin1;
        int _pin2;

};




#endif
