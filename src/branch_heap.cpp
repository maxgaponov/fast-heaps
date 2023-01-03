#ifndef PREFETCH_LEVEL
#define PREFETCH_LEVEL 3
#endif

const unsigned D = 2;

inline void goto_min(int* q, int& res, unsigned& idx) {
    int c0 = q[2 * idx];
    int c1 = q[2 * idx + 1];
    if (__builtin_expect(c0 <= c1, 1)) {
        res = c0;
        idx = 2 * idx;
    } else {
        res = c1;
        idx = 2 * idx + 1;
    }
}

#include "heap_template.cpp"
