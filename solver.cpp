#include "solver.h"
#include <iostream>

using namespace std;


SimplexSolver::SimplexSolver(Tableau p2): p2(p2) {
    constructPhase1Tableau();
}

Tableau SimplexSolver::getPhase1Tableau() {
    //getPhase1Tableau(): returns phase 1 tableau
    return p1;
}

void SimplexSolver::constructPhase1Tableau() {
    // constructPhase1Tableau(): construct the tableau for Phase 1 of the Simplex Method
    int numConstraints = p2.getConstraintsNum();
    int numOriginalVariables = p2.getVarsNum(); // Excluding the RHS column
    int numArtificialVariables = numConstraints;
    int numTotalVariablesPhase1 = numOriginalVariables + numArtificialVariables;

    Tableau result = Tableau(numTotalVariablesPhase1, numConstraints);

    std::vector<double> phase1ObjectiveFunction(numTotalVariablesPhase1, 0.0);
    for (int i = numOriginalVariables; i < numTotalVariablesPhase1; ++i) {
        phase1ObjectiveFunction[i] = 1.0; // Coefficients of -1 for artificial variables
    }
    result.setObjectiveFunction(phase1ObjectiveFunction);
    
    std::vector<std::vector<double>> constraints = p2.getConstraints();
    
    for (int i = 0; i < numConstraints; ++i) {
        auto& row = constraints[i];

        int oldSize = row.size();
        double rhs = row.back();  // Save RHS before resizing

        row.resize(oldSize + numConstraints, 0.0);  // Adds space for identity matrix

        // Shift RHS value to the new end
        row.back() = rhs;

        // Clear original RHS position (optional)
        row[oldSize - 1] = 0.0;
        // Insert identity value at the correct location
        row[oldSize - 1 + i] = 1.0;

    }

    result.setConstraints(constraints);
    
    cout << "\nPhase 1 Tableau before re-arranging:\n";
        
    for (const auto& row : result.getTableau()) {
        for (double val : row) {
            cout << val << "\t";
        }
        cout << "\n";
    }

    // make the artificial variables basic
    result.phase1ModifyFirstRow();

    p1 = result; // Store the Phase 1 tableau

}

Tableau SimplexSolver::solveHelper(Tableau t) {
    // Runs the simplex method by repeatedly choosing an entering variable and pivot until no entering variable could be found

    int enteringVarColIndex = t.chooseEnteringVar();
    t.setIsUnbounded(enteringVarColIndex);

    cout << "\nInitial Tableau:\n\n";
        
    for (const auto& row : t.getTableau()) {
        for (double val : row) {
            cout << val << "\t";
        }
        cout << "\n";
    }

    while (enteringVarColIndex != -1) {

        if (t.getIsUbounded()) {
            return t;
        } else {
            cout << "\nEntering variable: " << enteringVarColIndex << "\n";
            
            pair<int,int> pivotCoords = t.choosePivotElem(enteringVarColIndex);
            cout << "\nLeaving variable: " << pivotCoords.first << "\n";
            t.pivot(pivotCoords);
            
            cout << "\nCurrent Tableau:\n\n";
            
            for (const auto& row : t.getTableau()) {
                for (double val : row) {
                    cout << val << "\t";
                }
                cout << "\n";
            }
            enteringVarColIndex = t.chooseEnteringVar();
            t.setIsUnbounded(enteringVarColIndex);

        }
        
    }

    // return t.getTableau()[0][t.getTableau()[0].size()-1];
    return t;
}

void SimplexSolver::solve() {
    // Phase 1
    cout << "\n-------------- Phase 1 starting --------------\n";
    vector<vector<double>> p1Final = solveHelper(p1).getTableau();

    double w = p1Final[0][p1Final[0].size()-1];

    if (w != 0) {
        cout << "\nThe LP is infeasible!\n";
    } else {
        // Phase 2
        cout << "\n-------------- Phase 2 starting --------------\n";
        Tableau p2Result = solveHelper(p2);

        if (p2Result.getIsUbounded()) {
            cout << "\nThe LP is unbounded!\n\n";
        } else {
            vector<vector<double>> p2Final = p2Result.getTableau();
                    
            double optimalVal = p2Final[0][p2Final[0].size() - 1];
            cout << "\nThe optimal value is: " << optimalVal << "\n";
            
            cout << "\nFinal Tableau:\n\n";
            
            for (const auto& row : p2Final) {
                for (double val : row) {
                    cout << val << "\t";
                }
                cout << "\n";
            }
            cout << "\n";
        }

        
    }

}
