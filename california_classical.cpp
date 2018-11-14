#include <iostream>
using namespace std;

const int number_of_nodes = 21048;
const int number_of_edges = 21693;

long long INF = 25000000000; // 25 billion
long long d[number_of_nodes][number_of_nodes];

int main() {
  for (int i = 0; i < number_of_nodes; ++i) {
    for (int j = 0; j < number_of_nodes; ++j) {
      if (i == j) {
        d[i][j] = 0;
      } else {
        d[i][j] = INF;
      }
    }
  }

  cout << "FINISH INITIAL" << endl;

  int label, u, v, ll_weight;
  double weight;
  for (int e = 0; e < number_of_edges; ++e) {
    cin >> label >> u >> v >> weight;
    ll_weight = (long long)weight*1000000;
    d[u][v] = ll_weight;
    d[v][u] = ll_weight;
  }

  cout << "FINISH INPUT" << endl;

  clock_t begin_time = clock();
  for (int k = 0; k < number_of_nodes; ++k) {
    //cout << "PROC: " << k << endl;
    //preload k-th column and k-th row
    for (int i = 0; i < number_of_nodes; ++i) {
      for (int j = 0; j < number_of_nodes; ++j) {
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
      }
    }
  }
  clock_t end_time = clock();
  double elapsed_secs = double(end_time - begin_time) / CLOCKS_PER_SEC;
  cout << "Classical Floyd-Warshall takes " << elapsed_secs << " seconds!" << endl;

  // print to file for checking correctness
  for (int i = 0; i < number_of_nodes; i++) {
    for (int j = 0; j < number_of_nodes; j++) {
      cout << d[i][j];
      if (j != number_of_nodes - 1) cout << " ";
    }
    cout << endl;
  }
}
