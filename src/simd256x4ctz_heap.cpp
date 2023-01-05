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
    __m256i v01 = _mm256_min_epi32(v0, v1);
    __m256i v23 = _mm256_min_epi32(v2, v3);
    __m256i v = _mm256_min_epi32(v01, v23);

    {
        __m256i v_p = _mm256_srli_si256(v, 4);
        v = _mm256_min_epi32(v, v_p);
    }
    {
        __m256i v_p = _mm256_srli_si256(v, 8);
        v = _mm256_min_epi32(v, v_p);
    }
    {
        __m256i v_p = _mm256_permute2x128_si256(v, v, 1);
        v = _mm256_min_epi32(v, v_p);
    }

    res = _mm256_extract_epi32(v, 0);
    __m256i res_vec = _mm256_set1_epi32(res);
    __m256i mask0 = _mm256_cmpeq_epi32(v0, res_vec);
    __m256i mask1 = _mm256_cmpeq_epi32(v1, res_vec);
    __m256i mask2 = _mm256_cmpeq_epi32(v2, res_vec);
    __m256i mask3 = _mm256_cmpeq_epi32(v3, res_vec);
    int int_mask = _mm256_movemask_ps((__m256) mask0) + 
                   (_mm256_movemask_ps((__m256) mask1) << 8) + 
                   (_mm256_movemask_ps((__m256) mask2) << 16) +
                   (_mm256_movemask_ps((__m256) mask3) << 24);
    idx = left_child + __builtin_ctz(int_mask);
}

#include "heap_template.cpp"
