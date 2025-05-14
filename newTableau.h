#ifndef NEWTABLEAU_H
#define NEWTABLEAU_H

#include <iostream>
#include <vector>
#include <limits>

class Tableau {
    private:
        // number of decision variables
        int varsNum;
        // number of constraints
        int constraintsNum;
        // phase 1 tableau
        std::vector<std::vector<double>> tableau;
        // is the Tableau unbounded?
        bool isUnbounded;

    public:
        // initialize the tableau based on varsNum and constraintsNum
        Tableau(int varsNumsToSet=0, int constraintsNumToSet=0);
        // get the current state of the tableau
        std::vector<std::vector<double>> getTableau();
        // get the current objective function
        std::vector<double> getObjectiveFunction();
        // get the constraints of the tableau
        std::vector<std::vector<double>> getConstraints();
        // get the number of variables in the tableau
        int getVarsNum();
        // get the number of constraints in the tableau
        int getConstraintsNum();
        // set the objective function in the tableau
        void setObjectiveFunction(std::vector<double> objectiveFunction);
        // set the constraints in the tableau
        void setConstraints(std::vector<std::vector<double>> constraints);
        // returns the index of entering variable, rerturns -1 if all of the entries of the objective function is negative
        int chooseEnteringVar();
        // -------------- ONLY APPLICABLE TO PHASE I of the Simplex Method --------------
        void phase1ModifyFirstRow();
        // returns a pair of coordinates for the pivoting element in the tableau
        std::pair<int,int> choosePivotElem(int col);
        // make approriate change to tableau by pivoting on element at pivotCoords
        void pivot(std::pair<int,int> pivotCoords);
        // returns true if the LP is unbounded (based on the tableau), and false otherwise
        bool getIsUbounded();
        // set the value of the isUnbounded variable
        bool setIsUnbounded(int col);
};

#endif // NEWTABLEAU_H