#include <iostream>
using namespace std;

const int number_of_nodes = 3179;
const int number_of_edges = 66067;

double INF = 100000000.0; // 25 billion
double d[number_of_nodes][number_of_nodes];

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