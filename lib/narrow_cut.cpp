#include"narrow_cut.hpp"
#include"gh_tree.hpp"
#include"min_cut.hpp"
#include<queue>
#include<iostream>

void find_father(graph* T, int s, int t, int father[]) {
  int n = T->n;
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
}

set_double narrow_cut_values(LP_solution* x) {
  int n = x->n;
  int s = x->s;
  int t = x->t;
  graph G = from_LP_solution_to_graph(x);
  graph T = gh_tree(&G);
  int father[n];
  find_father(&T, s, t, father);

  int u = t;
  set_double S;
  while(u!=s) {
    double a = T.edges[u][father[u]];
    if (a < 2)
      S.insert(a);
    u = father[u];
  }
  return S;
}

queue<cut> narrow_cuts(LP_solution* x) {
  int n = x->n;
  int s = x->s;
  int t = x->t;
  graph G = from_LP_solution_to_graph(x);
  graph T = gh_tree(&G);
  int father[n];
  find_father(&T, s, t, father);

  int u = t;
  queue<cut> Q;
  while(u!=s) {
    int f = father[u];
    cut C = min_cut(&G, f, u);
    if (C.value < 2)
      Q.push(C);
    u = f;
  }
  return Q;
}

void print_set_double(set_double* S) {
  cout << "The set contains: ";
  for (set_double::iterator it=S->begin(); it!=S->end(); it++)
    cout << *it << " ";
  cout << "\n";
}
