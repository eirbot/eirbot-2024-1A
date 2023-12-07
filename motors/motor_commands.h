// This file handles the connection to the motors and any low-level
// commands that must be sent to the motors

/**
 * Assuming the left and right wheels rotate with opposite angular speeds,
 *  sets their rotation to rotates the specified angle.
 * @param theta_rad The rotation in radian to perform
 * @param left_wheel_rotation Pointer to the left wheel rotation angle, in radian
 * @param right_wheel_rotation Pointer to the right wheel rotation angle, in radian
 */
void set_wheels_rotation_from_global_rotation(float theta_rad, float *left_wheel_rotation, float *right_wheel_rotation);

/**
 * Assuming the left and right wheels rotate with the same angular speed,
 *  sets their rotation to cross the specified distance.
 * @param distance The distance to travel, in meters
 * @param left_wheel_rotation Pointer to the left wheel rotation angle, in radian
 * @param right_wheel_rotation Pointer to the right wheel rotation angle, in radian
 */
void set_wheels_rotation_from_distance(float distance, float *left_wheel_rotation, float *right_wheel_rotation);


void accomplish_steps(float *left_wheel_rotation, float *right_wheel_rotation);