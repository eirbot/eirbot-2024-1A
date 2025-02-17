#include "embedded_strategy.h"
#include "cinematic.h"
#include "task_queue.h"
#include "Arduino.h"
#include "variables.h"

#define delayI 0.4

void allerRetour(float distance){
    enqueueInstruction({'p', 0});
    // enqueueInstruction({'w', delayI});
    // enqueueInstruction({'l', 4.0*3.14/180});
    enqueueInstruction({'w', delayI});
    enqueueInstruction({'f', distance});
    enqueueInstruction({'w', 0.5});
    enqueueInstruction({'p', 90});
    enqueueInstruction({'w', delayI});
    enqueueInstruction({'r', 3.14});
    enqueueInstruction({'w', delayI});
    enqueueInstruction({'f', distance});
    enqueueInstruction({'w', delayI});
    enqueueInstruction({'r', 3.14});
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
    enqueueInstruction({'f', 35});
    // enqueueInstruction({'w', 0.5});
    enqueueInstruction({'r', 3.14/2});

    // enqueueInstruction({'w', 0.5});
    enqueueInstruction({'f', 35});
    // enqueueInstruction({'w', 0.5});
    enqueueInstruction({'r', 3.14/2});

    // enqueueInstruction({'w', 0.5});
    enqueueInstruction({'f', 35});
    // enqueueInstruction({'w', 0.5});
    enqueueInstruction({'r', 3.14/2});
    
    // enqueueInstruction({'w', 0.5});
    enqueueInstruction({'f', 35});
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

void stratBlue6P(){
    enqueueInstruction({'w', 10});
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

void stratBlue3P(){
    enqueueInstruction({'f', 80});
    enqueueInstruction({'p', 7});
    enqueueInstruction({'s', 90});
    enqueueInstruction({'h', 80});
    enqueueInstruction({'p', 105});
    enqueueInstruction({'s', 300});
    enqueueInstruction({'f', 125});
    enqueueInstruction({'l', 2.15});
    enqueueInstruction({'f', 190});
    // enqueueInstruction({'r', 95*3.14/180});
    // enqueueInstruction({'f', 120});
    enqueueInstruction({'e', 0});
}

void stratBlueReact(){
    enqueueInstruction({'w', 10});
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

void stratBlueTest(){
    // enqueueInstruction({'w', 10});
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

void stratYellow6P(){
    enqueueInstruction({'w', 10});
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

void stratYellow3P(){
    enqueueInstruction({'b', 90});
    enqueueInstruction({'p', 7});
    enqueueInstruction({'s', 90});
    enqueueInstruction({'g', 90});
    enqueueInstruction({'p', 105});
    enqueueInstruction({'s', 300});
    enqueueInstruction({'b', 125});
    enqueueInstruction({'l', 3.14 - 2.2});
    enqueueInstruction({'f', 190});
    // enqueueInstruction({'r', 95*3.14/180});
    // enqueueInstruction({'f', 120});
    enqueueInstruction({'e', 0});
}

void stratYellowReact(){
    enqueueInstruction({'w', 10});
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

void stratYellowTest(){
    // enqueueInstruction({'w', 10});
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

void panneaux_solaires_bleus(){
    enqueueInstruction({'f', 80});
    enqueueInstruction({'p', 7});
    enqueueInstruction({'b', 80});
    enqueueInstruction({'p', 105});
    enqueueInstruction({'e', 0});
} 

void stratDragF(){
    enqueueInstruction({'v', 600});
}

#define SOLAR_PANEL_AXIS 1752

#define ARM_UP enqueueInstruction({ROTATE_ARM, 10})
#define ARM_DOWN enqueueInstruction({ROTATE_ARM, 90})

/**
 * The robot is expected to be on the correct bottom left/right-hand
 * corner, looking to the right side of the table.
 */
void staticPath()
{
    // TODO: adapt for blue team
    // 3 solar panels turned 
    struct vector2 path[4] = {
        {2725, SOLAR_PANEL_AXIS},
        {2000, 1615},
        {1163, SOLAR_PANEL_AXIS}
    };
    float currentOrientation = schedule_path(0, path, 3);

    // rotate to right
    struct instruction to_right = {NON_TRIG_ROTATE, currentOrientation};
    if (currentOrientation < 0)
        to_right = {TRIG_ROTATE, -currentOrientation};
    enqueueInstruction(to_right);

    ARM_DOWN;

    path[0] = {1163, SOLAR_PANEL_AXIS};
    path[1] = {1790, SOLAR_PANEL_AXIS};
    currentOrientation = schedule_path(0, path, 2);

    ARM_UP;
    // 3 solar panels turned

    path[0] = {1790, SOLAR_PANEL_AXIS};
    path[1] = {2000, 1685};
    path[2] = {2155, SOLAR_PANEL_AXIS};
    currentOrientation = schedule_path(currentOrientation, path, 3);

    ARM_DOWN;

    path[0] = {2155, SOLAR_PANEL_AXIS};
    path[1] = {2825, SOLAR_PANEL_AXIS};
    currentOrientation = schedule_path(currentOrientation, path, 2);
    
    ARM_UP;

    // 6 plants in zone
    path[0] = {2825, SOLAR_PANEL_AXIS};
    path[1] = {1810, 1600};
    path[2] = {2700, 260};
    currentOrientation = schedule_path(currentOrientation, path, 3);

    // 12 plants in zone
    path[0] = {2700, 260};
    path[1] = {2531, 490};
    path[2] = {1860, 340};
    path[3] = {400, 950};
    currentOrientation = schedule_path(currentOrientation, path, 4);

    // 12 plants in zone + go back to start place
    path[0] = {400, 950}; 
    path[1] = {570, 900};
    path[2] = {660, 1200};
    path[3] = {2000, 1685};
    currentOrientation = schedule_path(currentOrientation, path, 4);

    path[0] = {2000, 1685}; 
    path[1] = {2725, 1752};
    schedule_path(currentOrientation, path, 2);
}

void inspectEnvironmentAndComputeNewStrategy()
{
    //TODO: enqueue a cyclic instruction
    // enqueueInstruction({'a', 0});   
    // carre();
    // allerRetour(110);
    // droiteGauche();

    // if(checkVar(team) == blue){
    //     if(checkVar(match)) stratBlue3P();
    //     else stratBlue();
    // }
    // else if(checkVar(team) == yellow){
    //     if(checkVar(match)) stratYellow3P();
    //     else stratYellow();
    // }

    switch(checkVar(match)){
        // case stratReact:
        //     if(checkVar(team) == blue){
        //         stratBlueReact();
        //     }
        //     else{
        //         stratYellowReact();
        //     }
        //     break;

        //     case strat6P:
        //     if(checkVar(team) == blue){
        //         stratBlue6P();
        //     }
        //     else{
        //         stratYellow6P();
        //     }
        //     break;

        //     case strat3P:
        //     if(checkVar(team) == blue){
        //         stratBlue3P();
        //     }
        //     else{
        //         stratYellow3P();
        //     }
        //     break;

        //     case stratTest:
        //     if(checkVar(team) == blue){
        //         stratBlueTest();
        //     }
        //     else{
        //         stratYellowTest();
        //     }

            case drag:
            stratDragF();
            break;
            case stratCarre:
            carre();
            break;
            case aller_retour:
            allerRetour(50);
            break;

        default:
            break;

    }

    // panneaux_solaires_bleus();
    
    // staticPath();
};