#include<iostream>
#include<queue>
#include<set>
#include"graph.hpp"
#include"gh_tree.hpp"
#include"min_cut.hpp"
using namespace std;

graph gh_tree(graph* G) {
  int n = G->n;
  int p[n] = {0};
  graph T(n);

  for (int s=1; s<n; s++) {
    int t = p[s];
    cut C = min_cut(G, s, t);
    T.edges[s][t] = C.value;
    T.edges[t][s] = C.value;
    for (int i=s+1; i<n; i++)
      if (p[i] == t && is_in_cut(&C, i))
        p[i] = s;
  }

  return T;
}

set<double> narrow_cut_values(graph* T, int s, int t) {
  int n = T->n;
  int father[n];

  bool visited[n] = {false};
  queue<int> active;
  visited[s]=true;
  int u = s;
  while(u!=t) {
    for (int v=0; v<n; v++)
      if (T->edges[u][v] > eps && !visited[v]) {
        active.push(v);
        father[v] = u;
      }
    visited[u] = true;
    u = active.front();
    active.pop();
  }

  set<double> S;
  while(u!=s) {
    S.insert(T->edges[u][father[u]]);
    u = father[u];
  }
  return S;
}
