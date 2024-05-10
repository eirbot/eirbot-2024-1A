#include <SPI.h>

#include "task_queue.h"
#include "instruction.h"


struct instruction queue[MAX_QUEUE_SIZE]; // TODO : dynamic size
unsigned int tail_cursor = MAX_QUEUE_SIZE-1;
unsigned int head_cursor = MAX_QUEUE_SIZE-1;
char queue_empty = 1;
//Queue size = head_cursor + (-tail_cursor)%MAX_QUEUE_SIZE + 1

char isQueueEmpty()
{
    return queue_empty;
}

struct instruction dequeueInstruction()
{
    if (isQueueEmpty()) {
        struct instruction error_instruction = {'q', 0}; 
        return error_instruction;
    }
    struct instruction i = queue[head_cursor];
    if (head_cursor > 0)
        head_cursor--;
    else
        head_cursor = MAX_QUEUE_SIZE-1;
    
    if (head_cursor==tail_cursor)
        queue_empty = 1;
    return i;
}

void clearQueue() {
    tail_cursor = MAX_QUEUE_SIZE-1;
    head_cursor = MAX_QUEUE_SIZE-1;
    queue_empty = 1;
}

void raiseFullQueueError() {
    // TODO: define an error if the queue is full
}

void enqueueInstruction(struct instruction instrct)
{
    if (queue_empty || tail_cursor != head_cursor) {
        if (queue_empty)
            queue_empty = 0;
        queue[tail_cursor] = instrct;
        if (tail_cursor > 0)
            tail_cursor--;
        else
            tail_cursor = MAX_QUEUE_SIZE-1;
    } else
        raiseFullQueueError();
}

void pushInstruction(struct instruction instrct) {
    if (queue_empty || tail_cursor != head_cursor) {
        if (queue_empty)
            queue_empty = 0;
        if (head_cursor < MAX_QUEUE_SIZE - 1)
            queue[++head_cursor] = instrct;
        else
            queue[head_cursor = 0] = instrct;
    } else
        raiseFullQueueError();
}

void displayQueue() {
    if (isQueueEmpty()) {
        Serial.println("<empty queue>\n");
        return;
    }
    int i = head_cursor;
    int last_index = (tail_cursor < MAX_QUEUE_SIZE - 1) ? tail_cursor+1 : 0; 
    while (i != last_index) {
        displayInstruction(queue + i);
        i = (i-1)%MAX_QUEUE_SIZE;
    }
}