#ifndef BSORT_H
#define BSORT_H

// Bubble sort algorithm

#include <stddef.h>

void bsort(void* arr, size_t n, size_t elem_sz, 
           int (*cmp)(const void* lhs, const void* rhs));

#endif // BSORT_H
