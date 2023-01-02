#ifndef PREFETCH_LEVEL
#define PREFETCH_LEVEL 3
#endif

const unsigned D = 2;

inline void get_min(int* q, int& res, unsigned& idx) {
    if (__builtin_expect(q[0] <= q[1], 1)) {
        res = q[0];
        idx = 0;
    } else {
        res = q[1];
        idx = 1;
    }
}

#include "heap_template.cpp"
