#include<set>
#include<queue>
#include<algorithm>
#include<climits>
#include<iostream>
#include"graph.hpp"
#include"min_cut.hpp"
using namespace std;

const double eps = 1e-5;

struct node {
  int id;
  double excess = 0;
  int height = 0;

};

struct node_comp {
  bool operator()(node* lhs, node* rhs) {
    return lhs->height < rhs->height;
  }
};

typedef priority_queue<node*, vector<node*>, node_comp> pq;

void initialize(graph* G, int s, node* nodes, double** flow, pq* active_nodes) {
  int n = G->n;
  nodes[s].height = n;
  for (int i=0; i<n; i++) {
    flow[i] = new double[n];
    for (int j = 0; j < n; j++)
      flow[i][j] = 0;
  }
  for(int i=0; i<n; i++) {
    nodes[i].id = i;
    double c = G->edges[s][i];
    if (i!=s && c>eps) {
      nodes[i].excess = c;
      flow[s][i] = c;
      flow[i][s] = -c;
      active_nodes->push(&nodes[i]);
    }
  }
}

void push(node* u, node* v, graph* G, node* nodes, double** flow, pq* a_nodes){
  int iu = u->id;
  int iv = v->id;
  double delta = min(u->excess, G->edges[iu][iv]-flow[iu][iv]);
  flow[iu][iv] += delta;
  flow[iv][iu] -= delta;
  u->excess -= delta;
  v->excess += delta;
  if (v->height < G->n)
    a_nodes->push(v);
}

void relabel(node* u, graph* G, node* nodes, double** flow, pq* a_nodes){
  if (u->excess < eps)
    return;
  int min_height = INT_MAX;
  for (int v = 0; v < G->n; v++) {
    if(G->edges[u->id][v]-flow[u->id][v] > eps) {
      int n_height = nodes[v].height;
      if(u->height > n_height)
        return;
      if (min_height > n_height)
        min_height = n_height;
    }
  }
  u->height = min_height+1;
}

void clear_node(node* u, graph* G, node* nodes, double** flow, pq* a_nodes){
  while(u->excess > eps) {
    for (int v=0; v<G->n; v++)
      if (u->excess > eps && nodes[v].height == u->height-1)
        push(u, &nodes[v], G, nodes, flow, a_nodes);
    relabel(u, G, nodes, flow, a_nodes);
  }
}

void print_flow(double** flow, int n) {
  cout << "This is the flow:\n";
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++)
      cout << flow[i][j] << " ";
    cout << "\n";
  }
}

void print_pq(pq* active_nodes) {
  pq q(*active_nodes);
  while(!q.empty()) {
    cout << q.top()->id << " ";
    q.pop();
  }
  cout << "\n";
}

cut find_cut(double** flow, graph* G, int s, int t) {
  cut C;
  int n = G->n;
  graph nG(n);
  for (int i=0; i<n; i++)
    for (int j=0; j<n; j++) {
      if (G->edges[i][j]>0 and abs(flow[i][j])+eps<G->edges[i][j])
        nG.edges[i][j]=1;
      /*nG.edges[i][j] = G->edges[i][j];
      if (abs(flow[i][j]) > eps)
        nG.edges[i][j]-=abs(flow[i][j]);*/
    }

  C.nodes.insert(s);
  queue<int> active;
  active.push(s);
  while(!active.empty()) {
    int v = active.front();
    active.pop();
    for(int i=0; i<n; i++)
      if (nG.edges[v][i]>eps && !is_in_cut(&C, i)) {
        C.nodes.insert(i);
        active.push(i);
      }
  }
  print_flow(flow, n);
  for (int i=0; i<n; i++)
    C.value+=flow[s][i];
  return C;
}

cut min_cut(graph* G, int s, int t){
  int n = G->n;
  node nodes[n];
  pq active_nodes;
  double** flow = new double*[n];;
  initialize(G, s, nodes, flow, &active_nodes);
  while(!active_nodes.empty()) {
    node* u = active_nodes.top();
    active_nodes.pop();
    if (u->id != s && u->id!=t) {
      clear_node(u, G, nodes, flow, &active_nodes);
    }
  }
  return find_cut(flow, G, s, t);
}
