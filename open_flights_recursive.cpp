#include <iostream>
using namespace std;

typedef long long ll;

const ll L1_CACHE_SIZE = 32768;
const int number_of_nodes = 3179;
const int number_of_edges = 66067;

double INF = 100000000.0; // 25 billion
double d[number_of_nodes][number_of_nodes];

/*
 * Size of (sub)matrix A: dm x dp
 * Size of (sub)matrix B: dm x dn
 * Size of (sub)matrix C: dn x dp
 * */
void FWR_All(double* A, double* B, double* C, const ll N,
        const int dm, const int dn, const int dp) {
    //get cache size
    //cout << dm << " " << dn << " " << dp << endl;
    ll memSize = ((ll)dm*(ll)dp + (ll)dm*(ll)dn + (ll)dn*(ll)dp)*(sizeof(ll));
    if (memSize <= L1_CACHE_SIZE) {
        // implement iterative version
        for (ll k = 0; k < dn; k++) {
            for (ll i = 0; i < dm; i++) {
                for (ll j = 0; j < dp; j++) {
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
  for (int i = 0; i < number_of_nodes; ++i) {
    for (int j = 0; j < number_of_nodes; ++j) {
      if (i == j) {
        d[i][j] = 0.0;
      } else {
        d[i][j] = INF;
      }
    }
  }

  cout << "FINISH INITIAL" << endl;

  int u, v;
  double weight;
  for (int e = 0; e < number_of_edges; ++e) {
    // cout << "INPUT: " << e << endl;
    cin >> u >> v >> weight;
    d[u][v] = weight;
    d[v][u] = weight;
  }

  cout << "FINISH INPUT" << endl;
  
  clock_t begin_time = clock();
  FWR_All((double*)d,(double*)d,(double*)d,number_of_nodes,number_of_nodes,number_of_nodes,number_of_nodes);
  clock_t end_time = clock();
  double elapsed_secs = double(end_time - begin_time) / CLOCKS_PER_SEC;
  cout << "Recursive Floyd-Warshall (Flexible version) takes " << elapsed_secs << " seconds!" << endl;

  // output to a file for checking correctness
  for (int i = 0; i < number_of_nodes; i++) {
    for (int j = 0; j < number_of_nodes; j++) {
      cout << d[i][j];
      if (j != number_of_nodes - 1) cout << " ";
    }
    cout << endl;
  }
  return 0;
}
