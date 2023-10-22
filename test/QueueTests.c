#include "Test.h"
#include "DS_Queue.h"

int QueChk(struct DS_Queue *que, size_t size, int len, int cap) {
    int failed = 0;
    if(que->capacity != cap) failed++;
    if(que->length != len) failed++;
    if(que->size != size) failed++;
    return failed;
}

int NewDeleteZero() {
    int failed = 0;
    struct DS_Queue *que = DS_QueueAllocate(64, 0);
    if(que == 0) return ++failed;
    failed += QueChk(que, 64, 0, 0);
    DS_QueueDeallocate(que);
    return failed;
}

int NewDeleteMany() {
    int failed = 0;
    struct DS_Queue *que = DS_QueueAllocate(64, 4);
    if(que == 0) return ++failed;
    failed += QueChk(que, 64, 0, 4);
    *((int*) (que + 1) + 0) = 0;
    *((int*) (que + 1) + 1) = 1;
    *((int*) (que + 1) + 2) = 2;
    *((int*) (que + 1) + 3) = 3;
    DS_QueueDeallocate(que);
    return failed;
}

int ResizeBiggerEmpty() {
    int failed = 0;
    struct DS_Queue *que = DS_QueueAllocate(sizeof(int), 0);
    que = DS_QueueReallocate(que, 4);
    if(que == 0) return ++failed;
    failed += QueChk(que, sizeof(int), 0, 4);
    *((int*) (que + 1) + 0) = 0;
    *((int*) (que + 1) + 1) = 1;
    *((int*) (que + 1) + 2) = 2;
    *((int*) (que + 1) + 3) = 3;
    que = DS_QueueReallocate(que, 8);
    if(que == 0) return ++failed;
    failed += QueChk(que, sizeof(int), 0, 8);
    *((int*) (que + 1) + 4) = 4;
    *((int*) (que + 1) + 5) = 5;
    *((int*) (que + 1) + 6) = 6;
    *((int*) (que + 1) + 7) = 7;
    if(*((int*) (que + 1) + 0) != 0) failed++;
    if(*((int*) (que + 1) + 1) != 1) failed++;
    if(*((int*) (que + 1) + 2) != 2) failed++;
    if(*((int*) (que + 1) + 3) != 3) failed++;
    if(*((int*) (que + 1) + 4) != 4) failed++;
    if(*((int*) (que + 1) + 5) != 5) failed++;
    if(*((int*) (que + 1) + 6) != 6) failed++;
    if(*((int*) (que + 1) + 7) != 7) failed++;
    DS_QueueDeallocate(que);
    return failed;
}

int ResizeSmallerEmpty() {
    int failed = 0;
    struct DS_Queue *que = DS_QueueAllocate(sizeof(int), 8);
    *((int*) (que + 1) + 0) = 0;
    *((int*) (que + 1) + 1) = 1;
    *((int*) (que + 1) + 2) = 2;
    *((int*) (que + 1) + 3) = 3;
    *((int*) (que + 1) + 4) = 4;
    *((int*) (que + 1) + 5) = 5;
    *((int*) (que + 1) + 6) = 6;
    *((int*) (que + 1) + 7) = 7;
    que = DS_QueueReallocate(que, 4);
    if(que == 0) failed++;
    failed += QueChk(que, sizeof(int), 0, 4);
    if(*((int*) (que + 1) + 0) != 0) failed++;
    if(*((int*) (que + 1) + 1) != 1) failed++;
    if(*((int*) (que + 1) + 2) != 2) failed++;
    if(*((int*) (que + 1) + 3) != 3) failed++;
    que = DS_QueueReallocate(que, 0);
    if(que == 0) return ++failed;
    failed += QueChk(que, sizeof(int), 0, 0);
    DS_QueueDeallocate(que);
    return failed;
}

