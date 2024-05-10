#include <conversions.h>
#include "strategy_interface.h"
#include <table.h>
#include "embedded_strategy.h"
#include "stepper_interface.h"
#include <real_time_strategy.h>
#include <variables.h>
#include "sensors.h"

#define YES 1
#define NO 0

/**
 * @param instruction_type an instruction among forward and backward movement
*/
char checkSensorsBeforeRectilinearMove(const struct instruction *instr)
{
    char FwdBwd = 'f'; // FORWARD
    if (is_backward_instruction(instr))
        FwdBwd = 'b';

    char ok = 1;
    float distance;
    for (int i = 1; i < 4; i++)
    {
        distance = readUltrasonic(FwdBwd, i);

        if (distance < DANGER_ZONE_RADIUS && distance > 0.1 /*&& (checkVar(instruct) == 'f' || checkVar(instruct) == 'b')*/)
        {
            ok = 0;
            break;
        }
    }
    return ok;
}

/**
 * @param instruction_type must be a rotation instruction
*/
char checkSensorsBeforeRotation(const struct instruction *instr)
{
    char is_trig_rotation = is_trig_rotation_instruction(instr);
    char ok = YES;
    float distance;

    distance = readUltrasonic('f', is_trig_rotation ? 1: 2);

    if (distance < DANGER_ZONE_RADIUS && distance > 0.1 /*&& (checkVar(instruct) == 'f' || checkVar(instruct) == 'b')*/)
    {
        ok = 0;
    }

    distance = readUltrasonic('b', is_trig_rotation ? 2: 1);

    if (distance < DANGER_ZONE_RADIUS && distance > 0.1 /*&& (checkVar(instruct) == 'f' || checkVar(instruct) == 'b')*/)
    {
        ok = 0;
    }
    return ok;
}

char canExecuteInstruction(const struct instruction *justDequeuedInstruction)
{
    if (is_rotation_instruction(justDequeuedInstruction))
        // TODO: not allow rotation when sensors detect
        // for now, we ignore this issue
        // return checkSensorsBeforeRotation(justDequeuedInstruction);
        return YES;
    if (is_rectilinear_move_instruction(justDequeuedInstruction))
        return checkSensorsBeforeRectilinearMove(justDequeuedInstruction);
    // arm rotation or waiting instruction => OK
    return YES;
}

void updateStrategicData(const struct instruction *justDequeuedInstruction)
{
    if (is_rectilinear_move_instruction(justDequeuedInstruction)) {
        float move_value = justDequeuedInstruction->value;
        if (is_in_step_instruction(justDequeuedInstruction))
            move_value = steps_to_centimetres(move_value);
        return updateNextValuedPosition(move_value,
                                 is_forward_instruction(justDequeuedInstruction));
    }
    if (is_rotation_instruction(justDequeuedInstruction)) {
        float rotation_value = justDequeuedInstruction->value;
        if (is_in_step_instruction(justDequeuedInstruction))
            rotation_value = steps_to_radian(rotation_value);
        return updateNextValuedOrientation(rotation_value,
                                           is_trig_rotation_instruction(justDequeuedInstruction));
    }
}

void scheduleDeviationNow(const struct instruction *interruptedInstr)
{
    if (is_rotation_instruction(interruptedInstr))
        avoir_other_robot_in_rotation(interruptedInstr);
    avoid_other_bot(0, YES); // mock values are here just to precise that 0 steps has been achieved.
}

void scheduleDeviationDuringMovement(const instruction *interruptedInstr)
{
    // TODO: for rotation, nothing is done
    if (is_rectilinear_move_instruction(interruptedInstr)) {
        unsigned int remainingSteps = abortRunningTask();
        avoid_other_bot(remainingSteps / getScheduledStepNumber(), is_forward_instruction(interruptedInstr));
    }
    else
        // TODO: manage during the rotation 
        ;
}

void inspectEnvironmentAndComputeNewStrategy()
{
    init_strategic_data(checkVar(team) == blue);
    initialGlobalStrategy();
}