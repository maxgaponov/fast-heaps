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

int pop() {
    int res = INT_MAX;
    int i = -1;
    for (int j = 0; j < D; ++j) {
        res = (res > q[j] ? q[j] : res);
        i = (res == q[j] ? j : i);
    }
    size--;
    int val = q[size];
    q[size] = INT_MAX;
    while (1) {
        // __builtin_prefetch(&q[i * D*D + D + 1]);
        int chld = INT_MAX;
        int j = -1;
        for (int k = i * D + D; k < i * D + 2 * D; ++k) {
            chld = (chld > q[k] ? q[k] : chld);
            j = (chld == q[k] ? k : j);
        }
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
