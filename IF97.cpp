#include "IF97.h"


int main(){
    Region1 R1;
    double v = 1/R1.rhomass(300, 3e6);
    double h = R1.hmass(300, 3e6);
    double u = R1.umass(300, 3e6);
    double s = R1.smass(300, 3e6);
    double cp = R1.cpmass(300, 3e6);
    double w = R1.speed_sound(300, 3e6);

    Region2 R2;
    double v2 = 1/R2.rhomass(300, 0.0035e6);
    double h2 = R2.hmass(300, 0.0035e6);
    double u2 = R2.umass(300, 0.0035e6);
    double s2 = R2.smass(300, 0.0035e6);
    double cp2 = R2.cpmass(300, 0.0035e6);
    double w2 = R2.speed_sound(300, 0.0035e6);

    Region4 R4;
    double p300 = R4.p_T(300);
    double p500 = R4.p_T(500);
    double p600 = R4.p_T(600);
    double T0p1 = R4.T_p(0.1e6);
    double T1 = R4.T_p(1e6);
    double T10 = R4.T_p(10e6);

    Region5 R5;
    double v5 = 1/R5.rhomass(1500, 0.5e6);
    double h5 = R5.hmass(1500, 0.5e6);
    double u5 = R5.umass(1500, 0.5e6);
    double s5 = R5.smass(1500, 0.5e6);
    double cp5 = R5.cpmass(1500, 0.5e6);
    double w5 = R5.speed_sound(1500, 0.5e6);

    return 0;
}