
#include <webots/robot.h>
#include <webots/motor.h>

#include "motors.h"
#include "global_constants.h"

int main(int argc, char **argv) {
  wb_robot_init();
  
  motors_init();
  
  
  motors_move_forward_meters(0.25);
  motors_spin_degrees(LEFT, 90);

  while (wb_robot_step(TIME_STEP) != -1) {
    /*
     * Read the sensors :
     * Enter here functions to read sensor data, like:
     *  double val = wb_distance_sensor_get_value(my_sensor);
     */

    /* Process sensor data here */

    /*
     * Enter here functions to send actuator commands, like:
     * wb_motor_set_position(my_actuator, 10.0);
     */
  };

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}
