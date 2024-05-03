#include "cinematic.h"
#include "task_queue.h"
#include "instruction.h"
#include <math.h>

/**
 * @brief Return a + b.
*/
struct vector2 vec__add(const struct vector2 *a, const struct vector2 *b)
{
    return {a->x + b->x, a->y + b->y};
}

/**
 * @brief Return -a.
*/
struct vector2 vec__opposite(const struct vector2 *a)
{
    return {-a->x, -a->y};
}

/**
 * @brief Return a - b.
*/
struct vector2 vec__minus(const struct vector2 *a, const struct vector2 *b)
{
    struct vector2 opposite = vec__opposite(b);
    return vec__add(a, &opposite);
}

/**
 * @brief Return the 2-norm of a.
*/
float vec__norm(const struct vector2 *a)
{
    int x = a->x;
    int y = a->y;
    return x*x + y*y;
}

float scalar_product(const struct vector2 *a, const struct vector2 *b)
{
    return a->x * b->x + a->y * b->y;
}

/**
 * @brief Return in radian the angle between a and b.
 * @details Return the radian angle that the robot must rotate by to be
 * directed according to b if it is currently directed according to a.  
*/
float angle(const struct vector2 *a, const struct vector2 *b)
{
    // TODO: check those calculus
    return acos(scalar_product(a, b)/(vec__norm(a)*vec__norm(b)));
}

void schedulePath(const struct vector2 positions[], unsigned int position_number)
{
    // TODO: optimize the path by rotating the less and scheduling forward
    // or backard moves according to the most quick rotation
    if (position_number < 2) return;
    struct vector2 currentPosition = positions[0];
    struct vector2 currentOrientation = vec__minus(positions + 1, positions);
    enqueueInstruction({ FORWARD, vec__norm(&currentOrientation)});
    for (unsigned int i = 1; i < position_number; ++i) {
        struct vector2 nextOrientation = vec__minus(positions + i, positions+i+1);
        float rotation = angle(&currentOrientation, &nextOrientation);
        enqueueInstruction({ (rotation > 0) ? TRIG_ROTATE: NON_TRIG_ROTATE,
        (rotation > 0) ? rotation : -rotation });
        enqueueInstruction({ FORWARD, vec__norm(&currentOrientation)});
        currentOrientation = nextOrientation;
    }
}