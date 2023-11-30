#include "robot_commands.h"
#include "motor_commands.h"

void move_forward(float distance) {
    float left_wheel_rotation;
    float right_wheel_rotation;
    set_wheels_rotation_from_distance(distance, &left_wheel_rotation, &right_wheel_rotation);
    accomplish_steps(&left_wheel_rotation, &right_wheel_rotation);
}

void move_backwards(float distance) {
    move_forward(-distance);
}

void rotate(float theta_rad) {
    float left_wheel_rotation;
    float right_wheel_rotation;
    set_wheels_rotation_from_global_rotation(theta_rad, &left_wheel_rotation, &right_wheel_rotation);
    accomplish_steps(&left_wheel_rotation, &right_wheel_rotation);
}