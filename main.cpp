#include <iostream>
#include "solver.h"
#include "tableau.h"
using namespace std;

int varsNum;
int constraintsNum;
vector<double> objFunc;
vector<vector<double>> constraints;

Tableau getInput() {
    string testFile;
    // get test file name
    cout << "Please enter the name of the test file (with the extension):\n";
    cin >> testFile; 
    // getInput: set the corresponding variables based on user's input and return the configured tableau
    freopen(("./tests/" + testFile).c_str(), "r", stdin);
    
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

    tableau.setConstraints(constraints);
    

    return tableau;
}

int main() {
    // SimplexSolver solver = SimplexSolver("input.txt");
    // solver.solve();
    // return 0;

    Tableau tableau = getInput();
    // cout << "\nInitial Tableau:\n\n";
    
    // for (const auto& row : tableau.getTableau()) {
    //     for (double val : row) {
    //         cout << val << "\t";
    //     }
    //     cout << "\n";
    // }
    // cout << "\n";


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