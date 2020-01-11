#ifndef __GH_TREE_HPP_INCLUDED__
#define __GH_TREE_HPP_INCLUDED__

#include<set>
#include"graph.hpp"
using namespace std;

graph gh_tree(graph*);

set<int> narrow_cuts_values(graph*);

#endif
