#include "CDS_Array.h"

struct CDS_Array* CDS_ArrayConstruct(struct CDS_Array *a, int size, int length) {
    a->first = malloc(size * length);
    if(a->first == 0) {
        return 0;
    }
    a->length = length;
    a->size = size;
    return a;
}

struct CDS_Array* CDS_ArrayResize(struct CDS_Array *a, int length) {
    a->first = realloc(a->first, a->size * length);
    if(a->first == 0) {
      return 0;
    }
    a->length = length;
    return a;
}

struct CDS_Array* CDS_ArrayDestruct(struct CDS_Array *a) {
    free(a->first);
    a->first = 0;
    a->length = 0;
    a->size = 0;
    return a;
}

struct CDS_Array* CDS_ArrayFromArray(struct CDS_Array *a, int index, void *array, int length) {
    memcpy(a->first + a->size * index, array, a->size * length);
    return a;
}

struct CDS_Array* CDS_ArrayToArray(struct CDS_Array *a, int index, void *array, int length) {
    memcpy(array, a->first + a->size * index, a->size * length);
    return a;
}

struct CDS_Array* CDS_ArrayFill(struct CDS_Array *a, int index, void *value, int length) {
    void *element = a->first + a->size * index;
    while(length > 0) {
        memcpy(element, value, a->size);
        element += a->size;
        length--;
    }
    return a;

}

int CDS_ArrayLength(struct CDS_Array *a) {
    return a->length;
}

void* CDS_ArrayAt(struct CDS_Array *a, int index) {
    return a->first + a->size * index;
}

int CDS_ArrayFirstIndexOf(struct CDS_Array *a, int index, void *value, int (*compare)(const void*, const void*)) {
    void *element = a->first + a->size * index;
    while(index < a->length) {
        if(compare(element, value) == 0) {
            return index;
        }
        element += a->size;
        index++;
    }
    return -1;
}

int CDS_ArrayLastIndexOf(struct CDS_Array *a, int index, void *value, int (*compare)(const void*, const void*)) {
    void *element = a->first + a->size * index;
    while(index >= 0) {
        if(compare(element, value) == 0) {
            return index;
        }
        element -= a->size;
        index--;
    }
    return -1;
}

struct CDS_Array* CDS_ArraySort(struct CDS_Array *a, int (*compare)(const void*, const void*)) {
    qsort(a->first, a->length, a->size, compare);
    return a;
}

int CDS_ArrayBinarySearch(struct CDS_Array *a, void *value, int (*compare)(const void*, const void*)) {
    value = bsearch(value, a->first, a->length, a->size, compare);
    if(value > 0) {
        return (value - a->first) / a->size;
    }
    return -1;
}