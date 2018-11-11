#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <ctime>
#include <algorithm>
#include <random>
using namespace std;

#include "constants.h"

static const int N = 4096;
long long d[N][N], dAll[N][N], test[N][N];

/*
 * Size of (sub)matrix A: dm x dp
 * Size of (sub)matrix B: dm x dn
 * Size of (sub)matrix C: dn x dp
 * */
void FWR_All(long long * A, long long * B, long long * C, const int N,
        const int dm, const int dn, const int dp) {
    //get cache size
    int memSize = (dm*dp + dm*dn + dn*dp)*(sizeof(long long));
    if (memSize <= L1_CACHE_SIZE) {
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

/*
A, B, C are square (sub)matrix with size s x s,
N is size of original FW matrix.
*/
void FWR(long long* A, long long* B, long long* C, const int N, const int s) {
    //get cache size
    int memSize = (3*s*s)*(sizeof(long long));
    if (memSize <= L1_CACHE_SIZE) {
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

void FW(long long test[N][N]) {
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
    //srand(time(NULL));
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            d[i][j] = (long long)rng(); //might change to all 1 to easier check correctness
            dAll[i][j] = d[i][j]; //for testing against flexible FWR implementation
            test[i][j] = d[i][j]; //for testing against classic implementation
        }
    }
    
    cout << "Finish generating random array" << endl;
    
    clock_t begin_time = clock();
    FWR((long long *)d,(long long *)d,(long long *)d,N,N);
    clock_t end_time = clock();
    double elapsed_secs = double(end_time - begin_time) / CLOCKS_PER_SEC;
    cout << "Recursive Floyd-Warshall takes " << elapsed_secs << " seconds!" << endl;
    
    begin_time = clock();
    FWR_All((long long *)dAll,(long long *)dAll,(long long *)dAll,N,N,N,N);
    end_time = clock();
    elapsed_secs = double(end_time - begin_time) / CLOCKS_PER_SEC;
    cout << "Recursive Floyd-Warshall (Flexible version) takes " << elapsed_secs << " seconds!" << endl;
    
    begin_time = clock();
    FW(test);
    end_time = clock();
    elapsed_secs = double(end_time - begin_time) / CLOCKS_PER_SEC;
    cout << "Classical Floyd-Warshall takes " << elapsed_secs << " second!" << endl;
    
    // checking correctness
    bool flag = true; //check for correctness of FWR
    bool flagAll = true; //check for correctness of FWR_All
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (test[i][j] != d[i][j]) {
                cout << "Inconsistent result detected for FWR!" << endl;
                cout << "test[" << i << "][" << j << "] = " << test[i][j] << endl;
                cout << "d[" << i << "][" << j << "] = " << d[i][j] << endl;
                flag = false;
                break;
            }
            if (test[i][j] != dAll[i][j]) {
                cout << "Inconsistent result detected for FWR_All!" << endl;
                cout << "test[" << i << "][" << j << "] = " << test[i][j] << endl;
                cout << "dAll[" << i << "][" << j << "] = " << dAll[i][j] << endl;
                flagAll = false;
                break;
            }
        }
        if (!flag) break;
        if (!flagAll) break;
    }
    if (flag && flagAll) cout << "All good!" << endl;
    else if (flagAll) cout << "FWR have problem" << endl;
    else cout << "FWR (Flexible) have problem!" << endl;
    return 0;
}
