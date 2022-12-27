#pragma GCC target("avx2")

#include <x86intrin.h>
#include <bits/stdc++.h>

unsigned size = 0;
int* q;

const unsigned D = 8;

void prepare(int N) {
    int _N = 1;
    while (_N <= N) _N *= D;
    N = _N * D;

    q = new (std::align_val_t(64)) int[N];
    q[0] = INT_MIN;
    for (int i = 1; i < N; ++i) {
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

inline void get_min(int* q, int& res, unsigned& idx) {
    __m128i v0 = _mm_load_si128 ((__m128i*) &q[0]);
    __m128i v1 = _mm_load_si128 ((__m128i*) &q[4]);
    
    __m128i i0 = _mm_setr_epi32(0, 1, 2, 3);
    __m128i i1 = _mm_setr_epi32(4, 5, 6, 7);
    
    __m128i mask = _mm_cmpgt_epi32(v0, v1);
    __m128i v = _mm_blendv_epi8(v0, v1, mask);
    __m128i i = _mm_blendv_epi8(i0, i1, mask);

    {
        __m128i v_p = _mm_srli_si128(v, 4);
        __m128i i_p = _mm_srli_si128(i, 4);
        __m128i mask = _mm_cmpgt_epi32(v, v_p);
        v = _mm_blendv_epi8(v, v_p, mask);
        i = _mm_blendv_epi8(i, i_p, mask);
    }
    {
        __m128i v_p = _mm_srli_si128(v, 8);
        __m128i i_p = _mm_srli_si128(i, 8);
        __m128i mask = _mm_cmpgt_epi32(v, v_p);
        v = _mm_blendv_epi8(v, v_p, mask);
        i = _mm_blendv_epi8(i, i_p, mask);
    }

    res = _mm_extract_epi32(v, 0);
    idx = _mm_extract_epi32(i, 0);
}

int pop() {
    int res = INT_MAX;
    unsigned i = 0;
    q[0] = INT_MAX;
    get_min(q, res, i);
    q[0] = INT_MIN;
    
    int val = q[size];
    q[size] = INT_MAX;
    size--;
    if (i == size + 1) {
        return res;
    }
    while (1) {
        unsigned left_son = i * D;
        int min_val = INT_MAX;
        unsigned next_i = 0;
        get_min(q + left_son, min_val, next_i);
        if (min_val < val) {
            q[i] = min_val;
            i = left_son + next_i;
        } else {
            break;
        }
    }
    q[i] = val;
    return res;
}