int PushFrontBackPop() {
    int val, failed = 0;
    struct DS_Queue *que = DS_QueueAllocate(sizeof(int), 4);
    val = 1;
    DS_QueuePush(que, &val);
    if(*((int*) DS_QueueFront(que, &val)) != 1) failed++;
    if(*((int*) DS_QueueBack(que, &val)) != 1) failed++;
    val = 2;
    DS_QueuePush(que, &val);
    if(*((int*) DS_QueueFront(que, &val)) != 1) failed++;
    if(*((int*) DS_QueueBack(que, &val)) != 2) failed++;
    val = 3;
    DS_QueuePush(que, &val);
    if(*((int*) DS_QueueFront(que, &val)) != 1) failed++;
    if(*((int*) DS_QueueBack(que, &val)) != 3) failed++;
    val = 4;
    DS_QueuePush(que, &val);
    if(*((int*) DS_QueueFront(que, &val)) != 1) failed++;
    if(*((int*) DS_QueueBack(que, &val)) != 4) failed++;
    if(*((int*) DS_QueuePop(que, &val)) != 1) failed++;
    if(*((int*) DS_QueueFront(que, &val)) != 2) failed++;
    if(*((int*) DS_QueueBack(que, &val)) != 4) failed++;
    if(*((int*) DS_QueuePop(que, &val)) != 2) failed++;
    if(*((int*) DS_QueueFront(que, &val)) != 3) failed++;
    if(*((int*) DS_QueueBack(que, &val)) != 4) failed++;
    val = 5;
    DS_QueuePush(que, &val);
    if(*((int*) DS_QueueFront(que, &val)) != 3) failed++;
    if(*((int*) DS_QueueBack(que, &val)) != 5) failed++;
    val = 6;
    DS_QueuePush(que, &val);
    if(*((int*) DS_QueueFront(que, &val)) != 3) failed++;
    if(*((int*) DS_QueueBack(que, &val)) != 6) failed++;
    if(*((int*) DS_QueuePop(que, &val)) != 3) failed++;
    if(*((int*) DS_QueueFront(que, &val)) != 4) failed++;
    if(*((int*) DS_QueueBack(que, &val)) != 6) failed++;
    if(*((int*) DS_QueuePop(que, &val)) != 4) failed++;
    if(*((int*) DS_QueueFront(que, &val)) != 5) failed++;
    if(*((int*) DS_QueueBack(que, &val)) != 6) failed++;
    if(*((int*) DS_QueuePop(que, &val)) != 5) failed++;
    if(*((int*) DS_QueueFront(que, &val)) != 6) failed++;
    if(*((int*) DS_QueueBack(que, &val)) != 6) failed++;
    if(*((int*) DS_QueuePop(que, &val)) != 6) failed++;
    failed += QueChk(que, sizeof(int), 0, 4);
    DS_QueueDeallocate(que);
    return failed;
}

int Capacity() {
    int failed = 0;
    struct DS_Queue *que = DS_QueueAllocate(sizeof(int), 0);
    if(DS_QueueCapacity(que) != 0) failed++;
    failed += QueChk(que, sizeof(int), 0, 0);
    que = DS_QueueReallocate(que, 4);
    if(DS_QueueCapacity(que) != 4) failed++;
    failed += QueChk(que, sizeof(int), 0, 4);
    que = DS_QueueReallocate(que, 8);
    if(DS_QueueCapacity(que) != 8) failed++;
    failed += QueChk(que, sizeof(int), 0, 8);
    DS_QueueDeallocate(que);
    return failed;
}

int Empty() {
    int val, failed = 0;
    struct DS_Queue *que = DS_QueueAllocate(sizeof(int), 4);
    if(DS_QueueEmpty(que) == 0) failed++;
    val = 42;
    DS_QueuePush(que, &val);
    if(DS_QueueEmpty(que) != 0) failed++;
    DS_QueuePush(que, &val);
    if(DS_QueueEmpty(que) != 0) failed++;
    DS_QueuePush(que, &val);
    if(DS_QueueEmpty(que) != 0) failed++;
    DS_QueuePush(que, &val);
    if(DS_QueueEmpty(que) != 0) failed++;
    DS_QueuePop(que, &val);
    if(DS_QueueEmpty(que) != 0) failed++;
    DS_QueuePop(que, &val);
    if(DS_QueueEmpty(que) != 0) failed++;
    DS_QueuePop(que, &val);
    if(DS_QueueEmpty(que) != 0) failed++;
    DS_QueuePop(que, &val);
    if(DS_QueueEmpty(que) == 0) failed++;
    DS_QueuePush(que, &val);
    if(DS_QueueEmpty(que) != 0) failed++;
    DS_QueuePush(que, &val);
    if(DS_QueueEmpty(que) != 0) failed++;
    DS_QueuePop(que, &val);
    if(DS_QueueEmpty(que) != 0) failed++;
    DS_QueuePop(que, &val);
    if(DS_QueueEmpty(que) == 0) failed++;
    failed += QueChk(que, sizeof(int), 0, 4);
    DS_QueueDeallocate(que);
    return failed;
}

