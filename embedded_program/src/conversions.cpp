#include "conversions.h"

#define AXLE_TREE_LENGTH 13.05 // centimetres
#define WHEEL_RADIUS 3.63 // centimetres
#define STEPS_BY_RAD 4074.36654208 // steps/rad


void set_wheels_rotation_from_global_rotation(float theta_rad, struct wheel_step_data *left_wheel_step_data, struct wheel_step_data *right_wheel_step_data)
{
    if (theta_rad) {
        float rotation = AXLE_TREE_LENGTH*theta_rad/WHEEL_RADIUS;
        left_wheel_step_data->step_number = (rotation>=0)?(STEPS_BY_RAD*rotation):(-STEPS_BY_RAD*rotation);
        left_wheel_step_data->direction = (rotation>=0);
        right_wheel_step_data->step_number = left_wheel_step_data->step_number;
        right_wheel_step_data->direction = !(left_wheel_step_data->direction);
    } else {
        *left_wheel_step_data = {};
        *right_wheel_step_data = {};
    }
}

void set_wheels_rotation_from_distance(float distance, struct wheel_step_data *left_wheel_step_data, struct wheel_step_data *right_wheel_step_data)
{
    if (distance) {
        float rotation = distance/WHEEL_RADIUS;
        left_wheel_step_data->step_number = (rotation>=0)?(STEPS_BY_RAD*rotation):(-STEPS_BY_RAD*rotation);;
        left_wheel_step_data->direction = (rotation>=0);
        *right_wheel_step_data = *left_wheel_step_data;
    } else {
        *left_wheel_step_data = {};
        *right_wheel_step_data = {};
    }
}