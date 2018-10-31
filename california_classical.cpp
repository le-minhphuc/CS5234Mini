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

  for (int k = 0; k < number_of_nodes; ++k) {
    cout << "PROC: " << k << endl;
    //preload k-th column and k-th row
    for (int i = 0; i < number_of_nodes; ++i) {
      for (int j = 0; j < number_of_nodes; ++j) {
        if (d[i][j] > d[i][k] + d[k][j]) {
          d[i][j] = d[i][k] + d[k][j];
        }
      }
    }
  }

  cout << "FINISH FW" << endl;
}