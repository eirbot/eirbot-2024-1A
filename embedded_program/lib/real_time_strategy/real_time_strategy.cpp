#include <Arduino.h>
#include <cinematic.h>
#include <constants.h>
#include <instruction.h>
#include <task_queue.h>

float currentOrientation;
struct vector2 lastStartValuedPosition;
struct vector2 nextValuedPosition;

void init_strategic_data(char in_blue_team) {
    currentOrientation = in_blue_team ? 0: M_PI;
    lastStartValuedPosition = START_POSITION;
    nextValuedPosition = START_POSITION;
}

void updateNextValuedPosition(float forward_cm, int is_forward)
{
    lastStartValuedPosition = nextValuedPosition;
    Serial.print(lastStartValuedPosition.x);
    Serial.println(lastStartValuedPosition.y);
    struct vector2 moveVec = vec_from_arg(currentOrientation, forward_cm);
    if (!is_forward)
        moveVec = {-moveVec.x, -moveVec.y};
    nextValuedPosition = vec__add(&nextValuedPosition, &moveVec);
}

void updateNextValuedOrientation(float rotation_rad, int is_trig_rotation)
{
    float rotation = is_trig_rotation?rotation_rad:-rotation_rad;
    currentOrientation = angle__add(currentOrientation, rotation);
    Serial.print(currentOrientation*180/M_PI);
    Serial.print("\n");
}

/**
 * It is assumed the next scheduled instruction is a rotation
 * to the next position to be reacht.
*/
void skip_current_scheduled_position(float remaining_distance, const struct vector2 *currentStopPosition)
{
    // TODO
    // nextValuedPosition = *currentStopPosition;
    // float nextCurrentOrientation = ;
    // float rotation = dequeueInstruction();
}

void reach_next_position_from_deviation(float remaining_distance, const struct vector2 *currentStopPosition)
{
    // TODO: figure out if a deviation on the left is possible
    // then
        nextValuedPosition = *currentStopPosition;
        pushInstruction({NON_TRIG_ROTATE, M_PI_2});
        pushInstruction({FORWARD, remaining_distance});
        pushInstruction({TRIG_ROTATE, M_PI_2});
        return;

    // TODO: figure out if a deviation on the right is possible
    // then
    //    pushInstruction({TRIG_ROTATE, M_PI_2});
    //    pushInstruction({FORWARD, remaining_distance});
    //    pushInstruction({NON_TRIG_ROTATE, M_PI_2});
    //    return;

    return skip_current_scheduled_position(remaining_distance, currentStopPosition);
}

void avoid_other_bot(unsigned int total_scheduled_steps, unsigned int remaining_steps,
                     int is_forward_move) {
    struct vector2 achievedMoveVector = vec__minus(&nextValuedPosition, &lastStartValuedPosition);
    float remaining_distance = vec__magnitude(&achievedMoveVector);
    achievedMoveVector.x *= (1-remaining_steps/total_scheduled_steps);
    achievedMoveVector.y *= (1-remaining_steps/total_scheduled_steps);
    struct vector2 currentValuedPosition = vec__add(&lastStartValuedPosition, &achievedMoveVector);
    if (remaining_distance < DANGER_ZONE_RADIUS)
        // the next position is unreachable so we skip it
        // and go to the next scheduled position
        return skip_current_scheduled_position(remaining_distance, &currentValuedPosition);
    // try to make a deviation
    return reach_next_position_from_deviation(remaining_distance, &currentValuedPosition);
}