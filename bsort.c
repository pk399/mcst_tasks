// Implementation of bubble sort

#include <stddef.h>

#include "bsort.h"

void _swapmem(void* pp1, void* pp2, size_t sz)
{
    char* p1 = pp1;
    char* p2 = pp2;

    for (int i = 0; i < sz; i++, p1++, p2++)
    {
        char t = *p1;
        *p1 = *p2;
        *p2 = t;
    }
}

// Constructs a new void* based on index and element size
void* _idx(void* p, size_t el_sz, int idx)
{
    return (void*) ( (char*) p + el_sz*idx );
}


void bsort(void* p, size_t n, size_t el_sz,
           int (*cmp)(const void* lhs, const void* rhs))
{
    if (n <= 1) return; // Nothing to do

    for (int i = 0; i < (n - 1); i++)
    {
        for (int j = 1; j < (n - i); j++)
        {
            void* el1 = _idx(p, el_sz, j);
            void* el2 = _idx(p, el_sz, j - 1);

            if ( cmp(el1, el2) > 0 )
            {
                _swapmem(el1, el2, el_sz);
            }
        }
    }
}
