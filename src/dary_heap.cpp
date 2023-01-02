#ifndef BRANCHING_FACTOR
#define BRANCHING_FACTOR 4
#endif

#ifndef PREFETCH_LEVEL
#define PREFETCH_LEVEL 1
#endif

const unsigned D = BRANCHING_FACTOR;

inline void get_min(int* q, int& res, unsigned& idx) {
    res = q[0];
    for (unsigned i = 1; i < D; ++i) {
        int val = q[i];
        res = (res < val ? res : val);
    }
    for (unsigned i = 0; i < D; ++i) {
        idx = (q[i] == res ? i : idx);
    }
}

#include "heap_template.cpp"
