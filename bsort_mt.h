#ifndef BSORT_MT_H
#define BSORT_MT_H

// Bubble sort algorithm, multithreaded

#include <stddef.h>

void bsort_mt(void* arr, size_t n, size_t elem_sz, 
           int (*cmp)(const void* lhs, const void* rhs));

#endif // BSORT_MT_H
