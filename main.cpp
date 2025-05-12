#include <iostream>
#include "solver.h"
using namespace std;

int main() {
    SimplexSolver solver = SimplexSolver("input.txt");
    solver.solve();
    return 0;
}