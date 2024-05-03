#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#define FORWARD 'f'
#define BACKWARD 'b'
#define NON_TRIG_ROTATE 'r'
#define TRIG_ROTATE 'l'
#define WAIT 'w'
#define CHANGE_SPEED 's'

#define FORWARD_S '1'
#define BACKWARD_S '2'
#define NON_TRIG_ROTATE_S '3'
#define TRIG_ROTATE_S '4'

/**
 * Instruction types:
 * - 'f': rectilign forward movement (distance in cm)
 * - 'b': rectilign backward movement (distance in cm)
 * - 'r': static non-trigo rotation (angle in rad)
 * - 'l': static trigo rotation (angle in rad)
 * - 'w': wait (time in seconds)
 * - 's': set speed in step per second
 * - '1': rectilign forward movement (in step number)
 * - '2': rectiling backward movement (in step number)
 * - '3': static non-trigo rotation (in step number)
 * - '4': static trigo rotation (in step number)
 */
struct instruction {
    char instruction_type;
    float value;
};

#endif