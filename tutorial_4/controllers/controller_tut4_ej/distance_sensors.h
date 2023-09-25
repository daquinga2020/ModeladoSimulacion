// avanzo 2*pi*r <-> 1 seg
// meters <-> duration
#ifndef _DISTANCESENSORS_MODULE_H
#define _DISTANCESENSORS_MODULE_H

#include "global_constants.h"

void distance_sensors_init(void);

bool distance_sensors_detect_obstacle(int left_right);

#endif