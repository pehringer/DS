#include "DS_Queue.h"

struct DS_Queue* DS_QueueAlloc(int size, int capacity) {
    struct DS_Queue *q = malloc(sizeof(struct DS_Queue) + capacity * size);
    if(q == 0) {
        return 0;
    }
    q->back = -size;
    q->capacity = capacity;
    q->front = 0;
    q->length = 0;
    q->size = size;
    q->wrap = capacity * size;
    return q;
}

void DS_QueueDealloc(struct DS_Queue *q) {
    free(q);
}

struct DS_Queue* DS_QueueRealloc(struct DS_Queue *q, int capacity) {
    // Shift elements so front is zeroth element.
    void *start = (void*) (q + 1);
    void *middle = (void*) (q + 1) + q->front;
    void *end = (void*) (q + 1) + q->wrap;
    void *next = middle;
    while(start != next) {
        // XOR swap elements. Increment start and next.
        for(int byte = 0; byte < q->size; byte++) {
            *((char*) start) = *((char*) start) ^ *((char*) next);
            *((char*) next) = *((char*) start) ^ *((char*) next);
            *((char*) start) = *((char*) start) ^ *((char*) next);
            start++;
            next++;
        }
        // Shift logic.
        if(next == end) {
            next = middle;
        } else if(start == middle) {
            middle = next;
        }
    }
    // Now reallocate queue.
    q = realloc(q, sizeof(struct DS_Queue) + capacity * q->size);
    if(q == 0) {
        return 0;
    }
    q->capacity = capacity;
    q->front = 0;
    if(q->length > capacity) {
        q->length = capacity;
    }
    q->back = (q->length - 1) * q->size;
    q->wrap = capacity * q->size;
    return q;
}

void* DS_QueueBack(struct DS_Queue *q, void *destination) {
    //REMOVE if block to remove out of bounds check.
    if(q->length == 0) {
        return 0;
    }
    // ^^^^^^^^
    memcpy(destination, (void*) (q + 1) + q->back, q->size);
    return destination;
}

int DS_QueueCap(struct DS_Queue *q) {
    return q->capacity;
}

int DS_QueueEmpty(struct DS_Queue *q) {
    return q->length == 0;
}

void* DS_QueueFront(struct DS_Queue *q, void *destination) {
    //REMOVE if block to remove out of bounds check.
    if(q->length == 0) {
        return 0;
    }
    // ^^^^^^^^
    memcpy(destination, (void*) (q + 1) + q->front, q->size);
    return destination;
}

int DS_QueueFull(struct DS_Queue *q) {
    return q->length == q->capacity;
}

int DS_QueueLen(struct DS_Queue *q) {
    return q->length;
}

void* DS_QueuePop(struct DS_Queue *q, void *destination) {
    //REMOVE if block to remove out of bounds check.
    if(q->length == 0) {
        return 0;
    }
    // ^^^^^^^^
    memcpy(destination, (void*) (q + 1) + q->front, q->size);
    q->front += q->size;
    if(q->front == q->wrap) {
        q->front = 0;
    }
    q->length--;
    return destination;
}

struct DS_Queue* DS_QueuePush(struct DS_Queue *q, void *source) {
    // REMOVE if block to remove auto reallocation.
    if(q->length == q->capacity) {
        q = DS_QueueRealloc(q, q->length * 2);
    }
    // REMOVE ^^^^^^^^
    q->back += q->size;
    if(q->back == q->wrap) {
        q->back = 0;
    }
    q->length++;
    memcpy((void*) (q + 1) + q->back, source, q->size);
    return q;
}
