#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <random>
using namespace std;

const int L1_CACHE_SIZE = 32768;
const int N = 4096;
int d[N][N];

void FWR(int* A, int* B, int* C, const int s) {
    //get cache size
    if (3*s*s*(sizeof(int)) <= L1_CACHE_SIZE) {
        //implement iterative version
        for (int k = 0; k < s; k++) {
            for (int i = 0; i < s; i++) {
                for (int j = 0; j < s; j++) {
                    *(A+(i*N+j)) = min(*(A+(i*N+j)),
                            *(B+(i*N+k))+*(C+(k*N+j)));
                }
            }
        }
    } else {
        FWR(A,B,C,s/2);
        FWR(A+s/2,B,C+s/2,s/2);
        FWR(A+(s/2)*N,B+(s/2)*N,C,s/2);
        FWR(A+(s/2)*N+(s/2),B+(s/2)*N,C+s/2,s/2);
        FWR(A+(s/2)*N+s/2,B+(s/2)*N+s/2,C+(s/2)*N+s/2,s/2);
        FWR(A+(s/2)*N,B+(s/2)*N+s/2,C+(s/2)*N,s/2);
        FWR(A+s/2,B+s/2,C+(s/2)*N+s/2,s/2);
        FWR(A,B+s/2,C+(s/2)*N,s/2);
    }
}

int main() {
    //srand(time(NULL));
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            d[i][j] = rng()%1000000;
        }
    }
    cout << "Finish generating random array" << endl;
    clock_t begin_time = clock();
    FWR((int *)d,(int *)d,(int *)d,N);
    clock_t end_time = clock();
    double elapsed_secs = double(end_time - begin_time) / CLOCKS_PER_SEC;
    cout << "Recursive Floyd Warshall takes " << elapsed_secs << " seconds!" << endl;
}
