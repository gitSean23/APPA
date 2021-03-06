/*
 * "Library" to check distance of the Momo(unofficial name) 
 * rover from a predetermined obstacle flying on the Appa rocket in the FAR competition
 * Created by Romsev Charles
 * February 23 2022
*/
#ifndef DistanceSensor_h
#define DistanceSensor_h
#include "Rover.h"
    void sensorSetup();
    void checkArrived(Rover rover, int arrivalDistance, int interval);

#endif
