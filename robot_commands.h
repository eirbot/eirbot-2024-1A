/**
 * Command the robot to move forward by a given distance.
 * Unit of distance is in meters.
 * @param distance How much distance to travel, in meters.
 */
void move_forward(float distance);

/**
 * Command the robot to move backwards by a given distance.
 * Unit of distance is in meters.
 * @param distance How much distance to travel, in meters.
 */
void move_backwards(float distance);

/**
 * Rotates the robot of a given number of radian.
 * A positive angle will apply a clock-wise rotation.
 * @param theta_rad Rotation value (in rad)
 */
void rotate(float theta_rad);