#include<iostream>
#include"min_cut.hpp"
#include"gh_tree.hpp"
#include"linker.hpp"
#include<set>
#include"stdlib.h"
#include"time.h"
#include<fstream>
#include"narrow_cut.hpp"
#include"find_k.hpp"

using namespace std;

int main() {
  string file_name = "simple_graphs_with_at_least_two_narrow_cuts_2.txt";
  int i=0;
  while(i<8) {
    LP_solution x = get_solution();
    cout << "ESSAI\n";
    if (find_k(&x) <= 10) {
      cout << i << " K_CORRECT\n";
      if(narrow_cut_values(&x).size() > 2) {
        cout << i << "\n";
        store_LP_solution(&x, file_name);
        store_narrow_cuts(&x, file_name);
        i++;
      }
    }
  }
  /*int n=6;
  LP_solution x(n);
  x.s=0;
  x.t=n-1;
  double edges[n][n] = {{0,0,0,1,0,0},
                        {0,0,1,1,0,0},
                        {0,1,0,0,1,1},
                        {1,1,0,0,1,0},
                        {0,0,1,1,0,0},
                        {0,0,1,0,0,0}};
  for (int i=0; i<n; i++)
    for (int j=0; j<n; j++)
      x.edges[i][j] = edges[i][j];
  int k = find_k(&x);
  cout << k << "\n";
  set_double S = narrow_cut_values(&x);
  print_set_double(&S);*/
}