int Full() {
    int val, failed = 0;
    struct DS_Queue *que = DS_QueueAllocate(sizeof(int), 4);
    if(DS_QueueFull(que) != 0) failed++;
    val = 42;
    DS_QueuePush(que, &val);
    if(DS_QueueFull(que) != 0) failed++;
    DS_QueuePush(que, &val);
    if(DS_QueueFull(que) != 0) failed++;
    DS_QueuePush(que, &val);
    if(DS_QueueFull(que) != 0) failed++;
    DS_QueuePush(que, &val);
    if(DS_QueueFull(que) == 0) failed++;
    DS_QueuePop(que, &val);
    if(DS_QueueFull(que) != 0) failed++;
    DS_QueuePop(que, &val);
    if(DS_QueueFull(que) != 0) failed++;
    DS_QueuePop(que, &val);
    if(DS_QueueFull(que) != 0) failed++;
    DS_QueuePop(que, &val);
    if(DS_QueueFull(que) != 0) failed++;
    DS_QueuePush(que, &val);
    if(DS_QueueFull(que) != 0) failed++;
    DS_QueuePush(que, &val);
    if(DS_QueueFull(que) != 0) failed++;
    DS_QueuePop(que, &val);
    if(DS_QueueFull(que) != 0) failed++;
    DS_QueuePop(que, &val);
    if(DS_QueueFull(que) != 0) failed++;
    DS_QueuePush(que, &val);
    if(DS_QueueFull(que) != 0) failed++;
    DS_QueuePush(que, &val);
    if(DS_QueueFull(que) != 0) failed++;
    DS_QueuePush(que, &val);
    if(DS_QueueFull(que) != 0) failed++;
    DS_QueuePush(que, &val);
    if(DS_QueueFull(que) == 0) failed++;
    failed += QueChk(que, sizeof(int), 4, 4);
    DS_QueueDeallocate(que);
    return failed;
}

int Length() {
    int val, failed = 0;
    struct DS_Queue *que = DS_QueueAllocate(sizeof(int), 4);
    if(DS_QueueLength(que) != 0) failed++;
    val = 42;
    DS_QueuePush(que, &val);
    if(DS_QueueLength(que) != 1) failed++;
    DS_QueuePush(que, &val);
    if(DS_QueueLength(que) != 2) failed++;
    DS_QueuePush(que, &val);
    if(DS_QueueLength(que) != 3) failed++;
    DS_QueuePush(que, &val);
    if(DS_QueueLength(que) != 4) failed++;
    DS_QueuePop(que, &val);
    if(DS_QueueLength(que) != 3) failed++;
    DS_QueuePop(que, &val);
    if(DS_QueueLength(que) != 2) failed++;
    DS_QueuePush(que, &val);
    if(DS_QueueLength(que) != 3) failed++;
    DS_QueuePush(que, &val);
    if(DS_QueueLength(que) != 4) failed++;
    DS_QueuePop(que, &val);
    if(DS_QueueLength(que) != 3) failed++;
    DS_QueuePop(que, &val);
    if(DS_QueueLength(que) != 2) failed++;
    DS_QueuePop(que, &val);
    if(DS_QueueLength(que) != 1) failed++;
    DS_QueuePop(que, &val);
    if(DS_QueueLength(que) != 0) failed++;
    failed += QueChk(que, sizeof(int), 0, 4);
    DS_QueueDeallocate(que);
    return failed;
}

