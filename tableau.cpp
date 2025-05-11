#include <vector>
#include <iostream>
#include <limits>


using namespace std;

class Tableau {
    private:
        int varsNum;
        int constraintsNum;
        vector<vector<double>> tableau;
        vector<int> basis;

    public:
        Tableau() {
            // constructor
            freopen("input.txt", "r", stdin);
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

            // get the starting basis
            // cout << "Enter the index of the starting basis in the matrix:\n";
            // for (int i = 0; i < constraintsNum; ++i) {
            //     int value;
            //     cin >> value;
            //     basis.push_back(value);
            // }
        }

        int chooseEnteringVar(vector<double> objectiveFunction) {
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

        pair<int,int> choosePivotElem(int col){
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

        void pivot(pair<int, int> pivotCoords) {
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

        bool isUnbounded(int col) {
            // isUnbounded: int -> Bool
            //            : Return true if the LP is unbounded, false otherwise
            for (int i = 0; i < constraintsNum + 1; ++i) {
                if (tableau[i][col] > 0) {
                    return false;
                }
            }
            
            return true;

        }

        void solve() {
            // solve: None -> None
            //      : Runs the simplex method by repeatedly choosing a entering variable and pivot until no entering variable could be found

            int enteringVarColIndex = chooseEnteringVar(vector<double>(tableau[0].begin() +1, tableau[0].end()-1));
            

            while (enteringVarColIndex != -1 && !isUnbounded(enteringVarColIndex)) {
                cout << "\nEntering Variable Column Index: " << enteringVarColIndex << "\n";
                cout << "\n Current Tableau:\n";
                for (const auto& row : tableau) {
                    for (double val : row) {
                        cout << val << "\t";
                    }
                    cout << "\n";
                }
                pair<int,int> pivotCoords = choosePivotElem(enteringVarColIndex);
                pivot(pivotCoords);
                enteringVarColIndex = chooseEnteringVar(vector<double>(tableau[0].begin() +1, tableau[0].end()-1));
            }

            if (isUnbounded(enteringVarColIndex)) {
                cout << "\nThe LP is unbounded!\n";
            } else {
                cout << "\nThe optimal solution is " << tableau[0][tableau[0].size()-1] << "\n";
            }
        }

};

int main() {
    Tableau tableau = Tableau();
    tableau.solve();
    return 0;
}