#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;

#include "constants.h"

/*
A, B, C are square (sub)matrix with size s x s,
N is size of original FW matrix.
*/
void FWR(long long* A, long long* B, long long* C, const long long N, const long long s) {
    //get cache size
    long long memSize = (3*s*s)*(sizeof(long long));
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

/*
A, B, C are square (sub)matrix with size s x s,
N is size of original FW matrix.
*/
void FWRInt(int * A, int * B, int* C, const int N, const int s) {
    //get cache size
    long long memSize = (3*s*s)*(sizeof(int));
    if (memSize <= (long long)L1_CACHE_SIZE) {
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
        FWRInt(A,B,C,N,s/2); //A11,B11,C11
        
        FWRInt(A+s/2,B,C+s/2,N,s/2); //A12,B11,C12
        
        FWRInt(A+s/2*N,B+s/2*N,C,N,s/2); //A21,B21,C11
        
        FWRInt(A+s/2*N+s/2,B+(s/2)*N,C+s/2,N,s/2); //A22,B21,C12
        
        FWRInt(A+(s/2)*N+s/2,B+(s/2)*N+s/2,C+(s/2)*N+s/2,N,s/2); //A22,B22,C22
        
        FWRInt(A+(s/2)*N,B+(s/2)*N+s/2,C+(s/2)*N,N,s/2); //A21,B22,C21
        
        FWRInt(A+s/2,B+s/2,C+(s/2)*N+s/2,N,s/2); //A12,B12,C22
        
        FWRInt(A,B+s/2,C+(s/2)*N,N,s/2); //A11,B12,C21
    }
}