int ResizeBiggerFull() {
    int val, failed = 0;
    struct DS_Queue *que = DS_QueueAllocate(sizeof(int), 0);
    que = DS_QueueReallocate(que, 2);
    if(que == 0) return ++failed;
    failed += QueChk(que, sizeof(int), 0, 2);
    val = 0;
    DS_QueuePush(que, &val);
    val = 1;
    DS_QueuePush(que, &val);
    que = DS_QueueReallocate(que, 4);
    if(que == 0) return ++failed;
    failed += QueChk(que, sizeof(int), 2, 4);
    val = 2;
    DS_QueuePush(que, &val);
    val = 3;
    DS_QueuePush(que, &val);
    if(*((int*) DS_QueuePop(que, &val)) != 0) failed++;
    if(*((int*) DS_QueuePop(que, &val)) != 1) failed++;
    val = 4;
    DS_QueuePush(que, &val);
    val = 5;
    DS_QueuePush(que, &val);
    que = DS_QueueReallocate(que, 6);
    if(que == 0) return ++failed;
    failed += QueChk(que, sizeof(int), 4, 6);
    val = 6;
    DS_QueuePush(que, &val);
    val = 7;
    DS_QueuePush(que, &val);
    if(*((int*) DS_QueuePop(que, &val)) != 2) failed++;
    if(*((int*) DS_QueuePop(que, &val)) != 3) failed++;
    val = 8;
    DS_QueuePush(que, &val);
    val = 9;
    DS_QueuePush(que, &val);
    if(*((int*) DS_QueuePop(que, &val)) != 4) failed++;
    if(*((int*) DS_QueuePop(que, &val)) != 5) failed++;
    if(*((int*) DS_QueuePop(que, &val)) != 6) failed++;
    if(*((int*) DS_QueuePop(que, &val)) != 7) failed++;
    if(*((int*) DS_QueuePop(que, &val)) != 8) failed++;
    if(*((int*) DS_QueuePop(que, &val)) != 9) failed++;
    failed += QueChk(que, sizeof(int), 0, 6);
    DS_QueueDeallocate(que);
    return failed;
}

int ResizeSmallerFull() {
    int val, failed = 0;
    struct DS_Queue *que = DS_QueueAllocate(sizeof(int), 6);
    if(que == 0) return failed++;
    failed += QueChk(que, sizeof(int), 0, 6);
    val = 0;
    DS_QueuePush(que, &val);
    val = 1;
    DS_QueuePush(que, &val);
    if(*((int*) DS_QueuePop(que, &val)) != 0) failed++;
    if(*((int*) DS_QueuePop(que, &val)) != 1) failed++;
    val = 2;
    DS_QueuePush(que, &val);
    val = 3;
    DS_QueuePush(que, &val);
    val = 4;
    DS_QueuePush(que, &val);
    val = 5;
    DS_QueuePush(que, &val);
    val = 6;
    DS_QueuePush(que, &val);
    val = 7;
    DS_QueuePush(que, &val);
    que = DS_QueueReallocate(que, 4);
    if(que == 0) return failed++;
    failed += QueChk(que, sizeof(int), 4, 4);
    if(*((int*) DS_QueuePop(que, &val)) != 2) failed++;
    if(*((int*) DS_QueuePop(que, &val)) != 3) failed++;
    if(*((int*) DS_QueuePop(que, &val)) != 4) failed++;
    if(*((int*) DS_QueuePop(que, &val)) != 5) failed++;
    val = 8;
    DS_QueuePush(que, &val);
    val = 9;
    DS_QueuePush(que, &val);
    if(*((int*) DS_QueuePop(que, &val)) != 8) failed++;
    if(*((int*) DS_QueuePop(que, &val)) != 9) failed++;
    val = 10;
    DS_QueuePush(que, &val);
    val = 11;
    DS_QueuePush(que, &val);
    val = 12;
    DS_QueuePush(que, &val);
    val = 13;
    DS_QueuePush(que, &val);
    que = DS_QueueReallocate(que, 2);
    if(que == 0) return failed++;
    failed += QueChk(que, sizeof(int), 2, 2);
    if(*((int*) DS_QueuePop(que, &val)) != 10) failed++;
    if(*((int*) DS_QueuePop(que, &val)) != 11) failed++;
    val = 14;
    DS_QueuePush(que, &val);
    val = 15;
    DS_QueuePush(que, &val);
    que = DS_QueueReallocate(que, 0);
    if(que == 0) return failed++;
    failed += QueChk(que, sizeof(int), 0, 0);
    DS_QueueDeallocate(que);
    return failed;
}

