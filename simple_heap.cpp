#include <bits/stdc++.h>

unsigned size = 0;
int* q;

void prepare(int N) {
    int _N = 1;
    while (_N <= N) _N *= 2;
    N = _N * 2;

    q = new (std::align_val_t(64)) int[N];
    q[0] = INT_MIN;
    for (int i = 1; i < N; ++i) {
        q[i] = INT_MAX;
    }
}

void push(int x) {
    size++;
    unsigned i = size;
    while (q[i >> 1] > x) {
        q[i] = q[i >> 1];
        i >>= 1;
    }
    q[i] = x;
}

int pop() {
    int res = q[1];
    int val = q[size];
    q[size] = INT_MAX;
    size--;
    unsigned i = 1;
    while (1) {
        #if PREFETCH_LEVEL > 0
        __builtin_prefetch(&q[i * (1 << (PREFETCH_LEVEL + 1))]);
        #endif
        int c1 = q[i * 2];
        int c2 = q[i * 2 + 1];
        #ifdef WITH_BRANCH
        int min_val = c1;
        int next_i = 2 * i;
        if (c1 > c2) {
            min_val = c2;
            next_i++;
        }
        if (min_val < val) {
            q[i] = min_val;
            i = next_i;
        } else {
            break;
        }
        #else
        int min_val = (c1 < c2 ? c1 : c2);
        if (min_val < val) {
            q[i] = min_val;
            i = 2 * i + (c1 > c2);
        } else {
            break;
        }
        #endif
    }
    q[i] = val;
    return res;
}
