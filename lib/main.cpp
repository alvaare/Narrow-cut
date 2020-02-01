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
  string file_name = "simple_graphs_with_at_least_two_narrow_cuts.txt";
  for (int n=6; n<7; n++) {
    int i=0;
    while(i<20) {
      LP_solution x = get_solution();
      if(find_k(&x) <= 10 && narrow_cut_values(&x).size() > 1) {
        cout << i << "\n";
        store_LP_solution(&x, file_name);
        i++;
      }
    }
  }
}
