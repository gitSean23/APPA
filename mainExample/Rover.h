#ifndef Rover_h
#define Rover_h
#include "MotorControl.h"


class Rover{

    private:
        MotorControl _motorA;
        MotorControl _motorB;

    public:
        
        Rover();
        Rover(int enableA, int pin1, int pin2, int enableB, int pin3, int pin4);
        void faster();
        void faster(int target);
        void slower();
        void slower(int target);
        void straight();
        void left();
        void right();
};

#endif