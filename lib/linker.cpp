#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<fstream>
#include"linker.hpp"
using namespace std;

graph get_solution() {
  char command[] = "python Lp_solver.py";
  system(command);

  string line;
  ifstream myfile ("temp.txt");

  getline(myfile, line);
  int n = stoi(line);
  graph G(n);

  int i = 0, j = 0;
  while (getline(myfile,line)) {
    double e = stod(line);
    G.edges[i][j] = e;
    if(j==n-1) {
      j = 0;
      i++;
    }
    else
      j++;
  }
  return G;

}
