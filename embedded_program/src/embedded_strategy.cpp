#include <Arduino.h>
#include <math.h>
#include "embedded_strategy.h"
#include "cinematic.h"
#include "task_queue.h"
#include "variables.h"

#define delayI 0.4
#define MAX_PATH_LENGTH = 256

float currentOrientation;
struct vector2 lastStartValuedPosition;
struct vector2 nextValuedPosition;

void updateNextValuedPosition(float forward_cm, int is_forward)
{
    lastStartValuedPosition = nextValuedPosition;
    struct vector2 moveVec = vec_from_arg(currentOrientation, forward_cm);
    if (!is_forward)
        moveVec = {-moveVec.x, -moveVec.y};
    nextValuedPosition = vec__add(&nextValuedPosition, &moveVec);
}

void updateNextValuedOrientation(float rotation_rad, int is_trig_rotation)
{
    float rotation = is_trig_rotation?rotation_rad:-rotation_rad;
    currentOrientation = angle__add(currentOrientation, rotation);
}

void avoid_other_bot(unsigned int total_scheduled_steps, unsigned int remaining_steps,
                     int is_forward_move) {
    struct vector2 currentMoveVector = vec__minus(&nextValuedPosition, &lastStartValuedPosition);
    struct vector2 currentValuedPosition = vec__add(&lastStartValuedPosition, {
        currentMoveVector.x*remaining_steps/total_scheduled_steps,
        currentMoveVector.y*remaining_steps/total_scheduled_steps
    });
}

void allerRetour(float distance){
    // enqueueInstruction({'p', 0});
    // enqueueInstruction({'w', delayI});
    // enqueueInstruction({'l', 4.0*3.14/180});
    enqueueInstruction({'w', delayI});
    enqueueInstruction({'f', distance});
    // enqueueInstruction({'w', delayI});
    // enqueueInstruction({'r', 4.0*3.14/180});
    // enqueueInstruction({'w', 0.5});
    // enqueueInstruction({'p', 90});
    enqueueInstruction({'w', delayI});
    enqueueInstruction({'b', distance});
}

void allerRetourVitesse(float distance){
    enqueueInstruction({'p', 0});
    enqueueInstruction({'w', 0.5});
    enqueueInstruction({'s', distance});
    enqueueInstruction({'w', 0.5});
    enqueueInstruction({'p', 90});
    enqueueInstruction({'b', distance});
}

void carre(){
    // enqueueInstruction({'w', 0.5});
    enqueueInstruction({'f', 50});
    // enqueueInstruction({'w', 0.5});
    enqueueInstruction({'r', 3.14/2});

    // enqueueInstruction({'w', 0.5});
    enqueueInstruction({'f', 50});
    // enqueueInstruction({'w', 0.5});
    enqueueInstruction({'r', 3.14/2});

    // enqueueInstruction({'w', 0.5});
    enqueueInstruction({'f', 50});
    // enqueueInstruction({'w', 0.5});
    enqueueInstruction({'r', 3.14/2});
    
    // enqueueInstruction({'w', 0.5});
    enqueueInstruction({'f', 50});
    // enqueueInstruction({'w', 0.5});
    enqueueInstruction({'r', 3.14/2});
}


void ramenerLesPots(){

    enqueueInstruction({'w', 5});

    enqueueInstruction({'f', 120});
    enqueueInstruction({'w', 0.5});

    enqueueInstruction({'r', 3.14/2});
    enqueueInstruction({'w', 0.5});

    enqueueInstruction({'f', 75.8});
    enqueueInstruction({'w', 0.5});

    enqueueInstruction({'r', 2.129});
    enqueueInstruction({'w', 0.5});

    enqueueInstruction({'f', 130});
    enqueueInstruction({'s', 0});
    enqueueInstruction({'e', 0});
}

void stratBlueFFFF(){
    enqueueInstruction({'f', 170});
    enqueueInstruction({'p', 7});
    enqueueInstruction({'s', 90});
    enqueueInstruction({'h', 170});
    enqueueInstruction({'p', 105});
    enqueueInstruction({'s', 300});
    enqueueInstruction({'f', 125});
    enqueueInstruction({'l', 2.15});
    enqueueInstruction({'f', 190});
    // enqueueInstruction({'r', 95*3.14/180});
    // enqueueInstruction({'f', 120});
    enqueueInstruction({'e', 0});
}

void stratBlue(){
    enqueueInstruction({'7', 170});
    enqueueInstruction({'p', 7});
    enqueueInstruction({'s', 90});
    enqueueInstruction({'h', 170});
    enqueueInstruction({'p', 105});
    enqueueInstruction({'s', 300});
    enqueueInstruction({'f', 125});
    enqueueInstruction({'l', 2.15});
    enqueueInstruction({'f', 190});
    // enqueueInstruction({'r', 95*3.14/180});
    // enqueueInstruction({'f', 120});
    enqueueInstruction({'e', 0});
}

