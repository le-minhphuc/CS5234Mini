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

void FWR(int* A, int* B, int* C, 
        const int N, const int s) {
    //get cache size
    long memSize = (3*(long)s*(long)s)*(sizeof(int));
    if (memSize <= (long)L1_CACHE_SIZE) {
        // implement iterative version
        for (int k = 0; k < s; k++) {
            for (int i = 0; i < s; i++) {
                for (int j = 0; j < s; j++) {
                    *(A+(i*N+j)) = min(*(A+(i*N+j)),
                            *(B+(i*N+k)) + *(C+(k*N+j)));
                }
            }
        }
    } else {
        // recurse
        FWR(A,B,C,N,s/2); //A11,B11,C11
        
        FWR(A+s/2,B,C+s/2,N,s/2); //A12,B11,C12
        
        FWR(A+s/2*N,B+s/2*N,C,N,s/2); //A21,B21,C11
        
        FWR(A+s/2*N+s/2,B+(s/2)*N,C+s/2,N,s/2); //A22,B21,C12
        
        FWR(A+(s/2)*N+s/2,B+(s/2)*N+s/2,C+(s/2)*N+s/2,N,s/2); //A22,B22,C22
        
        FWR(A+(s/2)*N,B+(s/2)*N+s/2,C+(s/2)*N,N,s/2); //A21,B22,C21
        
        FWR(A+s/2,B+s/2,C+(s/2)*N+s/2,N,s/2); //A12,B12,C22
        
        FWR(A,B+s/2,C+(s/2)*N,N,s/2); //A11,B12,C21
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
    FWR((int *)d,(int *)d,(int *)d,N,N);
    clock_t end_time = clock();
    double elapsed_secs = double(end_time - begin_time) / CLOCKS_PER_SEC;
    cout << "Recursive Floyd-Warshall takes " << elapsed_secs << " seconds!" << endl;
    return 0;
}
