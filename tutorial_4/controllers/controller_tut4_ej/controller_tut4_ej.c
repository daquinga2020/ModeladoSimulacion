
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/distance_sensor.h>

#include "motors.h"
#include "distance_sensors.h"
#include "global_constants.h"

#define BASIC_SPIN_UNIT 5.0
#define BASIC_FWD_UNIT 5.0

int main(int argc, char **argv) {

  bool obstacle_right, obstacle_left;
  
  wb_robot_init();
  
  motors_init();
  distance_sensors_init();
  
  
  /*motors_move_forward_meters(0.25);
  motors_spin_degrees(LEFT, 90);*/

  while (wb_robot_step(TIME_STEP) != -1) {
    obstacle_left = distance_sensors_detect_obstacle(LEFT);
    obstacle_right = distance_sensors_detect_obstacle(RIGHT);
    
    if (obstacle_left)
      motors_spin_degrees(RIGHT, BASIC_SPIN_UNIT);
    else if (obstacle_right)
      motors_spin_degrees(LEFT, BASIC_SPIN_UNIT);
    else
      motors_move_forward_meters(BASIC_FWD_UNIT);
  };

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}
