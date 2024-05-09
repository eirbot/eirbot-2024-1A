#ifndef __CINEMATIC_H__
#define __CINEMATIC_H__

struct vector2 {
    float x, y;
};

/**
 * @brief Return a + b.
*/
struct vector2 vec__add(const struct vector2 *a, const struct vector2 *b);

/**
 * @brief Return a - b.
*/
struct vector2 vec__minus(const struct vector2 *a, const struct vector2 *b);

/**
 * @brief Return norm*e^{i*argument}
 * @param argument an angle in [-pi; pi]
 * @param norm a positive real
*/
struct vector2 vec_from_arg(float argument, float norm);

/**
 * @brief Add two angles
 * @param angle1 an angle in [-pi; pi]
 * @param angle2 an angle in [-pi; pi]
 * @return the total angle in [-pi; pi]
*/
float angle__add(float angle1, float angle2);

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
 * @param positions An array of positions (cm), assuming the robot to be already in the first one.
 * @param position_number the number of given positions in the array. 
 * 
 * @return the final valued orientation of the robot
 * 
 * @def the coordinate system of the table is the euclidian one, with the blue zone on the solar
 * panels' side at the origin. x growing => right, y growing => top
*/
float schedule_path(float currentOrientation, const struct vector2 positions[], unsigned int position_number);

#endif // __CINEMATIC_H__