
#ifndef _MOTORS_MODULE_H
#define _MOTORS_MODULE_H

#include "global_constants.h"

#define MAX_SPEED (2 * PI)
#define WHEEL_RADIUS 0.02
#define AXLE_LEN 0.04

void motors_init(void);

void motors_move_forward_meters(double meters);

void motors_spin_degrees(int left_right, double degrees);


#endif