#include <x86intrin.h>

#ifndef PREFETCH_LEVEL
#define PREFETCH_LEVEL 1
#endif

#include "utils.cpp"

unsigned size = 0;
int* q;

const unsigned D = 4;

void prepare(int N) {
    q = utils::allocate_aligned_heap<D>(N);
}

void push(int x) {
    utils::push<D>(q, x, size);
}

inline void get_min(int* q, int& res, unsigned& idx) {
    __m128i v = _mm_load_si128 ((__m128i*) &q[0]);
    __m128i i = _mm_setr_epi32(0, 1, 2, 3);

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
    int res;
    unsigned i;
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
        if (i * D > size) {
            q[i] = val;
            return res;
        }
        utils::prefetch<D>(q, i);
        unsigned left_son = i * D;
        int min_val;
        unsigned next_i;
        get_min(q + left_son, min_val, next_i);
        q[i] = min_val;
        i = left_son + next_i;
        if (min_val < val) {
        } else {
            q[i / D] = val;
            return res;
        }
    }
}
