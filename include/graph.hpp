#ifndef __GRAPH_HPP_INCLUDED__
#define __GRAPH_HPP_INCLUDED__

#include<set>
using namespace std;

struct cut {
  set<int> nodes;
  double value;
};

struct graph {
  int n;
  double** edges;
  graph(int n) {
    this->n = n;
    this->edges = new double*[n];
    for (int i = 0; i < n; i++) {
      this->edges[i] = new double[n];
      for (int j = 0; j < n; j++)
        this->edges[i][j] = 0;
    }
  }
  ~graph() {
    for (int i=0; i<n; i++)
      delete [] this->edges[i];
    delete [] this->edges;
  }
};

bool is_connex(graph*);

graph complete_graph(graph*);

graph rand_graph(int);

graph rand_connex_graph(int);

void print_graph(graph*);

void print_cut(cut*);

bool is_in_cut(cut*, int);

#endif
