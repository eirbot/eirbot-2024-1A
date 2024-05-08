#include "embedded_strategy.h"
#include "task_queue.h"
#include "Arduino.h"
#include "variables.h"

#define delayI 0.4

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

void stratBlue(){
    enqueueInstruction({'f', 80});
    enqueueInstruction({'p', 7});
    enqueueInstruction({'b', 80});
    enqueueInstruction({'p', 100});
    enqueueInstruction({'f', 120});
    enqueueInstruction({'l', 3.14/2});
    enqueueInstruction({'f', 37});
    enqueueInstruction({'r', 95*3.14/180});
    enqueueInstruction({'f', 120});
    enqueueInstruction({'e', 0});
}

void stratYellow(){
    allerRetour(70);
}

void bonjour(){
    enqueueInstruction({'p', 0});
    enqueueInstruction({'p', 90});
}

void droiteGauche(){
    enqueueInstruction({'r', 3.14/2});
    enqueueInstruction({'w', 1});
    enqueueInstruction({'l', 3.14});
    enqueueInstruction({'w', 1});
    enqueueInstruction({'r', 3.14/2});
    enqueueInstruction({'w', 1});
}

void inspectEnvironmentAndComputeNewStrategy()
{
    //TODO: enqueue a cyclic instruction
    // enqueueInstruction({'a', 0});   
    // carre();
    // allerRetour(110);
    // droiteGauche();

    if(checkVar(team) == blue){
        stratBlue();
    }
    else if(checkVar(team) == yellow){
        stratYellow();
    }
};