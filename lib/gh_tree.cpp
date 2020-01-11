#include<iostream>
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
