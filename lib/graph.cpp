#include<iostream>
#include<queue>
#include<climits>
#include"graph.hpp"
using namespace std;

bool is_connex(graph* G) {
  bool visited[G->n]={false};
  int v = 0;
  queue<int> q;
  q.push(v);
  while(!q.empty()) {
    v = q.front();
    q.pop();
    if (!visited[v]) {
      visited[v] = true;
      for (int i=0; i < G->n; i++)
        if (G->edges[v][i] > 0)
          q.push(i);
    }
  }

  for(int i=0; i<G->n; i++)
    if(!visited[i])
      return false;
  return true;
}

graph rand_graph(int n) {
  graph G(n);
  for (int i=0; i<n; i++)
    for (int j=0; j<i; j++) {
      double r = ((double)rand()/(double)RAND_MAX);;
      G.edges[i][j] = r;
      G.edges[j][i] = r;
    }
  return G;
}

graph rand_connex_graph(int n) {
  graph G = rand_graph(n);
  while (!is_connex(&G))
    G = rand_graph(n);
  return G;
}

graph complete_graph(graph* G) {
  int n = G->n;
  graph C(n);
  for (int i=0; i<n; i++)
    for (int j=0; j<n; j++) {
      if (G->edges[i][j]>0 || i==j)
        C.edges[i][j] = G->edges[i][j];
      else
        C.edges[i][j] = INT_MAX/2;
      }
  for (int k=0; k<n; k++)
    for (int i=0; i<n; i++)
      for (int j=0; j<n; j++)
        if(C.edges[i][j] > C.edges[i][k]+C.edges[k][j])
          C.edges[i][j] = C.edges[i][k]+C.edges[k][j];
  return C;
}


void print_graph(graph* G) {
  for (int i=0; i<G->n; i++) {
    for (int j=0; j<G->n; j++) {
      cout << G->edges[i][j] << "\t";
    }
    cout << "\n";
  }
  cout << "\n";
}

void print_cut(cut* C) {
  cout << "The cut contains: ";
  for (set<int>::iterator it=C->nodes.begin(); it!=C->nodes.end(); it++)
    cout << *it << " ";
  cout << "\n";
  cout << "And its value is: " << C->value << "\n";
}

bool is_in_cut(cut* C, int u) {
  return C->nodes.find(u)!=C->nodes.end();
}

graph from_LP_solution_to_graph(LP_solution* x) {
  int n=x->n;
  graph G(n);
  for(int i=0; i<n; i++)
    for(int j=0; j<n; j++)
      G.edges[i][j] = x->edges[i][j];
  return G;
}
