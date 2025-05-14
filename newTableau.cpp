#include "newTableau.h"
#include <iostream>

using namespace std;

Tableau::Tableau(int varsNumToSet, int constraintsNumToSet) {
    // Tableau(): Constructor 
    //        : Initialize the dimensions of the tableau, as well as the tableau itself

    varsNum = varsNumToSet;
    constraintsNum = constraintsNumToSet;
    isUnbounded = false;

    // initilize the tableau with dimensions constraintsNum + 1 x varsNum + 2
    //      constraintsNum + 1 because we need to have 1 more line for the objective function
    //      varsNum + 2 because we need 1 left-most column, and 1 right-most column in addition to the constraints in the tableau
    tableau.resize(constraintsNum + 1, vector<double>(varsNum + 2));

    // set the top-left corner of the tableau to 1
    tableau[0][0] = 1;
}

vector<vector<double>> Tableau::getConstraints(){
    // getConstraints(): get the constraints of the tableau
    vector<vector<double>> A;
    for (int i = 1; i < constraintsNum+1; ++i) {
        vector<double> row;
        for (int j = 1; j < varsNum+2; ++j) {
            row.push_back(tableau[i][j]);
        }
        A.push_back(row);
    }
    return A;
}

vector<vector<double>> Tableau::getTableau() {
    // getTableau(): return the current state of the tableau
    return tableau;
}

vector<double> Tableau::getObjectiveFunction() {
    // getObjectiveFunction: return the current objective function
    return vector<double>(vector<double>(tableau[0].begin() + 1, tableau[0].end()-1));
}

void Tableau::setObjectiveFunction(vector<double> objectiveFunction) {
    // setObjectiveFunction: set the objective function of the tableau based on objectiveFunction

    for (int i = 1; i < varsNum + 1; ++i) {
        tableau[0][i] = objectiveFunction[i-1]; // offset by -1 to account for the length of objectiveFunction
    }    

}

int Tableau::getVarsNum() {
    // getVarsNum: return the number of variables in the tableau
    return varsNum;
}

int Tableau::getConstraintsNum() {
    // getVarsNum: return the number of variables in the tableau
    return constraintsNum;
}


void Tableau::setConstraints(vector<vector<double>> constraints) {
    // setConstraints: set the constraints of the tableau based on constraints
    for (int i = 1; i < constraintsNum + 1; ++i) {
        for (int j = 1; j < varsNum + 2; ++j) {
            tableau[i][j] = constraints[i-1][j-1];
        }
    }
}

void Tableau::phase1ModifyFirstRow() {
    // phase1ModifyFirstRow(): modify the first row of the tableau (including the RHS) so that the objective function is expressed in terms of the non-basic variables
    for (int i = 1; i < tableau.size(); i++) {
        for (int j = 0; j < tableau[0].size(); j++) {
            tableau[0][j] -= tableau[i][j];
        }
    }
}

int Tableau::chooseEnteringVar() {
    // chooseEnteringVar: Returns the index of the entering variable, using Bland's rule (i.e. the first positive entry of objectiveFunction)
    //                 : Returns -1 if all of the entries of objectiveFunction is negative.
    vector<double> objectiveFunction = getObjectiveFunction();
    // Note: objectiveFunction is the objective function portion of the tableau (i.e. the original objective function multiplied by -1)
    for (int i = 0; i < objectiveFunction.size(); ++i) {
        if (objectiveFunction[i] < 0) {
            return i + 1; // offset for tableau indexing
        }
    }
    
    return -1;
}

pair<int,int> Tableau::choosePivotElem(int col) {
    // choosePivotElem: returns a pair containing the coordinates of the pivot element for the next interation, using the minimum ratio test

    int row = -1;

    // initialize the minRatio to infinity
    double minRatio = numeric_limits<double>::infinity();

    for (int i = 0; i < constraintsNum + 1; ++i) {
        double candRatio = tableau[i][varsNum + 1]/tableau[i][col];
        if (tableau[i][col] > 0 &&  candRatio < minRatio) {
            row = i;
            minRatio = candRatio;
        }
    }
    return {row, col};
}

void Tableau::pivot(pair<int, int> pivotCoords) {
    // pivot: Takes in a coordinate pair of an element in the tableau, and pivot on this element
    int r = pivotCoords.first;
    int c = pivotCoords.second;
    double pivotElem = tableau[r][c];

    for (int k = 0; k < constraintsNum + 1; ++k) {
        if (k == r)  {
            for (int j = 0; j < varsNum + 2; ++j) {
                tableau[k][j] *= 1/pivotElem;
            }
        } else {
            double rowKPivot = tableau[k][c];
            for (int j = 0; j < varsNum + 2; ++j) {
                tableau[k][j] -= (rowKPivot/ pivotElem) * tableau[r][j];
            }
        }
    }
}

bool Tableau::getIsUbounded() {
    // isUnbounded: return true if the LP is unbounded (based on the tableau), and false otherwise
    return isUnbounded;
}

bool Tableau::setIsUnbounded(int col) {
    // set the value of the isUnbounded variable
    for (int i = 0; i < constraintsNum + 1; ++i) {
        if (tableau[i][col] > 0) {
            return false;
        }
    }
    
    isUnbounded = true;
    return true;
}
