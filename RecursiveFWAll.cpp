#include <algorithm>
#include <chrono>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <random>
using namespace std;

const int L1_CACHE_SIZE = 32768;
const int N = 8192;
int dAll[N][N];

/*
 * Size of (sub)matrix A: dm x dp
 * Size of (sub)matrix B: dm x dn
 * Size of (sub)matrix C: dn x dp
 * */
void FWR_All(int* A, int* B, int* C, const int N,
        const int dm, const int dn, const int dp) {
    //get cache size
    long memSize = ((long)dm*(long)dp + (long)dm*(long)dn + (long)dn*(long)dp)*(sizeof(int));
    if (memSize <= (long)L1_CACHE_SIZE) {
        // implement iterative version
        for (int k = 0; k < dn; k++) {
            for (int i = 0; i < dm; i++) {
                for (int j = 0; j < dp; j++) {
                    *(A+(i*N+j)) = min(*(A+(i*N+j)),
                            *(B+(i*N+k)) + *(C+(k*N+j)));
                }
            }
        }
    } else {
        // recurse
        FWR_All(A,B,C,N,dm/2,dn/2,dp/2); //A11,B11,C11
        
        FWR_All(A+dp/2,B,C+dp/2,N,dm/2,dn/2,dp-dp/2); //A12,B11,C12
        
        FWR_All(A+dm/2*N,B+dm/2*N,C,N,dm-dm/2,dn/2,dp/2); //A21,B21,C11
        
        FWR_All(A+(dm/2)*N+(dp/2),B+(dm/2)*N,C+dp/2,N,dm-dm/2,dn/2,dp-dp/2); //A22,B21,C12
        
        FWR_All(A+(dm/2)*N+(dp/2),B+(dm/2)*N+(dn/2),C+(dn/2)*N+(dp/2),N,dm-dm/2,dn-dn/2,dp-dp/2); //A22,B22,C22
        
        FWR_All(A+(dm/2)*N,B+(dm/2)*N+(dn/2),C+(dn/2)*N,N,dm-dm/2,dn-dn/2,dp/2); //A21,B22,C21
        
        FWR_All(A+dp/2,B+dn/2,C+(dn/2)*N+(dp/2),N,dm/2,dn-dn/2,dp-dp/2); //A12,B12,C22
        
        FWR_All(A,B+dn/2,C+(dn/2)*N,N,dm/2,dn-dn/2,dp/2); //A11,B12,C21
    }
}

int main() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dAll[i][j] = rng()%(1000000); //might change to all 1 to easier check correctness
        }
    }

    cout << "Finish generating random array" << endl;

    clock_t begin_time = clock();
    FWR_All((int *)dAll,(int *)dAll,(int *)dAll,N,N,N,N);
    clock_t end_time = clock();
    double elapsed_secs = double(end_time - begin_time) / CLOCKS_PER_SEC;
    cout << "Recursive Floyd-Warshall (Flexible version) takes " << elapsed_secs << " seconds!" << endl;
    return 0;
}
