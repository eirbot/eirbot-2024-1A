#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

/**
 * Instruction types:
 * - 'f': rectilign forward movement (distance in cm)
 * - 'r': static rotation (angle in rad)
 * - 'w': wait (time in milliseconds)
*/
struct instruction {
    char instruction_type;
    float value;
};

#endif