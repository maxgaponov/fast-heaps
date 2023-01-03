#ifndef BRANCHING_FACTOR
#define BRANCHING_FACTOR 4
#endif

#ifndef PREFETCH_LEVEL
#define PREFETCH_LEVEL 1
#endif

const unsigned D = BRANCHING_FACTOR;

inline void goto_min(int* q, int& res, unsigned& idx) {
    unsigned left_child = idx * D;
    res = q[left_child];
    for (unsigned i = left_child + 1; i < left_child + D; ++i) {
        int val = q[i];
        res = (res < val ? res : val);
    }
    for (unsigned i = left_child; i < left_child + D; ++i) {
        idx = (q[i] == res ? i : idx);
    }
}

#include "heap_template.cpp"
