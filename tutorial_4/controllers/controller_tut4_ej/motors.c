
#include <webots/robot.h>
#include <webots/motor.h>

#include "motors.h"
#include "global_constants.h"

static WbDeviceTag left_motor;
static WbDeviceTag right_motor;

void motors_init(void)
{
  left_motor = wb_robot_get_device("left wheel motor");
  right_motor = wb_robot_get_device("right wheel motor");
  
  wb_motor_set_position(left_motor, INFINITY);
  wb_motor_set_position(right_motor, INFINITY);
  
  wb_motor_set_velocity(left_motor, 0.0);
  wb_motor_set_velocity(right_motor, 0.0);
}
 
void motors_move_forward_meters(double meters)
{
  double duration = meters/ (2 * PI * WHEEL_RADIUS);
  double t_init = wb_robot_get_time();

  wb_motor_set_velocity(left_motor, MAX_SPEED);
  wb_motor_set_velocity(right_motor, MAX_SPEED);
  
  while (wb_robot_get_time() < t_init + duration) {
    wb_robot_step(TIME_STEP);
  }
  
  wb_motor_set_velocity(left_motor, 0.0);
  wb_motor_set_velocity(right_motor, 0.0);
}

void motors_spin_degrees(int left_right, double degrees)
{
  double motor_speed = MAX_SPEED;
  double duration = ( (AXLE_LEN / 2) / WHEEL_RADIUS) * (degrees / 360);
  double t_init = wb_robot_get_time();
  
  if (left_right == RIGHT) {
    wb_motor_set_velocity(left_motor, motor_speed);
    wb_motor_set_velocity(right_motor, -motor_speed);
  }
  else if (left_right == LEFT) {
    wb_motor_set_velocity(left_motor, -motor_speed);
    wb_motor_set_velocity(right_motor, motor_speed);
  }
  else {
    wb_motor_set_velocity(left_motor, 0.0);
    wb_motor_set_velocity(right_motor, 0.0);
  }
  
  while (wb_robot_get_time() < t_init + duration) {
    wb_robot_step(TIME_STEP);
  }
  
  wb_motor_set_velocity(left_motor, 0.0);
  wb_motor_set_velocity(right_motor, 0.0);
}


