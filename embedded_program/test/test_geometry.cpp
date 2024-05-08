#include "cinematic.h"
#include <cmath>
#include <assert.h>

void test_angle(void) {
    struct vector2 a = {100, 0};
    struct vector2 b = {0, 100};
    assert(angle(&a, &b) + M_PI_2 < 0.000001);
    assert(angle(&b, &a) - M_PI_2 < 0.000001);
}

void test_function(void) {
    struct vector2 path[2] = {
        {0, 0},
        {100, 0}
    };
    schedule_path(0, path, 2);
}

void runUnityTests(void) {
    test_function();
}

void setup(void) {
    runUnityTests();
}

void loop(void) {}