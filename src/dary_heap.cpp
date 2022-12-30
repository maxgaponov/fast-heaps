#ifndef BRANCHING_FACTOR
#define BRANCHING_FACTOR 4
#endif

#ifndef PREFETCH_LEVEL
#define PREFETCH_LEVEL 1
#endif

#include "utils.cpp"

unsigned size = 0;
int* q;

const unsigned D = BRANCHING_FACTOR;

void prepare(int N) {
    q = utils::allocate_aligned_heap<D>(N);
}

void push(int x) {
    utils::push<D>(q, x, size);
}

int pop() {
    int res = INT_MAX;
    for (unsigned j = 1; j < D; ++j) {
        int val = q[j];
        res = (res < val ? res : val);
    }
    unsigned i = 0;
    for (unsigned j = 1; j < D; ++j) {
        i = (q[j] == res ? j : i);
    }
    int val = q[size];
    q[size] = INT_MAX;
    size--;
    if (i == size + 1) {
        return res;
    }
    while (1) {
        if (i * D > size) {
            q[i] = val;
            return res;
        }
        utils::prefetch<D>(q, i);
        unsigned left_son = i * D;
        int min_val = INT_MAX;
        for (unsigned j = 0; j < D; ++j) {
            int val = q[left_son + j];
            min_val = (min_val < val ? min_val : val);
        }
        q[i] = min_val;
        for (unsigned j = 0; j < D; ++j) {
            i = (q[left_son + j] == min_val ? left_son + j : i);
        }
        if (min_val < val) {
        } else {
            q[i / D] = val;
            return res;
        }
    }
}
