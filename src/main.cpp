#include <bits/stdc++.h>

void prepare(int N);
void push(int x);
int pop();

const int MAX_VAL = 1'000'000'000;
std::mt19937 rnd(42);

void benchmark(int N, int Q) {
    prepare(N);

    std::vector<double> elapsed(Q);
    std::vector<int> queries(N);
    int checksum = 0;
    for (int i = -2; i < Q; ++i) {
        for (int i = 0; i < N; ++i) {
            queries[i] = rnd() % MAX_VAL;
        }
        std::clock_t start = clock();
        for (int i = 0; i < N; ++i) {
            push(queries[i]);
        }
        for (int i = 0; i < N; ++i) {
            checksum ^= pop() + i;
        }
        double elapsed_i = double(clock() - start);
        if (i >= 0) {
            elapsed[i] = elapsed_i;
        }
    }
    std::sort(elapsed.begin(), elapsed.end());
    double elapsed_sec = elapsed[elapsed.size() / 2] / CLOCKS_PER_SEC;
    double latency_ns = elapsed_sec * 1e9 / N;
    printf("checksum: %d\n", checksum);
    printf("latency: %.2f\n", latency_ns);
}

int main(int argc, char** argv) {
    assert(argc == 3);
    int N = atoi(argv[1]);
    int Q = atoi(argv[2]);

    benchmark(N, Q);
    
    return 0;
}
