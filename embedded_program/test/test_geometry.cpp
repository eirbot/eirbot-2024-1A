#include "cinematic.h"
#include "task_queue.h"
#include <cmath>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <unity.h>

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

#define EPSILON 0.000001

void test_angle(void) {
    struct vector2 a = {100, 0};
    struct vector2 b = {0, 100};
    TEST_ASSERT_TRUE(angle(&a, &b) - M_PI_2 < EPSILON);
    TEST_ASSERT_TRUE(angle(&b, &a) + M_PI_2 < EPSILON);
    b = {100, 0};
    float flat_angle = angle(&a, &b);
    TEST_ASSERT_TRUE(flat_angle - M_PI < EPSILON || flat_angle + M_PI < EPSILON);
    a = {100, 0};
    b = {100, 100};
    TEST_ASSERT_TRUE(angle(&a, &b) - M_PI_4 < EPSILON);
    b = {-100, 100};
    TEST_ASSERT_TRUE(angle(&a, &b) - M_3PI_4 < EPSILON);

}

/**
 * @brief Test if the robot schedule an elementary forward for this path.
*/
void test_elementary_path(void) {
    struct vector2 path[2] = {
        {0, 0},
        {100, 0}
    };
    schedule_path(0, path, 2);
    struct instruction gotInstruction = dequeueInstruction(); 
    TEST_ASSERT_TRUE((gotInstruction.instruction_type == TRIG_ROTATE ||
        gotInstruction.instruction_type == NON_TRIG_ROTATE)
        && gotInstruction.value < EPSILON);
    gotInstruction = dequeueInstruction();
    TEST_ASSERT_TRUE(gotInstruction.instruction_type == FORWARD && gotInstruction.value - 100 < EPSILON);
}

/**
 * @brief Check if the robot make a backward move and a forward move for this elementary path
*/
void test_backward_path(void) {
    struct vector2 path[3] = {
        {0, 100},
        {0, 0},
        {100, 0}
    };
    schedule_path(M_PI_2, path, 3);
    struct instruction gotInstruction = dequeueInstruction(); 
    TEST_ASSERT_TRUE((gotInstruction.instruction_type == TRIG_ROTATE ||
        gotInstruction.instruction_type == NON_TRIG_ROTATE)
        && gotInstruction.value < EPSILON);
    gotInstruction = dequeueInstruction();
    TEST_ASSERT_TRUE(gotInstruction.instruction_type == BACKWARD && gotInstruction.value - 100 < EPSILON);
    gotInstruction = dequeueInstruction();
    TEST_ASSERT_TRUE(gotInstruction.instruction_type == NON_TRIG_ROTATE && gotInstruction.value - M_PI_2);
    gotInstruction = dequeueInstruction();
    TEST_ASSERT_TRUE(gotInstruction.instruction_type == FORWARD && gotInstruction.value - 100 < EPSILON);
}

void test_strategic_path(void) {
    #define SOLAR_PANEL_AXIS 200-175.2
    if (!isQueueEmpty())
        clearQueue();
    struct vector2 path[4] = {
        {300-13.570, 200-9.0554},
        {116.3, SOLAR_PANEL_AXIS},
    };
    float currentOrientation = schedule_path(0, path, 2);

    // TODO: slow down for solar panels

    path[0] = {116.3, SOLAR_PANEL_AXIS};
    path[1] = {282.5, SOLAR_PANEL_AXIS};
    currentOrientation = schedule_path(currentOrientation, path, 2);
    displayQueue();
    clearQueue();

}

void runUnityTests(void) {
    RUN_TEST(test_angle);
    RUN_TEST(test_elementary_path);
    RUN_TEST(test_strategic_path);
}

void setup(void) {
    Serial.begin(9600);
    UNITY_BEGIN();
    runUnityTests();
    UNITY_END();
}

void loop(void) {}