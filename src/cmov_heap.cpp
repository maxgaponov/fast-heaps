#ifndef PREFETCH_LEVEL
#define PREFETCH_LEVEL 3
#endif

const unsigned D = 2;

inline void get_min(int* q, int& res, unsigned& idx) {
    res = (q[0] <= q[1] ? q[0] : q[1]);
    idx = q[0] > q[1];
}

#include "heap_template.cpp"
