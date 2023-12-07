#include "motor_commands.h"

#define d1 0.05
#define r 0.05


void set_wheels_rotation_from_global_rotation(float theta_rad, float *left_wheel_rotation, float *right_wheel_rotation) {
    if (theta_rad) {
        *left_wheel_rotation = d1*theta_rad/r;
        *right_wheel_rotation = -(*left_wheel_rotation);
    } else {
        *left_wheel_rotation = 0;
        *right_wheel_rotation = 0;
    }
}

void set_wheels_rotation_from_from_distance(float distance, float *left_wheel_rotation, float *right_wheel_rotation)
{
    if (distance) {
        *left_wheel_rotation = distance/r;
        *right_wheel_rotation = *left_wheel_rotation;
    } else {
        *left_wheel_rotation = 0;
        *right_wheel_rotation = 0;
    }
}