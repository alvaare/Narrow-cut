#ifndef __NARROW_CUT_HPP_INCLUDED__
#define __NARROW_CUT_HPP_INCLUDED__

#include "graph.hpp"
#include <queue>

struct less_double {
  bool operator()(double a, double b) {
    return a < b-eps;
  }
};

typedef set<double, less_double> set_double;

set_double narrow_cut_values(LP_solution*);

queue<cut> narrow_cuts(LP_solution*);

void print_set_double(set_double*);



#endif
