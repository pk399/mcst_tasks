#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "bsort_mt.h"

// Number of elements in the array
const int N = 50000;

int cmp_int(const void* p, const void* q)
{
    const int* el1 = p;
    const int* el2 = q;

    return *el1 > *el2;
}

int main()
{
    srand(1337);

    int arr[N] = {};
    for (int i = 0; i < N; i++)
    {
        arr[i] = rand();
    }

    bsort_mt(arr, N, sizeof(int), &cmp_int);

    bool sorted = true;

    for (int i = 1; i < N; i++)
    {
        if (arr[i - 1] < arr[i]) sorted = false;
    }

    if (sorted) printf("Sorted!\n");
    else printf("NOT SORTED!!!\n");
}