void stratYellowFFFF(){
    enqueueInstruction({'b', 185});
    enqueueInstruction({'p', 7});
    enqueueInstruction({'s', 90});
    enqueueInstruction({'g', 185});
    enqueueInstruction({'p', 105});
    enqueueInstruction({'s', 300});
    enqueueInstruction({'b', 125});
    enqueueInstruction({'l', 3.14 - 2.2});
    enqueueInstruction({'f', 190});
    // enqueueInstruction({'r', 95*3.14/180});
    // enqueueInstruction({'f', 120});
    enqueueInstruction({'e', 0});
}

void stratYellow(){
    enqueueInstruction({'8', 185});
    enqueueInstruction({'p', 7});
    enqueueInstruction({'s', 90});
    enqueueInstruction({'g', 185});
    enqueueInstruction({'p', 105});
    enqueueInstruction({'s', 300});
    enqueueInstruction({'b', 125});
    enqueueInstruction({'l', 3.14 - 2.2});
    enqueueInstruction({'f', 190});
    // enqueueInstruction({'r', 95*3.14/180});
    // enqueueInstruction({'f', 120});
    enqueueInstruction({'e', 0});
}

void bonjour(){
    enqueueInstruction({'p', 7});
    enqueueInstruction({'p', 105});
}

void droiteGauche(){
    enqueueInstruction({'r', 3.14/2});
    enqueueInstruction({'w', 1});
    enqueueInstruction({'l', 3.14});
    enqueueInstruction({'w', 1});
    enqueueInstruction({'r', 3.14/2});
    enqueueInstruction({'w', 1});
}

#define START_POSITION {300-13.570, 200-9.0554}
#define SOLAR_PANEL_AXIS 200-175.2

void panneaux_solaires_bleus(){
    enqueueInstruction({'f', 80});
    enqueueInstruction({'p', 7});
    enqueueInstruction({'b', 80});
    enqueueInstruction({'p', 105});
    enqueueInstruction({'e', 0});
} 


#define ARM_UP enqueueInstruction({ROTATE_ARM, 100})
#define ARM_DOWN enqueueInstruction({ROTATE_ARM, 7})

/**
 * The robot is expected to be on the correct bottom left/right-hand
 * corner, looking to the right side of the table. He is yellow for now.
 */
void staticPath()
{
    // TODO: adapt for blue team
    // TODO: everything in euclidian coordinates
    // 6 solar panels turned
    struct vector2 path[4] = {
        START_POSITION,
        {116.3, SOLAR_PANEL_AXIS},
    };
    float currentOrientation = schedule_path(0, path, 2);

    ARM_DOWN;
    // TODO: slow down for solar panels

    path[0] = {116.3, SOLAR_PANEL_AXIS};
    path[1] = {282.5, SOLAR_PANEL_AXIS};
    currentOrientation = schedule_path(currentOrientation, path, 2);

    ARM_UP;
    //TODO: speed up

    // // 6 plants in zone
    // path[0] = {2825, SOLAR_PANEL_AXIS};
    // path[1] = {1810, 1600};
    // path[2] = {2700, 260};
    // currentOrientation = schedule_path(currentOrientation, path, 3);

    // // 12 plants in zone
    // path[0] = {2700, 260};
    // path[1] = {2531, 490};
    // path[2] = {1860, 340};
    // path[3] = {400, 950};
    // currentOrientation = schedule_path(currentOrientation, path, 4);

    // // 12 plants in zone + go back to start place
    // path[0] = {400, 950}; 
    // path[1] = {570, 900};
    // path[2] = {660, 1200};
    // path[3] = {2000, 1685};
    // currentOrientation = schedule_path(currentOrientation, path, 4);

    // path[0] = {2000, 1685}; 
    // path[1] = {2725, 1752};
    // schedule_path(currentOrientation, path, 2);
}

void inspectEnvironmentAndComputeNewStrategy()
{
    //TODO: enqueue a cyclic instruction
    // enqueueInstruction({'a', 0});   
    // carre();
    // allerRetour(110);
    // droiteGauche();

    if(checkVar(team) == blue){
        if(checkVar(match)) stratBlueFFFF();
        else stratBlue();
    }
    else if(checkVar(team) == yellow){
        if(checkVar(match)) stratYellowFFFF();
        else stratYellow();
    }

    // panneaux_solaires_bleus();
    
    staticPath();
    displayQueue();
};