#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<queue>
#include<set>
#include"linker.hpp"
#include"narrow_cut.hpp"
#include <iomanip>
using namespace std;

LP_solution get_solution() {
  char command[] = "python Lp_solver.py";
  system(command);

  string line;
  ifstream myfile ("temp.txt");

  getline(myfile, line);
  int n = stoi(line);
  getline(myfile, line);
  int s = stoi(line);
  getline(myfile, line);
  int t = stoi(line);
  LP_solution G(n);
  G.s=s;
  G.t=t;

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

void store_LP_solution(LP_solution* x, string file_name) {
  fstream myfile;
  myfile.open(file_name, fstream::app);
  myfile << setprecision(3);
  int n=x->n;
  for(int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      myfile << x->edges[i][j] << " \t";
    }
    myfile << "\n";
  }
  myfile.close();
}

void store_narrow_cuts(LP_solution* x, string file_name) {
  fstream myfile;
  myfile.open(file_name, fstream::app);
  myfile << setprecision(3);

  queue<cut> Q = narrow_cuts(x);
  while(!Q.empty()) {
    cut C = Q.front();
    Q.pop();
    myfile << "The narrow cut contains: ";
    set<int> S = C.nodes;
    for (set<int>::iterator it=S.begin(); it!=S.end(); it++)
      myfile << *it << " ";
    myfile << "\n";
    myfile << "And its value is: " << C.value << "\n";
  }

  myfile << "\n";
  myfile.close();
}
