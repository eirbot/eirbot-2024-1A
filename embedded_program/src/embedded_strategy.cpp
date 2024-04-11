#include "embedded_strategy.h"
#include "task_queue.h"
#include "Arduino.h"


void allerRetour(float distance){
    // enqueueInstruction({'p', 0});
    enqueueInstruction({'w', 0.5});
    enqueueInstruction({'f', distance});
    enqueueInstruction({'w', 0.5});
    // enqueueInstruction({'p', 90});
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
    enqueueInstruction({'w', 0.5});
    enqueueInstruction({'f', 50});
    enqueueInstruction({'w', 0.5});
    enqueueInstruction({'r', 3.14/2});

    enqueueInstruction({'w', 0.5});
    enqueueInstruction({'f', 50});
    enqueueInstruction({'w', 0.5});
    enqueueInstruction({'r', 3.14/2});

    enqueueInstruction({'w', 0.5});
    enqueueInstruction({'f', 50});
    enqueueInstruction({'w', 0.5});
    enqueueInstruction({'r', 3.14/2});
    
    enqueueInstruction({'w', 0.5});
    enqueueInstruction({'f', 50});
    enqueueInstruction({'w', 0.5});
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

void stratYellow(){
    enqueueInstruction({'f', 160});
    enqueueInstruction({'p', 30});
    enqueueInstruction({'b', 160});
    enqueueInstruction({'p', 90});
    enqueueInstruction({'f', 160});
    enqueueInstruction({'r', 3.14/2});
    enqueueInstruction({'f', 37});
    enqueueInstruction({'r', 95*3.14/180});
    enqueueInstruction({'f', 160});
    enqueueInstruction({'e', 0});
}

void bonjour(){
    enqueueInstruction({'p', 0});
    enqueueInstruction({'p', 90});
}

void laDanseDuRobot(){
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
    enqueueInstruction({'a', 0});   
    carre();
    // allerRetour(60);
};