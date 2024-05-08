#ifndef __TASK_QUEUE_H__
#define __TASK_QUEUE_H__

#include "instruction.h"

#define MAX_QUEUE_SIZE 200

/**
 * Pop the instruction at the head of the queue and
 * returns it. If the queue is empty, returns a false
 * instruction with a useless type. 
*/
struct instruction dequeueInstruction();

/**
 * Erase all the pending instructions in the queue.
*/
void clearQueue();

/**
 * Add at the tail of the queue a new instruction.
 * @param instrct The instruction to be added.
*/
void enqueueInstruction(struct instruction instrct);


/**
 * Add the instruction in priority in the queue 
 * @param instrct The instruction to be added.
 */
void pushInstruction(struct instruction instrct);

/**
 * Returns 1 if the queue is empty, else 0.
*/
char isQueueEmpty();

/**
 * Display all the pending instructions, from the most prioritary
 * one to the last.
*/
void displayQueue();

#endif
