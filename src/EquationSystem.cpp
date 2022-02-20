#include "include/EquationSystem.hpp"

equationSystem::equationSystem(){

}

equationSystem::~equationSystem(){
    delete fn1;
    delete fn2;
}

void equationSystem::introduceEquations(string eq1, string eq2){
    fn1->prepare(eq1);
    fn2->prepare(eq2);
}

void equationSystem::solve(double *x, double *y){
    double i=0, diference=1, distancePoints;
    struct point{
        double x=0;
        double y=0;
    }p1, p2;
    p1.y=fn1->solve(i);
    p2.y=fn2->solve(i);
    distancePoints=abs(p1.y-p2.y);
    i+=diference;
    p1.y=fn1->solve(i);
    p2.y=fn2->solve(i);
    if(abs(p1.y-p2.y)>distancePoints) diference=-diference;
    distancePoints=abs(p1.y-p2.y);
    i+=diference;
    while(true){
        i+=diference;
        p1.y=fn1->solve(i);
        p2.y=fn2->solve(i);
        if(abs(p1.y-p2.y)>distancePoints){
            diference=-diference/10;
        }else if(p1.y==p2.y||abs(p1.y-p2.y)<0.001||diference==abs(p1.y-p2.y)) break;
        distancePoints=abs(p1.y-p2.y); 
    }
    *x=i;
    *y=p1.y;
}
