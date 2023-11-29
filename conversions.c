#include <stdio.h>

#define d1 0.05  // in meters
#define r 0.05 // in meters

/**
    Interacts with the motors to rotates the two wheels with the specified rotation angles.
*/
void accomplish_steps(const float *left_wheel_rotation, const float *right_wheel_rotation)
{

}

/**
    Assuming the left and right wheels rotate with the same angular speed, 
    sets their rotation to cross the specified distance. 
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


/**
    Carries out a rectilign forward move with the specified distance (metres).
*/
void advance(float distance)
{
    float left_wheel_rotation;
    float right_wheel_rotation;
	set_wheels_rotation_from_distance(distance, &left_wheel_rotation, &right_wheel_rotation);
    accomplish_steps(&left_wheel_rotation, &right_wheel_rotation);
}

/**
    Assuming the left and right wheels rotate with opposite angular speeds,
    sets their rotation to rotates the specified angle.
*/
void set_wheels_rotation_from_global_rotation(float global_rotation, float *wheel_left_rotation, float *wheel_right_rotation) {
    if (global_rotation) {
        *wheel_left_rotation = d1*global_rotation/r;
        *wheel_right_rotation = -(*wheel_left_rotation);    
    } else {
        *wheel_left_rotation = 0;
        *wheel_right_rotation = 0;
    }
}

/**
    Rotates the robot with the specified angle (radian). A positive angle means a clock-wise one.
*/
void rotate(float global_rotation)
{
    float left_wheel_rotation;
    float right_wheel_rotation;
	set_wheels_rotation_from_global_rotation(global_rotation, &left_wheel_rotation, &right_wheel_rotation);
    accomplish_steps(&left_wheel_rotation, &right_wheel_rotation);
}