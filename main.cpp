#include <bits/stdc++.h>

void prepare(int N);
void push(int x);
int pop();

const int MAX_VAL = 1'000'000;
std::mt19937 rnd(42);

void benchmark(int N, int Q) {
    prepare(N);

    for (int i = 0; i < N; ++i) {
        int x = rnd() % MAX_VAL;
        #ifdef DEBUG
        std::cerr << "push " << x << std::endl;
        #endif
        push(x);
    }

    std::vector<int> q(Q);
    for (int i = 0; i < Q; ++i) {
        q[i] = rnd() % MAX_VAL;
    }

    std::clock_t start = clock();
    int checksum = 0;
    for (int i = 0; i < Q; ++i) {
        int val = pop();
        #ifdef DEBUG
        std::cerr << "pop " << val << std::endl;
        std::cerr << "push " << q[i] << std::endl;
        #endif
        checksum ^= val;
        push(q[i]);
    }

    double elapsed_sec = double(clock() - start) / CLOCKS_PER_SEC;
    double latency_ns = elapsed_sec * 1e9 / Q;
    printf("checksum: %d\n", checksum);
    printf("latency: %.2f\n", latency_ns);
}

void example() {
    prepare(5);
    push(2);
    push(3);
    printf("%d ", pop());
    push(1);
    printf("%d ", pop());
}

int main(int argc, char** argv) {
    // example();
    // return 0;

    assert(argc == 3);
    int N = atoi(argv[1]);
    int Q = atoi(argv[2]);
    
    benchmark(N, Q);
    
    return 0;
}
