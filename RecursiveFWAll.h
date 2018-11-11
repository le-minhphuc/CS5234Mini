#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;

#include "constants.h"

/*
 * Size of (sub)matrix A: dm x dp
 * Size of (sub)matrix B: dm x dn
 * Size of (sub)matrix C: dn x dp
 * */
void FWR_All(long long* A, long long* B, long long* C, const long long N,
        const long long dm, const long long dn, const long long dp) {
    //get cache size
    long long memSize = (dm*dp + dm*dn + dn*dp)*(sizeof(long long));
    if (memSize <= L1_CACHE_SIZE) {
        // implement iterative version
        for (long long k = 0; k < dn; k++) {
            for (long long i = 0; i < dm; i++) {
                for (long long j = 0; j < dp; j++) {
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
 * Size of (sub)matrix A: dm x dp
 * Size of (sub)matrix B: dm x dn
 * Size of (sub)matrix C: dn x dp
 * */
inline void FWR_AllInt(int * A, int * B, int * C, const int N,
        const int dm, const int dn, const int dp) {
    //get cache size
    long long memSize = (dm*dp + dm*dn + dn*dp)*(sizeof(int));
    if (memSize <= (long long)L1_CACHE_SIZE) {
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
        FWR_AllInt(A,B,C,N,dm/2,dn/2,dp/2); //A11,B11,C11
        
        FWR_AllInt(A+dp/2,B,C+dp/2,N,dm/2,dn/2,dp-dp/2); //A12,B11,C12
        
        FWR_AllInt(A+dm/2*N,B+dm/2*N,C,N,dm-dm/2,dn/2,dp/2); //A21,B21,C11
        
        FWR_AllInt(A+(dm/2)*N+(dp/2),B+(dm/2)*N,C+dp/2,N,dm-dm/2,dn/2,dp-dp/2); //A22,B21,C12
        
        FWR_AllInt(A+(dm/2)*N+(dp/2),B+(dm/2)*N+(dn/2),C+(dn/2)*N+(dp/2),N,dm-dm/2,dn-dn/2,dp-dp/2); //A22,B22,C22
        
        FWR_AllInt(A+(dm/2)*N,B+(dm/2)*N+(dn/2),C+(dn/2)*N,N,dm-dm/2,dn-dn/2,dp/2); //A21,B22,C21
        
        FWR_AllInt(A+dp/2,B+dn/2,C+(dn/2)*N+(dp/2),N,dm/2,dn-dn/2,dp-dp/2); //A12,B12,C22
        
        FWR_AllInt(A,B+dn/2,C+(dn/2)*N,N,dm/2,dn-dn/2,dp/2); //A11,B12,C21
    }
}
