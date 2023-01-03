#include <bits/stdc++.h>

unsigned size = 0;
int* q;

void prepare(int N) {
    int _N = 1;
    while (_N <= N) _N *= D;
    _N *= D;

    q = new (std::align_val_t(64)) int[_N];
    q[0] = INT_MIN;
    for (int i = 1; i < _N; ++i) {
        q[i] = INT_MAX;
    }
}

void push(int x) {
    size++;
    unsigned i = size;
    while (q[i / D] > x) {
        q[i] = q[i / D];
        i /= D;
    }
    q[i] = x;
}

int pop() {
    int res;
    unsigned i = 0;
    q[0] = INT_MAX;
    goto_min(q, res, i);
    q[0] = INT_MIN;
    
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
        #if PREFETCH_LEVEL == 1
        __builtin_prefetch(&q[i * D * D]);
        #elif PREFETCH_LEVEL == 2
        __builtin_prefetch(&q[i * D * D * D]);
        #elif PREFETCH_LEVEL == 3
        __builtin_prefetch(&q[i * D * D * D * D]);
        #elif PREFETCH_LEVEL == 4
        __builtin_prefetch(&q[i * D * D * D * D * D]);
        #elif PREFETCH_LEVEL == 5
        __builtin_prefetch(&q[i * D * D * D * D * D * D]);
        #endif
        goto_min(q, q[i], i);
        if (q[i] < val) {
        } else {
            q[i / D] = val;
            return res;
        }
    }
}
