#include "SPI.h"
#include "cinematic.h"
#include "task_queue.h"

void test_function(void) {
    struct vector2 path[2] = {
        {0, 0},
        {100, 0}
    };
    schedule_path(0, path, 2);
    displayQueue();
}

void runUnityTests(void) {
    test_function();
}

void setup() {
    delay(2000);
    runUnityTests();
}

void loop() {};