int ResizeHalfFullBigger() {
    int val, failed = 0;
    struct DS_Queue *que = DS_QueueAllocate(sizeof(int), 0);
    que = DS_QueueReallocate(que, 2);
    if(que == 0) return ++failed;
    failed += QueChk(que, sizeof(int), 0, 2);
    val = 0;
    DS_QueuePush(que, &val);
    que = DS_QueueReallocate(que, 4);
    if(que == 0) return ++failed;
    failed += QueChk(que, sizeof(int), 1, 4);
    val = 1;
    DS_QueuePush(que, &val);
    val = 2;
    DS_QueuePush(que, &val);
    if(*((int*) DS_QueuePop(que, &val)) != 0) failed++;
    if(*((int*) DS_QueuePop(que, &val)) != 1) failed++;
    val = 3;
    DS_QueuePush(que, &val);
    que = DS_QueueReallocate(que, 6);
    if(que == 0) return ++failed;
    failed += QueChk(que, sizeof(int), 2, 6);
    val = 4;
    DS_QueuePush(que, &val);
    val = 5;
    DS_QueuePush(que, &val);
    if(*((int*) DS_QueuePop(que, &val)) != 2) failed++;
    que = DS_QueueReallocate(que, 8);
    if(que == 0) return ++failed;
    failed += QueChk(que, sizeof(int), 3, 8);
    if(*((int*) DS_QueuePop(que, &val)) != 3) failed++;
    if(*((int*) DS_QueuePop(que, &val)) != 4) failed++;
    if(*((int*) DS_QueuePop(que, &val)) != 5) failed++;
    failed += QueChk(que, sizeof(int), 0, 8);
    DS_QueueDeallocate(que);
    return failed;
}

int ResizeHalfFullSmaller() {
    int val, failed = 0;
    struct DS_Queue *que = DS_QueueAllocate(sizeof(int), 6);
    if(que == 0) return failed++;
    failed += QueChk(que, sizeof(int), 0, 6);
    val = 0;
    DS_QueuePush(que, &val);
    val = 1;
    DS_QueuePush(que, &val);
    if(*((int*) DS_QueuePop(que, &val)) != 0) failed++;
    if(*((int*) DS_QueuePop(que, &val)) != 1) failed++;
    val = 2;
    DS_QueuePush(que, &val);
    val = 3;
    DS_QueuePush(que, &val);
    val = 4;
    DS_QueuePush(que, &val);
    que = DS_QueueReallocate(que, 4);
    if(que == 0) return failed++;
    failed += QueChk(que, sizeof(int), 3, 4);
    if(*((int*) DS_QueuePop(que, &val)) != 2) failed++;
    if(*((int*) DS_QueuePop(que, &val)) != 3) failed++;
    if(*((int*) DS_QueuePop(que, &val)) != 4) failed++;
    val = 8;
    DS_QueuePush(que, &val);
    val = 9;
    DS_QueuePush(que, &val);
    val = 10;
    DS_QueuePush(que, &val);
    if(*((int*) DS_QueuePop(que, &val)) != 8) failed++;
    if(*((int*) DS_QueuePop(que, &val)) != 9) failed++;
    if(*((int*) DS_QueuePop(que, &val)) != 10) failed++;
    val = 11;
    DS_QueuePush(que, &val);
    val = 12;
    DS_QueuePush(que, &val);
    que = DS_QueueReallocate(que, 2);
    if(que == 0) return failed++;
    failed += QueChk(que, sizeof(int), 2, 2);
    if(*((int*) DS_QueuePop(que, &val)) != 11) failed++;
    if(*((int*) DS_QueuePop(que, &val)) != 12) failed++;
    val = 14;
    DS_QueuePush(que, &val);
    que = DS_QueueReallocate(que, 0);
    if(que == 0) return failed++;
    failed += QueChk(que, sizeof(int), 0, 0);
    DS_QueueDeallocate(que);
    return failed;
}

int main() {
    RunTests(13, (struct Test[13]) {
        (struct Test) {NewDeleteZero, "NewDeleteZero"},
        (struct Test) {NewDeleteMany, "NewDeleteMany"},
        (struct Test) {ResizeBiggerEmpty, "ResizeBiggerEmpty"},
        (struct Test) {ResizeSmallerEmpty, "ResizeSmallerEmpty"},
        (struct Test) {PushFrontBackPop, "PushFrontBackPop"},
        (struct Test) {Capacity, "Capacity"},
        (struct Test) {Empty, "Empty"},
        (struct Test) {Full, "Full"},
        (struct Test) {Length, "Length"},
        (struct Test) {ResizeBiggerFull, "ResizeBiggerFull"},
        (struct Test) {ResizeSmallerFull, "ResizeSmallerFull"},
        (struct Test) {ResizeHalfFullBigger, "ResizeHalfFullBigger"},
        (struct Test) {ResizeHalfFullSmaller, "ResizeHalfFullSmaller"},
    });
}
