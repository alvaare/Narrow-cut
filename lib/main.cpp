#include<iostream>
#include"min_cut.hpp"
#include"gh_tree.hpp"
#include<set>
#include"stdlib.h"
#include"time.h"
using namespace std;

int main() {
  srand(time(NULL));
  int n = 6;
  int s = 0;
  int t = n-1;

  graph G = rand_connex_graph(n);
  print_graph(&G);

  graph gh_T = gh_tree(&G);
  print_graph(&gh_T);

  cout << "The set contains: ";
  set<double> S = narrow_cut_values(&gh_T, s, t);
  for (set<double>::iterator it=S.begin(); it!=S.end(); it++)
    cout << *it << " ";
  cout << "\n";
}
