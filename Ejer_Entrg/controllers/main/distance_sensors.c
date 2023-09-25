
#include <webots/robot.h>
#include <webots/distance_sensor.h>

#include "distance_sensors.h"
#include "global_constants.h"


#define NUM_SENSORS 2

static WbDeviceTag ds[NUM_SENSORS];

void distance_sensors_init(void)
{
  int i;
  
  char ds_names[NUM_SENSORS][10] = {"ds_left", "ds_right"};
  for (i = 0; i < NUM_SENSORS; i++) {
    ds[i] = wb_robot_get_device(ds_names[i]);
    wb_distance_sensor_enable(ds[i], TIME_STEP);
  }
}


int distance_sensors_detect_obstacle(void)
{

  int side_detect_obstacle = -1;
  const double THRESHOLD = 700.0;
  double ds_values[NUM_SENSORS];
  
  for (int i = 0; i < NUM_SENSORS ; i++)
    ds_values[i] = wb_distance_sensor_get_value(ds[i]);
  
  if (ds_values[0] < THRESHOLD)
    side_detect_obstacle = LEFT;
  else if (ds_values[1] < THRESHOLD)
    side_detect_obstacle = RIGHT;
  else
    side_detect_obstacle = -1;
    

  return side_detect_obstacle;
}
