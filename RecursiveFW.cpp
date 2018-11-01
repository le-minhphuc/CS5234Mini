#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <ctime>
#include <algorithm>
using namespace std;

const int L1_CACHE_SIZE = 32768;
//const int N = 16384; //set this to be power of 2
const int N = 4096;
//vector<vector<int>> d;
int d[N][N];

void FWR(int* A, int* B, int* C, const int s) {
    //get cache size
    if (3*s*s*(sizeof(int)) <= L1_CACHE_SIZE) {
        // implement iterative version
        for (int k = 0; k < s; k++) {
            for (int i = 0; i < s; i++) {
                for (int j = 0; j < s; j++) {
                    *(A+(i*N+j)) = min(*(A+(i*N+j)),
                            *(B+(i*N+k)) + *(C+(k*N+j)));
                }
            }
        }
        //cout << "Weww" << endl;
    } else {
        // recurse
        FWR(A,B,C,s/2); //A11,B11,C11
        //cout << "A11,B11,C11" << endl;
        FWR(A+s/2,B,C+s/2,s/2); //A12,B11,C12
        //cout << "A12,B11,C12" << endl;
        FWR(A+s/2*N,B+s/2*N,C,s/2); //A21,B21,C11
        //cout << "A21,B21,C11" << endl;
        FWR(A+s/2*N+s/2,B+(s/2)*N,C+s/2,s/2); //A22,B21,C12
        //cout << "A22,B21,C12" << endl;
        FWR(A+(s/2)*N+s/2,B+(s/2)*N+s/2,C+(s/2)*N+s/2,s/2); //A22,B22,C22
        //cout << "A22,B22,C22" << endl;
        FWR(A+(s/2)*N,B+(s/2)*N+s/2,C+(s/2)*N,s/2); //A21,B22,C21
        //cout << "A21,B22,C21" << endl;
        FWR(A+s/2,B+s/2,C+(s/2)*N+s/2,s/2); //A12,B12,C22
        //cout << "A12,B12,C22" << endl;
        FWR(A,B+s/2,C+(s/2)*N,s/2); //A11,B12,C21
        //cout << "A11,B12,C21" << endl;
    }
}

int main() {
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            d[i][j] = rand(); //might change to all 1 to easier check correctness
        }
    }
    cout << "Finish generating random array" << endl;
    clock_t begin_time = clock();
    FWR((int*)d,(int*)d,(int*)d,N);
    clock_t end_time = clock();
    double elapsed_secs = double(end_time - begin_time) / CLOCKS_PER_SEC;
    cout << "Recursive Floyd-Warshall takes " << elapsed_secs << " seconds!" << endl;
}
