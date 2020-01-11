#ifndef __GH_TREE_HPP_INCLUDED__
#define __GH_TREE_HPP_INCLUDED__

#include<set>
#include"graph.hpp"
using namespace std;

graph gh_tree(graph*);

set<double> narrow_cut_values(graph*, int, int);

#endif
