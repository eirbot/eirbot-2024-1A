#ifndef __CONVERSIONS_H__
#define __CONVERSIONS_H__

struct wheel_step_data {
    unsigned int step_number;
    char direction; // 1 := trigonometric direction
};

/**
 * Assuming the left and right wheels rotate with opposite angular speeds,
 *  sets their rotation to rotates the specified angle.
 * @param theta_rad The rotation in radian to perform (positive if in trigonometric direction)
 * @param left_wheel_step_data Pointer to the left wheel step number var
 * @param right_wheel_step_data Pointer to the right wheel step number var
 */
void set_wheels_rotation_from_global_rotation(float theta_rad, struct wheel_step_data *left_wheel_step_data, struct wheel_step_data *right_wheel_step_data);

/**
 * Assuming the left and right wheels rotate with the same angular speed,
 *  sets their rotation to cross the specified distance.
 * @param distance The distance to travel, in meters 
 * @param left_wheel_step_data Pointer to the left wheel step number var
 * @param right_wheel_step_data Pointer to the right wheel step number var
 */
void set_wheels_rotation_from_distance(float distance, struct wheel_step_data *left_wheel_step_data, struct wheel_step_data *right_wheel_step_data);

#endif