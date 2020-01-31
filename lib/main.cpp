#include<iostream>
#include"min_cut.hpp"
#include"gh_tree.hpp"
#include"linker.hpp"
#include<set>
#include"stdlib.h"
#include"time.h"

using namespace std;

int main() {
  graph G = get_solution();
  print_graph(&G);

  int n = G.n;
  int s = 0;
  int t = n-1;

  graph gh_T = gh_tree(&G);
  print_graph(&gh_T);

  cout << "The set contains: ";
  set<double> S = narrow_cut_values(&gh_T, s, t);
  for (set<double>::iterator it=S.begin(); it!=S.end(); it++)
    cout << *it << " ";
  cout << "\n";
}
