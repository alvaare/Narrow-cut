#include"narrow_cut.hpp"
#include"gh_tree.hpp"
#include<queue>
#include<iostream>

set_double narrow_cut_values(LP_solution* x) {
  int n = x->n;
  int s = x->s;
  int t = x->t;
  graph G = from_LP_solution_to_graph(x);
  graph T = gh_tree(&G);

  int father[n];
  bool visited[n] = {false};
  queue<int> active;
  visited[s]=true;
  int u = s;
  while(u!=t) {
    for (int v=0; v<n; v++)
      if (T.edges[u][v] > eps && !visited[v]) {
        active.push(v);
        father[v] = u;
      }
    visited[u] = true;
    u = active.front();
    active.pop();
  }

  set_double S;
  while(u!=s) {
    S.insert(T.edges[u][father[u]]);
    u = father[u];
  }
  return S;
}

void print_set_double(set_double* S) {
  cout << "The set contains: ";
  for (set_double::iterator it=S->begin(); it!=S->end(); it++)
    cout << *it << " ";
  cout << "\n";
}
