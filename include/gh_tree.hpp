#ifndef __GH_TREE_HPP_INCLUDED__
#define __GH_TREE_HPP_INCLUDED__

#include<set>
#include"graph.hpp"
using namespace std;

struct less_double {
  bool operator()(double a, double b) {
    return a < b-eps;
  }
};

typedef set<double, less_double> set_double;

graph gh_tree(graph*);

set_double narrow_cut_values(graph*, int, int);

#endif
