// Implementation of multi-threaded bubble sort

#include <pthread.h>
#include <stddef.h>
#include "bsort.h"

#include "bsort_mt.h"

const int THREADS = 8;

// Constructs a new void* based on index and element size
static inline void* _idx(void* p, size_t el_sz, int idx)
{
    return (void*) ( (char*) p + el_sz*idx );
}

// Get size of nth partition
// n is in [0, (THREADS * 2)]
static inline size_t _psz(size_t arr_sz, int n)
{
    const int t = THREADS * 2;

    if (n < t)
    {
        return arr_sz / (t + 1);
    }
    else
    {
        return arr_sz / (t + 1) + arr_sz % (t + 1);
    }
}

// Get pointer to nth partition
// n is in [0, (THREADS * 2)]
static inline void* _pptr(void* arr, size_t arr_sz, size_t el_sz, int n)
{
    int virt_el_sz = el_sz * _psz(arr_sz, 0);

    return _idx(arr, virt_el_sz, n);
}

struct _arg
{
    void* p;
    size_t n;
    size_t el_sz;
    int (*cmp)(const void* lhs, const void* rhs);  
};

static void* _bsort_wrapper(void* arg)
{
    struct _arg* a = arg;

    bsort(a->p, a->n, a->el_sz, a->cmp);

    return NULL;
}


void bsort_mt(void* p, size_t n, size_t el_sz,
           int (*cmp)(const void* lhs, const void* rhs))
{
    // If an array is too small, use
    // the single-threaded version
    if (n < 2 * (THREADS + 1))
    {
        bsort(p, n, el_sz, cmp);
        return;
    }

    pthread_t threads[THREADS] = {};
    struct _arg args[THREADS] = {};

    for (int i = 0; i < THREADS * 2 + 2; i++)
    {
        int shift = i % 2;
        for (int j = 0; j < THREADS; j++)
        {
            int pnum = j * 2 + shift;

            struct _arg* a = &args[j];
            a->p = _pptr(p, n, el_sz, pnum);
            a->n = _psz(n, pnum) + _psz(n, pnum + 1);
            a->el_sz = el_sz;
            a->cmp = cmp;

            pthread_create(&threads[j], NULL, _bsort_wrapper, a);
        }

        for (int j = 0; j < THREADS; j++)
        {
            pthread_join(threads[j], NULL);
        }
    } 
}
