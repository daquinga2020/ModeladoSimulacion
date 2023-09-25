
#include <webots/robot.h>
#include <webots/motor.h>
#include <stdio.h>

#include "global_constants.h"
#include "motors.h"
#include "distance_sensors.h"

#define BASIC_SPIN_UNIT 5.0
#define BASIC_FWD_UNIT 0.01

int main(int argc, char **argv) {

  int side_obstacle = -1;
  int obstacle_check_counter = 0;

  wb_robot_init();

  motors_init();
  distance_sensors_init();

  
  while (wb_robot_step(TIME_STEP) != -1) {
    
    side_obstacle = distance_sensors_detect_obstacle();
    
    if (side_obstacle == LEFT) {
      motors_spin_degrees(RIGHT, BASIC_SPIN_UNIT);
      obstacle_check_counter++;
    }
    else if (side_obstacle == RIGHT) {
      motors_spin_degrees(LEFT, BASIC_SPIN_UNIT);
      obstacle_check_counter++;
    }
    else {
      motors_move_forward_meters(BASIC_FWD_UNIT);
      obstacle_check_counter = 0;
    }
    
    if (obstacle_check_counter > 70)
      motors_spin_degrees(LEFT, 180);
  };


  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}