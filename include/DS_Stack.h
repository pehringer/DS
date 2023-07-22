#ifndef DS_STACK_H
#define DS_STACK_H

#include <stdlib.h>
#include <string.h>

/*
Memory Allocation Format
========================

+-------+ <-- Header is located at the start of the allocation (pointer to
|DS     |     struct is retured by construct and restruct functions).
|Struct |
|       |
+-------+ <-- Data is located after header in the allocation.
|Index 0|
+-------+
|Index 1|
+-------+
|Index 2|
+-------+
|Index 3|
+-------+
| ...   |
+-------+
|Index N|
+-------+

*/

struct DS_Stack {
    int capacity;
    int length;
    size_t size;
    int top;
};

struct DS_Stack* DS_StackConstruct(int size, int capacity);

void DS_StackDestruct(struct DS_Stack *s);

struct DS_Stack* DS_StackRestruct(struct DS_Stack *s, int capacity);

int DS_StackCap(struct DS_Stack *s);

int DS_StackEmpty(struct DS_Stack *s);

int DS_StackFull(struct DS_Stack *s);

int DS_StackLen(struct DS_Stack *s);

void* DS_StackPop(struct DS_Stack *s, void *destination);

struct DS_Stack* DS_StackPush(struct DS_Stack *s, void *source);

void* DS_StackTop(struct DS_Stack *s, void *destination);

#endif
