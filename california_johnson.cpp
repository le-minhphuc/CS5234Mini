#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, long long int> il;
typedef pair<long long int, int> li;
typedef vector<int> vi;
typedef vector<long long int> vl;
typedef vector<il> vil;
typedef vector<li> vli;

const int number_of_nodes = 21048;
const int number_of_edges = 21693;

long long int INF = 25000000000; // 25 billion

vector<vil> AdjList;
long long int shortest[number_of_nodes][number_of_nodes];
priority_queue< li, vector<li>, greater<li> > pq;

void dijkstra(int source) {
  pq = priority_queue< li, vector<li>, greater<li> >();
  pq.push(li(0, source));

  while (!pq.empty()) {
    li front = pq.top();
    pq.pop();
    long long int dist = front.first;
    int node1 = front.second;
    // cout << "PROC: " << node1 << endl;
    if (dist > shortest[source][node1]) {
      continue;
    }
    for (int j = 0; j < (int)AdjList[node1].size(); ++j) {
      il node2 = AdjList[node1][j];
      if (shortest[source][node1] + node2.second < shortest[source][node2.first]) {
        shortest[source][node2.first] = shortest[source][node1] + node2.second;
        pq.push(li(shortest[source][node2.first], node2.first));
      }
    }
  }
}

int main() {
  AdjList.assign(number_of_nodes, vil());
  for (int i = 0; i < number_of_nodes; ++i) {
    for (int j = 0; j < number_of_nodes; ++j) {
      if (i == j) {
        shortest[i][j] = 0;
      } else {
        shortest[i][j] = INF;
      }
    }
  }

  cout << "FINISH INITIAL" << endl;

  int label, u, v;
  long long int weight;
  for (int e = 0; e < number_of_edges; ++e) {
    cin >> label >> u >> v >> weight;
    AdjList[u].push_back(il(v, weight));
    AdjList[v].push_back(il(u, weight));
  }

  cout << "FINISH INPUT" << endl;

  clock_t begin_time = clock();
  for (int u = 0; u < number_of_nodes; ++u) {
    cout << u << endl;
    dijkstra(u);
  }
  clock_t end_time = clock();
  double elapsed_secs = double(end_time - begin_time) / CLOCKS_PER_SEC;
  cout << "Johnson takes " << elapsed_secs << " seconds!" << endl;


  print to file for checking correctness
  // for (int i = 0; i < number_of_nodes; i++) {
  //   for (int j = 0; j < number_of_nodes; j++) {
  //     cout << shortest[i][j];
  //     if (j != number_of_nodes - 1) cout << " ";
  //   }
  //   cout << endl;
  // }

  cout << "FINISH Johnson" << endl;
}