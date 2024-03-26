#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

/**
 * Instruction types:
 * - 'f': rectilign forward movement (distance in cm)
 * - 'b': rectilign backward movement (distance in cm)
 * - 'r': static right rotation (angle in rad)
 * - 'l': static left rotation (angle in rad)
 * - 'w': wait (time in seconds)
 * - 's': set speed in step per second
*/
struct instruction {
    char instruction_type;
    float value;
};

#endif