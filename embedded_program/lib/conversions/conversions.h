#ifndef __CONVERSIONS_H__
#define __CONVERSIONS_H__

struct wheel_step_data {
    unsigned int step_number;
    char direction; // 1 := trigonometric direction
};

/**
 * Assuming the left and right wheels rotate with opposite angular speeds,
 *  sets their rotation (in step number) to rotates the specified angle.
 * @param theta_rad The rotation in radian to perform (positive if in trigonometric direction)
 * @param left_wheel_step_data Pointer to the left wheel step number var
 * @param right_wheel_step_data Pointer to the right wheel step number var
 */
void set_wheels_rotation_from_global_rotation(float theta_rad, struct wheel_step_data *left_wheel_step_data, struct wheel_step_data *right_wheel_step_data);

/**
 * Assuming the left and right wheels rotate with the same angular speed,
 *  sets their rotation (in step number) to cross the specified distance.
 * @param distance The distance to travel, in centimetres
 * @param left_wheel_step_data Pointer to the left wheel step number var
 * @param right_wheel_step_data Pointer to the right wheel step number var
 */
void set_wheels_rotation_from_distance(float distance, struct wheel_step_data *left_wheel_step_data, struct wheel_step_data *right_wheel_step_data);

/**
 * Return a valuation of the positive rotation reacht with the scheduled step number.
*/
float steps_to_radian(unsigned int step_number);

/**
 * Return a valuation of the positive distance reacht with the scheduled step number.
*/
float steps_to_centimetres(unsigned int step_number);

#endif