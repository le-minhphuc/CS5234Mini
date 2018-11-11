#include <iostream>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <ctime>
#include <random>
using namespace std;

const int N = 2000;
long d[N][N];

int main() {
    // generate random array
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            d[i][j] = (long)rng()%1000000;
        }
    }
    // flatten array and save it to binary file
    ofstream fstore("LargeArr.bin", ios::binary);
    fstore.write(reinterpret_cast<char *>((long *)d), N*N*sizeof(long));
    fstore.flush();
    fstore.close(); // close the output stream

    // try accessing the binary file
    ifstream faccess("LargeArr.bin", ios::binary);
    bool flag = true;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            long x;
            faccess.seekg((i*N+j)*sizeof(long));
            faccess.read(reinterpret_cast<char *>(&x), sizeof(long));
            if (x != d[i][j]) {
                cout << "Value of d[" << i << "][" << j << "] ";
                cout << " and the one read from storage are different!" << endl;
                cout << "Value: " << d[i][j] << endl;
                cout << "Read from store: " << x << endl;
                flag = false;
                break;
            }
        }
        if (!flag) break;
    }
    faccess.close(); // close the input stream
    
    if (flag) cout << "Holy shit everything ok" << endl;
    else cout << "Damn it" << endl;
    return 0;
}
