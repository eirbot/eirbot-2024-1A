struct vector2 {
    float x, y;
};

/**
 * @brief Return in radian the rotation for the robot to have the opposite final direction 
 * @details Return ((rotation_angle + pi) % 2pi) - pi
 * @param rotation_angle an angle between -pi and pi
*/
float opposite_angle(float rotation_angle);

/**
 * @brief Return in radian the angle to direct from a to b.
 * @param a the current direction vector in euclidian coordinate system
 * @param b the next dirction vector in euclidian coordinate system
 * @return the radian angle that the robot must rotate by to be
 * directed according to b if it is currently directed according to a.
 * The angle is between -pi and pi.  
*/
float angle(const struct vector2 *a, const struct vector2 *b);


/**
 * @brief Enqueue instructions for the robot to pass by each of the given positions.
 * @details The robots move forward or backward in order to minimize the rotations. The
 * final position is nevertheless reacht with a forced forward move, so the robot is
 * finally well-orientated.
 * 
 * @param currentOrientation an angle in radian between -pi and pi giving the angle of the robot
 * according to the direction orientated on the right.
 * @param positions An array of positions (mm), assuming the robot to be already in the first one.
 * @param position_number the number of given positions in the array. 
 * 
 * @return the final valued orientation of the robot
 * 
 * @def the coordinate system of the table is the euclidian one, with the blue zone on the solar
 * panels' side at the origin. x growing => right, y growing => top
*/
float schedule_path(float currentOrientation, const struct vector2 positions[], unsigned int position_number);