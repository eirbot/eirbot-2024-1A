struct vector2 {
    int x, y;
};

/**
 * @brief Enqueue instructions for the robot to pass by each of the given positions.
 * @details It is assumed that the robot is already relevantly orientated to reach the first
 * position after its start one. Afterwards, the robots move forward or backward in order to 
 * minimize the rotations. The final position is nevertheless reacht with a forced forward move,
 * so the robot is finally well-orientated.
 * @param positions An array of positions, assuming the robot to be already in the first one.
 * @param position_number the number of given positions in the array. 
*/
void schedulePath(const struct vector2 positions[], unsigned int position_number);