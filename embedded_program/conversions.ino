#include "conversions.h"

#define d1 0.05
#define r 0.05
#define lambda 100 // step conversion


void set_wheels_rotation_from_global_rotation(float theta_rad, struct wheel_step_data *left_wheel_step_data, struct wheel_step_data *right_wheel_step_data)
{
    if (theta_rad) {
        float rotation = d1*theta_rad/r;
        left_wheel_step_data->step_number = (rotation>=0)?(lambda*rotation):(-lambda*rotation);
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
        float rotation = distance/r;
        left_wheel_step_data->step_number = (rotation>=0)?(lambda*rotation):(-lambda*rotation);;
        left_wheel_step_data->direction = (rotation>=0);
        *right_wheel_step_data = *left_wheel_step_data;
    } else {
        *left_wheel_step_data = {};
        *right_wheel_step_data = {};
    }
}