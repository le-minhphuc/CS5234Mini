#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, double> id;
typedef pair<double, int> di;
typedef vector<int> vi;
typedef vector<double> vd;
typedef vector<id> vid;
typedef vector<di> vdi;

const int number_of_nodes = 3179;
const int number_of_edges = 66067;

double INF = 100000000.0; // 100 million

vector<vid> AdjList;
double shortest[number_of_nodes][number_of_nodes];
priority_queue< di, vector<di>, greater<di> > pq;

void dijkstra(int source) {
  pq = priority_queue< di, vector<di>, greater<di> >();
  pq.push(di(0, source));

  while (!pq.empty()) {
    di front = pq.top();
    pq.pop();
    double dist = front.first;
    int node1 = front.second;
    // cout << "PROC: " << node1 << endl;
    if (dist > shortest[source][node1]) {
      continue;
    }
    for (int j = 0; j < (int)AdjList[node1].size(); ++j) {
      id node2 = AdjList[node1][j];
      if (shortest[source][node1] + node2.second < shortest[source][node2.first]) {
        shortest[source][node2.first] = shortest[source][node1] + node2.second;
        pq.push(di(shortest[source][node2.first], node2.first));
      }
    }
  }
}

int main() {
  AdjList.assign(number_of_nodes, vid());
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

  int u, v;
  double weight;
  for (int e = 0; e < number_of_edges; ++e) {
    cin >> u >> v >> weight;
    AdjList[u].push_back(id(v, weight));
    AdjList[v].push_back(id(u, weight));
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


  // print to file for checking correctness
  for (int i = 0; i < number_of_nodes; i++) {
    for (int j = 0; j < number_of_nodes; j++) {
      cout << shortest[i][j];
      if (j != number_of_nodes - 1) cout << " ";
    }
    cout << endl;
  }

  cout << "FINISH Johnson" << endl;
}