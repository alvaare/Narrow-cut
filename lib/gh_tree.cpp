#include<iostream>
#include<queue>
#include<set>
#include"graph.hpp"
#include"gh_tree.hpp"
#include"min_cut.hpp"
using namespace std;

graph construct_gh_tree(int n, int* p, double* f) {
  graph T(n);
  for(int i=0; i<n; i++) {
    T.edges[i][p[i]] = f[i];
    T.edges[p[i]][i] = f[i];
  }
  return T;
}

void debug_int(int n, int* a) {
  for (int i=0; i<n; i++) {
    cout << a[i] << " ";
  }
  cout << "\n";
}

void debug_double(int n, double* a) {
  for (int i=0; i<n; i++) {
    cout << a[i] << " ";
  }
  cout << "\n";
}

graph gh_tree(graph* G) {
  int n = G->n;
  int p[n] = {0};
  double f[n] = {0};

  for (int s=1; s<n; s++) {
    int t = p[s];
    cut C = min_cut(G, s, t);
    //cout << s << " " << t << "\n";
    //print_cut(&C);
    f[s] = C.value;
    for (int i=0; i<n; i++)
      if (i!=s && p[i] == t && is_in_cut(&C, i))
        p[i] = s;
    if (is_in_cut(&C, p[t])) {
      p[s] = p[t];
      p[t] = s;

      f[s] = f[t];
      f[t] = C.value;
    }
  }
  //debug_int(n, p);
  //debug_double(n, f);
  return construct_gh_tree(n, p, f);
}

set_double narrow_cut_values(graph* T, int s, int t) {
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

  set_double S;
  while(u!=s) {
    S.insert(T->edges[u][father[u]]);
    u = father[u];
  }
  return S;
}
