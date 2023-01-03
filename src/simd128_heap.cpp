#include <x86intrin.h>

#ifndef PREFETCH_LEVEL
#define PREFETCH_LEVEL 1
#endif

const unsigned D = 4;

inline void goto_min(int* q, int& res, unsigned& idx) {
    unsigned left_child = idx * D;
    __m128i v = _mm_load_si128 ((__m128i*) &q[left_child]);
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
    idx = left_child + _mm_extract_epi32(i, 0);
}

#include "heap_template.cpp"
