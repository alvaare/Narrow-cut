#include<iostream>
#include"min_cut.hpp"
#include<queue>
#include<climits>
#include"stdlib.h"
#include"time.h"
using namespace std;

int main() {
  srand(time(NULL));
  int n = 8;
  graph G = rand_connex_graph(n);
  print_graph(&G);

  cut C = min_cut(&G, 0, n-1);
  print_cut(&C);
}
