#pragma GCC target("avx2")

#include <x86intrin.h>

#ifndef PREFETCH_LEVEL
#define PREFETCH_LEVEL 0
#endif

const unsigned D = 32;

inline void goto_min(int* q, int& res, unsigned& idx) {
    unsigned left_child = idx * D;
    __m256i v0 = _mm256_load_si256((__m256i*) &q[left_child]);
    __m256i v1 = _mm256_load_si256((__m256i*) &q[left_child + 8]);
    __m256i v2 = _mm256_load_si256((__m256i*) &q[left_child + 16]);
    __m256i v3 = _mm256_load_si256((__m256i*) &q[left_child + 24]);
    
    __m256i i0 = _mm256_setr_epi32(0, 1, 2, 3, 4, 5, 6, 7);
    __m256i i1 = _mm256_setr_epi32(8, 9, 10, 11, 12, 13, 14, 15);
    __m256i i2 = _mm256_setr_epi32(16, 17, 18, 19, 20, 21, 22, 23);
    __m256i i3 = _mm256_setr_epi32(24, 25, 26, 27, 28, 29, 30, 31);

    __m256i mask01 = _mm256_cmpgt_epi32(v0, v1);
    __m256i v01 = _mm256_blendv_epi8(v0, v1, mask01);
    __m256i i01 = _mm256_blendv_epi8(i0, i1, mask01);

    __m256i mask23 = _mm256_cmpgt_epi32(v2, v3);
    __m256i v23 = _mm256_blendv_epi8(v2, v3, mask23);
    __m256i i23 = _mm256_blendv_epi8(i2, i3, mask23);

    __m256i mask = _mm256_cmpgt_epi32(v01, v23);
    __m256i v = _mm256_blendv_epi8(v01, v23, mask);
    __m256i i = _mm256_blendv_epi8(i01, i23, mask);

    {
        __m256i v_p = _mm256_srli_si256(v, 4);
        __m256i i_p = _mm256_srli_si256(i, 4);
        __m256i mask = _mm256_cmpgt_epi32(v, v_p);
        v = _mm256_blendv_epi8(v, v_p, mask);
        i = _mm256_blendv_epi8(i, i_p, mask);
    }
    {
        __m256i v_p = _mm256_srli_si256(v, 8);
        __m256i i_p = _mm256_srli_si256(i, 8);
        __m256i mask = _mm256_cmpgt_epi32(v, v_p);
        v = _mm256_blendv_epi8(v, v_p, mask);
        i = _mm256_blendv_epi8(i, i_p, mask);
    }
    {
        __m256i v_p = _mm256_permute2x128_si256(v, v, 1);
        __m256i i_p = _mm256_permute2x128_si256(i, i, 1);
        __m256i mask = _mm256_cmpgt_epi32(v, v_p);
        v = _mm256_blendv_epi8(v, v_p, mask);
        i = _mm256_blendv_epi8(i, i_p, mask);
    }

    res = _mm256_extract_epi32(v, 0);
    idx = left_child + _mm256_extract_epi32(i, 0);
}

#include "heap_template.cpp"
