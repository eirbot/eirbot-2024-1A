#include "move_commands.h"

// private functions

/**
 * Assuming the left and right wheels rotate with opposite angular speeds,
 *  sets their rotation to rotates the specified angle.
 * @param theta_rad The rotation in radian to perform
 * @param wheel_left_rotation Pointer to the left wheel rotation angle, in radian
 * @param wheel_right_rotation Pointer to the right wheel rotation angle, in radian
 */
void set_wheels_rotation_from_global_rotation(float theta_rad, float *wheel_left_rotation, float *wheel_right_rotation) {
    if (theta_rad) {
        *wheel_left_rotation = d1*theta_rad/r;
        *wheel_right_rotation = -(*wheel_left_rotation);
    } else {
        *wheel_left_rotation = 0;
        *wheel_right_rotation = 0;
    }
}


/**
 * Assuming the left and right wheels rotate with the same angular speed,
 *  sets their rotation to cross the specified distance.
 * @param distance The distance to travel, in meters
 * @param left_wheel_rotation Pointer to the left wheel rotation angle, in radian
 * @param right_wheel_rotation Pointer to the right wheel rotation angle, in radian
 */
void set_wheels_rotation_from_distance(float distance, float *left_wheel_rotation, float *right_wheel_rotation)
{
    if (distance) {
        *left_wheel_rotation = distance/r;
        *right_wheel_rotation = *left_wheel_rotation;
    } else {
        *left_wheel_rotation = 0;
        *right_wheel_rotation = 0;
    }
}

// header implementations

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
    set_wheels_rotation_from_global_rotation(global_rotation, &left_wheel_rotation, &right_wheel_rotation);
    accomplish_steps(&left_wheel_rotation, &right_wheel_rotation);
}