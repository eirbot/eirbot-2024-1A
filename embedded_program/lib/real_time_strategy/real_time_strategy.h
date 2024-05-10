#ifndef __REAL_TIME_STRATEGY_H__
#define __REAL_TIME_STRATEGY_H__
/** Call this function at the setup step.
 * 
 * @param in_blue_team true if the robot is in the blue team
*/
void init_strategic_data(char in_blue_team);

/** Update the next predicted position when a new forward/backward instruction
 * is dequeued.
 * 
 * This function has to be called at each dequeue so the avoiding strategy can work.
*/
void updateNextValuedPosition(float forward_cm, int is_forward);

/** Update the next predicted orientation when a new rotation instruction
 * is dequeued.
 * 
 * This function has to be called at each dequeue so the avoiding strategy can work.
*/
void updateNextValuedOrientation(float rotation_rad, int is_trig_rotation);

/** Push avoiding instructions to reach the next position which had been scheduled.
 * @param progression_ratio the ratio of the recilinear/rotational task that has been
 * achieved
 * @param is_forward_move 1 if the move is forward, 0 if it is a backward move. 
*/
void avoid_other_bot(float remaining_steps,
                     int is_forward_move);

void avoir_other_robot_in_rotation(const struct instruction *impossible_rotation);

#endif // __REAL_TIME_STRATEGY_H__