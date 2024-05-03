struct vector2 {
    int x, y;
};

/**
 * @brief Enqueue instructions for the robot to pass by each of the given positions
 * @param positions An array of positions, assuming the robot to be already in the first one.
 * @param position_number the number of given positions in the array. 
*/
void schedulePath(const struct vector2 positions[], unsigned int position_number);