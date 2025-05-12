#include <vector>
#include <iostream>
#include <limits>
#include "tableau.h"

using namespace std;

Tableau::Tableau(string filePath = "") {
    // constructor
    if (filePath != "") {
        freopen("input.txt", "r", stdin);
    }
    // get the number of variables
    cout << "Enter the number of variables: ";
    cin >> varsNum;

    // get the number of constraints
    cout << "Enter the number of constraints: ";
    cin >> constraintsNum;

    // initialize the tableau dimensions
    int width = 1 + varsNum + 1;

    tableau.resize(constraintsNum + 1, vector<double>(width));

    // ---------------- SET UP THE TABLEAU ----------------
    // set the top-left corner of the tableau to 1
    tableau[0][0] = 1;

    // get the objective function
    cout << "Enter the coefficients of the objective function (space-separated):\n";

    for (int i = 1; i < varsNum+1; ++i) {
        double input;
        cin >> input;
        tableau[0][i] = input * -1;
    };

    // set the top-right corner of the tableau to 0 (the initial optimal value)
    tableau[0][varsNum + 1] = 0;

    // get the constraints
    for (int i = 1; i < constraintsNum + 1; ++i) {
        cout << "Enter coefficients for constraint " << i << " followed by the RHS:\n";
        // set the left-most column to be \vec{0}
        tableau[i][0] = 0;

        // set the tableau entries as the constraint coefficients
        for (int j = 1; j < varsNum + 2; ++j ) {
            cin >> tableau[i][j];
        }
    }
}

void constructAuxTableau() {
    
}

int Tableau::chooseEnteringVar(vector<double> objectiveFunction) {
    // chooseEnteringVar: Vector<Double> -> Double
    //                 : Returns the index of the entering variable, using Bland's rule (i.e. the first positive entry of objectiveFunction)
    //                 : Returns -1 if all of the entries of objectiveFunction is negative.

    // Note: objectiveFunction is the objective function portion of the tableau (i.e. the original objective function multiplied by -1)
    for (int i = 0; i < objectiveFunction.size(); ++i) {
        if (objectiveFunction[i] < 0) {
            return i + 1; // offset for tableau indexing
        }
    }
    
    return -1;
}

pair<int,int> Tableau::choosePivotElem(int col){
    // choosePivotElem: int -> pair<int,int>
    //                : Returns a pair containing the coordinates of the pivot element for the next iteration, using the minimum ratio test
    int row = -1;
    // initialize the minRatio to infinity
    double minRatio = numeric_limits<double>::infinity();

    for (int i = 0; i < constraintsNum + 1; ++i) {
        if (tableau[i][col]> 0 && tableau[i][varsNum + 1]/tableau[i][col] < minRatio) {
            row = i;
            minRatio = tableau[i][varsNum + 1]/tableau[i][col];
        }
    }

    return {row, col};
}

void Tableau::pivot(pair<int, int> pivotCoords) {
    // pivot: Pair<Int, Int> -> None
    //      : Takes in a coordinate of an element in the tableau and make approriate changes by pivoting on this element
    int r = pivotCoords.first;
    int c = pivotCoords.second;
    double pivotElem =  tableau[r][c];

    for (int k = 0; k < constraintsNum + 1; ++k) {
        if (k == r) {
            for (int j = 0; j < tableau[0].size(); ++j) {
                tableau[k][j] *= 1/pivotElem; 
            }
        } else {
            double row_k_pivot = tableau[k][c];

            for (int j = 0; j < tableau[0].size(); ++j) {
                tableau[k][j] -= (row_k_pivot/ pivotElem) * tableau[r][j];
            }
        }
    }
}

bool Tableau::isUnbounded(int col) {
    // isUnbounded: int -> Bool
    //            : Return true if the LP is unbounded, false otherwise
    for (int i = 0; i < constraintsNum + 1; ++i) {
        if (tableau[i][col] > 0) {
            return false;
        }
    }
    
    return true;

}

vector<double> Tableau::getObjectiveFunction() {
    // getObjectFunction: None -> vector<double>
    //                  : Return the object function of the current tableau
    return vector<double>(vector<double>(tableau[0].begin() +1, tableau[0].end()-1));
}

vector<vector<double>> Tableau::getTableau() {
    // getTableau: None -> vector<vector<double>>
    //           : Return the current state of the tableau
    return tableau;
}




