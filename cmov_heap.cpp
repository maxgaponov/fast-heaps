#ifndef PREFETCH_LEVEL
#define PREFETCH_LEVEL 3
#endif

#include "utils.cpp"

unsigned size = 0;
int* q;

void prepare(int N) {
    q = utils::allocate_aligned_heap<2>(N);
}

void push(int x) {
    utils::push<2>(q, x, size);
}

int pop() {
    int res = q[1];
    int val = q[size];
    q[size] = INT_MAX;
    size--;
    unsigned i = 1;
    while (1) {
        utils::prefetch<2>(q, i);
        if (2 * i > size) {
            q[i] = val;
            return res;
        }
        int c1 = q[i * 2];
        int c2 = q[i * 2 + 1];
        int min_val = (c1 < c2 ? c1 : c2);
        q[i] = min_val;
        i = 2 * i + (c1 > c2);
        if (min_val < val) {    
        } else {
            q[i >> 1] = val;
            return res;
        }
    }
}
