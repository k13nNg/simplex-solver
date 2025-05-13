#include <iostream>
#include "solver.h"
#include "newTableau.h"
using namespace std;

int varsNum;
int constraintsNum;
vector<double> objFunc;
vector<vector<double>> constraints;

Tableau getInput() {
    // getInput: set the corresponding variables based on user's input and return the configured tableau
    freopen("./tests/input.txt", "r", stdin);

    cout << "Enter the number of variables: ";
    cin >> varsNum;

    cout << "\nEnter the number of constraints: ";
    cin >> constraintsNum;

    Tableau tableau = Tableau(varsNum, constraintsNum);
    constraints.resize(constraintsNum, vector<double>(varsNum + 1));

    cout << "Enter the coefficients of the objective function (space-separated):\n";
    for (int i = 0; i < varsNum; ++i) {
        double input;
        cin >> input;
        if (input != 0.0 && input != 0) {
            objFunc.push_back(input * -1);
        } else {
            objFunc.push_back(input);
        }
    };

    tableau.setObjectiveFunction(objFunc);


    for (int i = 0; i < constraintsNum; ++i) {
        cout << "Enter coefficients for constraint " << i << " followed by the RHS:\n";

        for (int j = 0; j < varsNum + 1; ++j ) {
            cin >> constraints[i][j];
        }
    } 
    cout << tableau.getConstraintsNum() << " x " << tableau.getVarsNum() << "\n";
    cout << constraints.size() << " x " << constraints[0].size() << "!\n";

    tableau.setConstraints(constraints);
    

    return tableau;
}

int main() {
    // SimplexSolver solver = SimplexSolver("input.txt");
    // solver.solve();
    // return 0;

    Tableau tableau = getInput();
    cout << "\nCurrent Tableau:\n";
    
    for (const auto& row : tableau.getTableau()) {
        for (double val : row) {
            cout << val << "\t";
        }
        cout << "\n";
    }
    cout << "\n";


    SimplexSolver solver = SimplexSolver(tableau);

//    Tableau p1 = solver.getPhase1Tableau();

//    cout << "\nPhase 1 Tableau:\n";
//    for (const auto& row : p1.getTableau()) {
//         for (double val : row) {
//             cout << val << "\t";
//         }
//         cout << "\n";
//     }
    solver.solve();
    return 0;
};