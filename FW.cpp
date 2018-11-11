#include <algorithm>
#include <chrono>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <random>
using namespace std;

const int L1_CACHE_SIZE = 32768;
const int N = 8192;
//const int INF = 1e9;
int d[N][N];

void FW(int test[N][N]) {
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                test[i][j] = min(test[i][j],
                        test[i][k] + test[k][j]);
            }
        }
    }
}

int main() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            d[i][j] = rng()%(1000000); //might change to all 1 to easier check correctness
        }
    }

    cout << "Finish generating random array" << endl;

    clock_t begin_time = clock();
    FW(d);
    clock_t end_time = clock();
    double elapsed_secs = double(end_time - begin_time) / CLOCKS_PER_SEC;
    cout << "Classical Floyd-Warshall takes " << elapsed_secs << " second!" << endl;
    return 0;
}
