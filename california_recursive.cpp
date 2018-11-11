#include <algorithm>
#include <ctime>
#include <iostream>
using namespace std;

#include "RecursiveFW.cpp"

const int number_of_nodes = 21048;
const int number_of_edges = 21693;

long long INF = 25000000000; // 25 billion
long long dClassic[number_of_nodes][number_of_nodes]; // for classical algorithm
long long dFWR[number_of_nodes][number_of_nodes]; // for classical algorithm

int main() {
  for (int i = 0; i < number_of_nodes; ++i) {
    for (int j = 0; j < number_of_nodes; ++j) {
      if (i == j) {
        dClassic[i][j] = 0;
        dFWR[i][j] = 0;
      } else {
        dClassic[i][j] = INF;
        dFWR[i][j] = INF;
      }
    }
  }

  cout << "FINISH INITIAL" << endl;

  int label, u, v, ll_weight;
  double weight;
  for (int e = 0; e < number_of_edges; ++e) {
    cin >> label >> u >> v >> weight;
    ll_weight = (long long)weight*1000000;
    dClassic[u][v] = ll_weight;
    dClassic[v][u] = ll_weight;
    dFWR[u][v] = ll_weight;
    dFWR[v][u] = ll_weight;
  }

  cout << "FINISH INPUT READING" << endl;

  clock_t begin_time = clock();
  for (int k = 0; k < number_of_nodes; ++k) {
    cout << "PROC: " << k << endl;
    for (int i = 0; i < number_of_nodes; ++i) {
      for (int j = 0; j < number_of_nodes; ++j) {
        dClassic[i][j] = min(dClassic[i][j], dClassic[i][k] + dClassic[k][j]);
      }
    }
  }
  clock_t end_time = clock();
  double elapsed_secs = double(end_time - begin_time) / CLOCKS_PER_SEC;
  cout << "Classic Floyd Warshall takes " << elapsed_secs << " seconds!" << endl;

  begin_time = clock();
  FWR_All((int*)dFWR,(int*)dFWR,(int*)dFWR,number_of_nodes,number_of_nodes,number_of_nodes);
  end_time = clock();
  elapsed_secs = double(end_time - begin_time) / CLOCKS_PER_SEC;
  cout << "Recursive Floyd-Warshall (Flexible version) takes " << elapsed_secs << " seconds!" << endl;
}