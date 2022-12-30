#include <bits/stdc++.h>

namespace utils {

template<unsigned T>
inline int* allocate_aligned_heap(int N) {
    int _N = 1;
    while (_N <= N) _N *= T;
    _N *= T;

    int* q = new (std::align_val_t(64)) int[_N];
    q[0] = INT_MIN;
    for (int i = 1; i < _N; ++i) {
        q[i] = INT_MAX;
    }
    return q;
}

template<unsigned T>
inline void push(int* q, int x, unsigned& size) {
    size++;
    unsigned i = size;
    while (q[i / T] > x) {
        q[i] = q[i / T];
        i /= T;
    }
    q[i] = x;
}

template<unsigned T>
inline void prefetch(int* q, unsigned i) {
    #if PREFETCH_LEVEL == 1
    __builtin_prefetch(&q[i * T * T]);
    #elif PREFETCH_LEVEL == 2
    __builtin_prefetch(&q[i * T * T * T]);
    #elif PREFETCH_LEVEL == 3
    __builtin_prefetch(&q[i * T * T * T * T]);
    #elif PREFETCH_LEVEL == 4
    __builtin_prefetch(&q[i * T * T * T * T * T]);
    #elif PREFETCH_LEVEL == 5
    __builtin_prefetch(&q[i * T * T * T * T * T * T]);
    #endif
}

}
