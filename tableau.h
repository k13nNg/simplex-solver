#ifndef TABLEAU_H
#define TABLEAU_H

#include <iostream>
#include <vector>
#include <limits>
#include <utility>

class Tableau {
    private:
        int varsNum;                       // Number of original decision variables
        int constraintsNum;               // Number of constraints
        std::vector<std::vector<double>> phase1Tableau;  // Tableau for Phase 1 of simplex
        std::vector<std::vector<double>> phase2Tableau;  // Tableau for Phase 2 of simplex

    public:
        // Constructor: Reads problem data from "input.txt"
        Tableau(std::string filePath);

        // Returns index of entering variable using Bland's rule
        int chooseEnteringVar(std::vector<double> objectiveFunction);

        // Returns coordinates of pivot element using minimum ratio test
        std::pair<int, int> choosePivotElem(int col);

        // Performs pivot operation on the given pivot element
        void pivot(std::pair<int, int> pivotCoords);

        // Construct the auxiliary tableau for Phase 1
        void constructAuxTableau();

        // Checks if column corresponds to an unbounded direction
        bool isUnbounded(int col);

        // Returns the current objective function row (excluding first col and RHS)
        std::vector<double> getObjectiveFunction();

        // Returns the current state of the tableau
        std::vector<std::vector<double>> getTableau();
};

#endif // TABLEAU_H