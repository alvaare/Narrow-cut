#include<iostream>
#include"min_cut.hpp"
#include"gh_tree.hpp"
#include<queue>
#include<climits>
#include"stdlib.h"
#include"time.h"
using namespace std;

int main() {
  srand(time(NULL));
  int n = 6;
  graph G = rand_connex_graph(n);
  print_graph(&G);

  graph gh_T = gh_tree(&G);
  print_graph(&gh_T);
}
