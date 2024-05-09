#ifndef __STRATEGY_INTERFACE_H__
#define __STRATEGY_INTERFACE_H__

#include <instruction.h>

/**
 * @brief Check the sensors and return if the robot can execute the instruction
 * 
 * The instruction is not executable if the other robot is in front of the 
 * robot.
 * @param justDequeuedInstruction the instruction to be executed
 * @return 1 if the robot is able to execute the instruction, 0 else.
*/
char canExecuteInstruction(const struct instruction *justDequeuedInstruction);

/**
 * @brief Update the internal data for a minimal real-time strategy 
 * @param justDequeuedInstruction the instruction to be executed
*/
void updateStrategicData(const struct instruction *justDequeuedInstruction);

/**
 * @brief Enqueue and/or dequeue the good instructions to make a deviation avoiding
 * the other robot, given the current queue. 
 * 
 * This function assumes there is no instruction being executing. 
*/
void scheduleDeviationNow();

/**
 * @brief Generate a range of instructions and enqueued it to the
 * task queue. The decision-making algorithm is based on
 * robot's sensorial data.
*/
void inspectEnvironmentAndComputeNewStrategy();

#endif // __STRATEGY_INTERFACE_H__