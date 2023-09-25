
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/distance_sensor.h>

#include "distance_sensors.h"
#include "global_constants.h"

#define NUM_SENSORS 8

static WbDeviceTag ps[NUM_SENSORS];

void distance_sensors_init(void)
{
  int i;
  
  char ps_names[NUM_SENSORS][4] = {
    "ps0", "ps1", "ps2", "ps3",
    "ps4", "ps5", "ps6", "ps7"
  };
  
  for (i = 0; i < NUM_SENSORS; i++) {
    ps[i] = wb_robot_get_device(ps_names[i]);
    wb_distance_sensor_enable(ps[i], TIME_STEP);
  }

}
 
bool distance_sensors_detect_obstacle(int left_right)
{
  bool obstacle_detected = false;
  const double THRESHOLD = 80.0;
  
  int i;
  double ps_values[8];
  for (i = 0; i < NUM_SENSORS ; i++)
    ps_values[i] = wb_distance_sensor_get_value(ps[i]);
  
  if (left_right == RIGHT) {
    obstacle_detected = ps_values[0] > THRESHOLD ||
                        ps_values[1] > THRESHOLD ||
                        ps_values[2] > THRESHOLD;
  }
  else if (left_right == LEFT) {
    obstacle_detected = ps_values[5] > THRESHOLD ||
                        ps_values[6] > THRESHOLD ||
                        ps_values[7] > THRESHOLD;
  }
    
  return obstacle_detected;
}
