#include <iostream>
#include "funcion.hpp"

using namespace std;

class equationSystem{
    private:
        funcion *fn1=new funcion();
        funcion *fn2=new funcion();
    public:
        equationSystem();
            ~equationSystem();
        void introduceEquations(string eq1, string eq2);
        void solve(double *x, double *y);
};