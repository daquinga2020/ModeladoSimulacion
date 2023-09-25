

#include <webots/robot.h>
#include <webots/motor.h>

#include "motors.h"
#include "global_constants.h"

static WbDeviceTag wheels[4];

void motors_init(void)
{
  int i;
  
  char wheels_names[4][7] = {"wheel1", "wheel2", "wheel3", "wheel4"};
  for (i = 0; i < 4; i++) {
    // get a handler to the motors and set target position to infinity (speed control)
    wheels[i] = wb_robot_get_device(wheels_names[i]);
    wb_motor_set_position(wheels[i], INFINITY);
    wb_motor_set_velocity(wheels[i], 0.0);
  }
}

void motors_move_forward_meters(double meters)
{
  int i;
  
  double duration = meters / (2 * PI * WHEEL_RADIUS);
  double t_init = wb_robot_get_time();

  // set up the motor speeds to MAX_SPEED.
  for (i = 0; i < 4; i++) {
    wb_motor_set_velocity(wheels[i], MAX_SPEED);
  }

  // wait for duration
  while (wb_robot_get_time() < t_init + duration) {
    wb_robot_step(TIME_STEP);
  }

  // set up the motor speeds to zero
  for (i = 0; i < 4; i++) {
    wb_motor_set_velocity(wheels[i], 0.0);
  }
}


void motors_spin_degrees(int left_right, double degrees)
{
  int i;
  
  double motor_speed = MAX_SPEED / 2;
  double duration = (AXLE_LEN / WHEEL_RADIUS) * (degrees / 360);
  const double CORRECTION_FACTOR = 1.12;

  duration *= CORRECTION_FACTOR;

  double t_init = wb_robot_get_time();

  // set up the motor speeds to motor_speed.
  if (left_right == RIGHT) {
    // Left wheels
    wb_motor_set_velocity(wheels[0], motor_speed);
    wb_motor_set_velocity(wheels[3], motor_speed);
    
    // Right wheels
    wb_motor_set_velocity(wheels[1], -motor_speed);
    wb_motor_set_velocity(wheels[2], -motor_speed);
  }
  else if (left_right == LEFT) {
    // Left wheels
    wb_motor_set_velocity(wheels[0], -motor_speed);
    wb_motor_set_velocity(wheels[3], -motor_speed);
    
    // Right wheels
    wb_motor_set_velocity(wheels[1], motor_speed);
    wb_motor_set_velocity(wheels[2], motor_speed);
  }
  else {
    for (i = 0; i < 4; i++) {
      wb_motor_set_velocity(wheels[i], 0.0);
    }
  }

  // wait for duration
  while (wb_robot_get_time() < t_init + duration) {
    wb_robot_step(TIME_STEP);
  }

  // set up the motor speeds to zero
  for (i = 0; i < 4; i++) {
    wb_motor_set_velocity(wheels[i], 0.0);
  }
}

