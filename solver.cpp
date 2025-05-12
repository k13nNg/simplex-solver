#include "solver.h"
#include <iostream>

using namespace std;


SimplexSolver::SimplexSolver(string filePath): p2(filePath) {}

void SimplexSolver::solve() {
    // solve: None -> None
    //      : Runs the simplex method by repeatedly choosing an entering variable and pivot until no entering variable could be found

    int enteringVarColIndex = p2.chooseEnteringVar(p2.getObjectiveFunction());

    while (enteringVarColIndex != -1 && !p2.isUnbounded(enteringVarColIndex)) {
        cout << "\nEntering Variable Column Index: " << enteringVarColIndex << "\n";

        pair<int,int> pivotCoords = p2.choosePivotElem(enteringVarColIndex);

        p2.pivot(pivotCoords);

        enteringVarColIndex = p2.chooseEnteringVar(p2.getObjectiveFunction());

        
        cout << "\n Current Tableau:\n";
        
        for (const auto& row : p2.getTableau()) {
            for (double val : row) {
                cout << val << "\t";
            }
            cout << "\n";
        }
    }

    if (p2.isUnbounded(enteringVarColIndex)) {
        cout << "\nThe LP is unbounded!\n";
    } else {
        cout << "\nThe optimal solution is " << p2.getTableau()[0][p2.getTableau()[0].size()-1] << "\n";
    }
}