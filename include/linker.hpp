#ifndef __LINKER_HPP_INCLUDED__
#define __LINKER_HPP_INCLUDED__

#include"graph.hpp"
#include<string>

LP_solution get_solution();

void store_LP_solution(LP_solution*, string);

void store_narrow_cuts(LP_solution*, string);

#endif
