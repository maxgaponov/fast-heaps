#include <bits/stdc++.h>

int size = 0;
int* q;

void prepare(int N) {
    int _N = 1;
    while (_N <= N) _N *= 2;
    N = _N * 2;

    q = new (std::align_val_t(64)) int[N];
    for (int i = 0; i < N; ++i) {
        q[i] = INT_MAX;
    }
}

void push(int x) {
    int i = size;
    size++;
    while (i > 0 && q[(i - 1) / 2] > x) {
        q[i] = q[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    q[i] = x;
}

int pop() {
    int res = q[0];
    size--;
    int val = q[size];
    q[size] = INT_MAX;
    int i = 0;
    while (1) {
        // __builtin_prefetch(&q[i * 2 + 1]);
        int c1 = q[i * 2 + 1];
        int c2 = q[i * 2 + 2];
        q[i] = (c1 < c2 ? c1 : c2);
        if (q[i] < val) {
            i = 2 * i + (c1 < c2 ? 1 : 2);
        } else {
            q[i] = val;
            return res;
        }
        // int j = i * 2 + (q[i * 2 + 1] < q[i * 2 + 2] ? 1 : 2);
        // if (val > q[j]) {
        //     q[i] = q[j];
        //     i = j;
        // } else {
        //     break;
        // }
    }
    // q[i] = val;
    return res;
}
