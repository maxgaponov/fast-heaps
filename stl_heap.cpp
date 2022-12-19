#include <bits/stdc++.h>

using namespace std;

priority_queue<int> q;

void prepare(int N) {
}

void push(int x) {
    q.push(-x);
}

int pop() {
    int res = q.top();
    q.pop();
    return -res;
}
