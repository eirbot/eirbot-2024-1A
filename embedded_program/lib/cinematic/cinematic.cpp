#include "cinematic.h"
#include "task_queue.h"
#include "instruction.h"
#include <math.h>

#define YES 1
#define NO 0

struct vector2 RIGHT = {1, 0};

/**
 * @brief Return a + b.
*/
struct vector2 vec__add(const struct vector2 *a, const struct vector2 *b)
{
    return {a->x + b->x, a->y + b->y};
}

vector2 vec_from_arg(float argument, float norm)
{
    return {norm*cosf(argument), norm*sinf(argument)};
}

/**
 * @brief Return -a.
*/
struct vector2 vec__opposite(const struct vector2 *a)
{
    return {-a->x, -a->y};
}

struct vector2 vec__minus(const struct vector2 *a, const struct vector2 *b)
{
    struct vector2 opposite = vec__opposite(b);
    return vec__add(a, &opposite);
}

float vec__magnitude(const struct vector2 *a)
{
    int x = a->x;
    int y = a->y;
    return sqrtf(x*x + y*y);
}

float scalar_product(const struct vector2 *a, const struct vector2 *b)
{
    return a->x * b->x + a->y * b->y;
}

float cross_product(const struct vector2 *a, const struct vector2 *b)
{
    return a->x*b->y - a->y*b->x;
}

float angle(const struct vector2 *a, const struct vector2 *b)
{
    float angle = acosf(fmaxf(-1, fminf(1, scalar_product(a, b)/(vec__magnitude(a)*vec__magnitude(b))))); 
    return (cross_product(a, b) > 0) ? angle : -angle;
}

float angle__add(float angle1, float angle2)
{
    float new_rotation = angle1 + angle2;
    if (new_rotation > M_PI)
        return new_rotation - M_TWOPI;
    if (new_rotation < -M_PI)
        return new_rotation + M_TWOPI;
    return new_rotation;
}

float opposite_angle(float rotation_angle)
{
    if (rotation_angle > 0)
        return rotation_angle - M_PI;
    return rotation_angle + M_PI;
}

void enqueueMove(float rotation_angle, const struct vector2 *nextMoveVec, int must_forward) {
    // TODO: check if a null rotation has not to be enqueue
    enqueueInstruction({ (rotation_angle > 0) ? TRIG_ROTATE: NON_TRIG_ROTATE,
        (rotation_angle > 0) ? rotation_angle : -rotation_angle });
    enqueueInstruction({ must_forward ? FORWARD : BACKWARD, vec__magnitude(nextMoveVec)/10});
}

float schedule_path(float currentOrientation, const struct vector2 positions[], unsigned int position_number)
{
    if (position_number < 2) return currentOrientation;
    struct vector2 currentPosition = positions[0];
    struct vector2 currentOrientationVec = {cos(currentOrientation), sin(currentOrientation)};
    int should_forward = YES;
    for (unsigned int i = 0; i < position_number - 2; ++i) {
        currentPosition = positions[i];
        struct vector2 nextPosition = positions[i + 1];
        struct vector2 nextOrientation = vec__minus(&nextPosition, &currentPosition);
        float rotation = angle(&currentOrientationVec, &nextOrientation);
        if (fabsf(rotation) > M_PI_2) {
            rotation = opposite_angle(rotation);
            should_forward = NO;
        } else {
            should_forward = YES;
        }
        enqueueMove(rotation, &nextOrientation, should_forward);
        currentOrientationVec = should_forward ? nextOrientation : vec__opposite(&nextOrientation);
    }
    // force good orientation for the final position
    struct vector2 finalOrientationVec = vec__minus(positions + position_number - 1, positions + position_number - 2); 
    float lastRotation = angle(&currentOrientationVec, &finalOrientationVec);
    enqueueMove(lastRotation, &finalOrientationVec, YES);
    return angle(&RIGHT, &finalOrientationVec);
}