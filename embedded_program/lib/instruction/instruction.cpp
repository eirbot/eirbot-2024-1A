#include <Arduino.h>
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
    return is_element_in_tab(i->instruction_type, "fg15");
}

char is_backward_instruction(const struct instruction *i)
{

    return is_element_in_tab(i->instruction_type, "bh26");
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

char is_slow_move_instruction(const struct instruction *i)
{
    return is_element_in_tab(i->instruction_type, "gh56");
}


void displayInstruction(const struct instruction *i)
{
    char instrct_type[32]="";
    char unit[8] = "";
    float value = i->value;
    if (is_forward_instruction(i))
        strcpy(instrct_type, "FORWARD");
    else if (is_backward_instruction(i))
        strcpy(instrct_type, "BACKWARD");
    else if (is_trig_rotation_instruction(i))
        strcpy(instrct_type, "TRIG ROTATE");
    else if (is_non_trig_rotation_instruction(i))
        strcpy(instrct_type, "NON TRIG ROTATE");
    else if (i->instruction_type == WAIT)
        strcpy(instrct_type, "WAIT");
    else if (i->instruction_type == ROTATE_ARM)
        strcpy(instrct_type, "ROTATE ARM");
    else if (i->instruction_type == CHANGE_SPEED)
        strcpy(instrct_type, "CHANGE SPEED");
    else
        strcpy(instrct_type, "?TYPE NOT MANAGED BY DISPLAY?");

    if (is_in_step_instruction(i))
        strcpy(unit, "STEP");
    else if (is_rectilinear_move_instruction(i))
        strcpy(unit, "CM");
    else if (i->instruction_type == WAIT)
        strcpy(unit, "SEC");
    else if (i->instruction_type == CHANGE_SPEED)
        strcpy(unit, "STEP/S");
    else if (i->instruction_type == ROTATE_ARM)
        strcpy(unit, "DEG");
    else if (is_rotation_instruction(i)) {
        // strcpy(unit, "RAD");
        value = value*180/M_PI;
        strcpy(unit, "DEG");
    }
    
    Serial.print("-- Type: '");
    Serial.print(instrct_type);
    if (is_slow_move_instruction(i))
        Serial.print(" SLOW");
    Serial.print("', Value: ");
    Serial.print(value);
    Serial.print(" ");
    Serial.print(unit);
    Serial.println(" --");
}