#include <iostream>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <ctime>
#include <random>
#include <vector>
using namespace std;

const int N = 100000; // N^2 = 10 billions
const int NUM_TEST_POINTS = 1000000; // 1 million
vector<pair<int,int>> testpairs; // 1 million test points
vector<long> testvalues; // answer to 1 million test points

int main() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    // generate 1000000 test points
    for (int i = 0; i < NUM_TEST_POINTS; i++) {
        int p1 = rng()%N;
        int p2 = rng()%N;
        testpairs.push_back(make_pair(p1,p2));
    }
    cout << "Finish generating test points" << endl;
    sort(testpairs.begin(), testpairs.end());
    cout << "Finish sorting test points" << endl;
    int idx = 0;
    // generate random array and save it to binary file
    ofstream fstore("VeryLargeArr.bin", ios::binary);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            long x = (long)rng()%1000000;
            while (idx < NUM_TEST_POINTS && 
                    i == testpairs[idx].first && 
                    j == testpairs[idx].second) {
                testvalues.push_back(x);
                idx++;
            }
            fstore.write(reinterpret_cast<char *>(&x), sizeof(long));
        }
    }
    // flatten array and save it to binary file
    fstore.flush();
    cout << "Finish writing to disk" << endl;
    fstore.close(); // close the output stream

    // try accessing the binary file
    ifstream faccess("VeryLargeArr.bin", ios::binary);
    bool flag = true;
    for (int k = 0; k < NUM_TEST_POINTS; k++) {
        int i = testpairs[k].first, j = testpairs[k].second;
        long x;
        faccess.seekg((i*N+j)*sizeof(long));
        faccess.read(reinterpret_cast<char *>(&x), sizeof(long));
        if (x != testvalues[k]) {
            cout << "Value: " << testvalues[k] << endl;
            cout << "Read from store: " << x << endl;
            flag = false;
            break;
        }
        if (!flag) break;
    }
    cout << "Finish reading and checking all test points" << endl;
    faccess.close(); // close the input stream
    
    if (flag) cout << "Holy shit everything ok" << endl;
    else cout << "Damn it" << endl;
    return 0;
}
