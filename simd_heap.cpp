#pragma GCC target("avx2")

#include <x86intrin.h>
#include <bits/stdc++.h>

int size = 0;
int* q;

const int D = 8;

void prepare(int N) {
    int _N = 1;
    while (_N <= N) _N *= D;
    N = _N * D;

    q = new (std::align_val_t(64)) int[N];
    for (int i = 0; i < N; ++i) {
        q[i] = INT_MAX;
    }
}

void push(int x) {
    int i = size;
    size++;
    while (i >= D && q[(i - D) / D] > x) {
        q[i] = q[(i - D) / D];
        i = (i - D) / D;
    }
    q[i] = x;
}

inline void get_min(int* q, int& res, int& idx) {
    __m256i v = _mm256_load_si256((__m256i*) &q[0]);
    __m256i i = _mm256_setr_epi32(0, 1, 2, 3, 4, 5, 6, 7);

    __m256i p[3] = {
        _mm256_setr_epi32(1, 2, 3, 4, 5, 6, 7, 0),
        _mm256_setr_epi32(2, 0, 1, 3, 6, 4, 5, 7),
        _mm256_setr_epi32(4, 0, 1, 2, 3, 5, 6, 7)
    };
    
    for (int iter = 0; iter < 3; ++iter) {
        __m256i v_p = _mm256_permutevar8x32_epi32(v, p[iter]);
        __m256i i_p = _mm256_permutevar8x32_epi32(i, p[iter]);
        __m256i mask = _mm256_cmpgt_epi32(v, v_p);
        v = _mm256_blendv_epi8(v, v_p, mask);
        i = _mm256_blendv_epi8(i, i_p, mask);
    }

    res = _mm256_extract_epi32(v, 0);
    idx = _mm256_extract_epi32(i, 0);
}

int pop() {
    int res = INT_MAX;
    int i = -1;
    get_min(q, res, i);
    size--;
    int val = q[size];
    q[size] = INT_MAX;
    while (1) {
        int chld = INT_MAX;
        int j = -1;
        get_min(q + i * D + D, chld, j);
        j += i * D + D;
        if (val > q[j]) {
            q[i] = q[j];
            i = j;
        } else {
            break;
        }
    }
    q[i] = val;
    return res;
}
