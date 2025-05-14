// #include "tableau.h"
#include "newTableau.h"

class SimplexSolver {
    private:
        Tableau p1;
        Tableau p2;
    public:
        SimplexSolver(Tableau p2);

        // returns an mxm identity matrix
        std::vector<std::vector<double>> constructIdentityMatrix(int m);

        // construct phase 1 tableau
        void constructPhase1Tableau();

        // returns phase 1 tableau
        Tableau getPhase1Tableau();

        // Runs the simplex method by repeatedly choosing an entering variable and pivot until no entering variable could be found
        Tableau solveHelper(Tableau t);

        void solve();
};