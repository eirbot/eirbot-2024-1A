#include "instruction.h"

#define YES 1
#define NO 0

/**
 * Must take a string which terminates with the 0 char code
*/
static char is_element_in_tab(char element,
                              const char instruction_type_tab[])
{
    for (unsigned int idx = 0; instruction_type_tab[idx] != 0; ++idx)
        if (instruction_type_tab[idx] == element)
            return YES;
    return NO;
}

char is_forward_instruction(const struct instruction *i)
{
    return is_element_in_tab(i->instruction_type, "fg1");
}

char is_backward_instruction(const struct instruction *i)
{

    return is_element_in_tab(i->instruction_type, "bh2");
}

char is_trig_rotation_instruction(const struct instruction *i)
{
    return is_element_in_tab(i->instruction_type, "l4");
}

char is_non_trig_rotation_instruction(const struct instruction *i)
{
    return is_element_in_tab(i->instruction_type, "r3");
}

char is_rotation_instruction(const struct instruction *i)
{
    return is_trig_rotation_instruction(i) || is_non_trig_rotation_instruction(i);
}

char is_rectilinear_move_instruction(const struct instruction *i)
{
    return is_forward_instruction(i) || is_backward_instruction(i);
}

char is_in_step_instruction(const struct instruction *i)
{
    return is_element_in_tab(i->instruction_type, "123456");
}

char is_in_standard_unit_instruction(const struct instruction *i)
{
    return !is_in_step_instruction(i);
}