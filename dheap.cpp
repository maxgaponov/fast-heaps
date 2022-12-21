#include <bits/stdc++.h>

unsigned size = 0;
int* q;

const unsigned D = 4;

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
        __builtin_prefetch(&q[i * D * D]);
        unsigned left_son = i * D;
        int min_val = INT_MAX;
        for (unsigned j = 0; j < D; ++j) {
            int val = q[left_son + j];
            min_val = (min_val < val ? min_val : val);
        }
        if (min_val < val) {
            q[i] = min_val;
            for (unsigned j = 0; j < D; ++j) {
                i = (q[left_son + j] == min_val ? left_son + j : i);
            }
        } else {
            break;
        }
    }
    q[i] = val;
    return res;
}
