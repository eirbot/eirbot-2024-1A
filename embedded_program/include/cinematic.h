struct vector2 {
    float x, y;
};

/**
 * @brief Enqueue instructions for the robot to pass by each of the given positions.
 * @details It is assumed that the robot is already relevantly orientated to reach the first
 * position after its start one. Afterwards, the robots move forward or backward in order to 
 * minimize the rotations. The final position is nevertheless reacht with a forced forward move,
 * so the robot is finally well-orientated.
 * 
 * @param currentOrientation an angle in radian between -pi and pi giving the angle of the robot
 * according to the direction orientated on the right.
 * @param positions An array of positions, assuming the robot to be already in the first one.
 * @param position_number the number of given positions in the array. 
 * 
 * @return the final valued orientation of the robot
 * 
 * @def the coordinate system of the table is defined with a blue zone on the top left-hand corner
 * and the pami zone on the top. x growing => right, y growing => bottom
*/
float schedule_path(float currentOrientation, const struct vector2 positions[], unsigned int position_number);