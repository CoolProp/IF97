#define ENABLE_CATCH

#include "IF97.h"
#include <cstdio>

int main(){

    using namespace IF97;

    double T1 = 300, T2 = 300, T3 = 500, p1 = 3e6, p2 = 80e6, p3 = 3e6;
    printf("***************************************************************\n");
    printf("******************** Table 5 - Region 1 ***********************\n");
    printf("***************************************************************\n");
    printf("%5s %11.9e %11.9e %11.9e\n", "v", 1/rhomass_Tp(T1, p1), 1/rhomass_Tp(T2, p2), 1/rhomass_Tp(T3, p3));
    printf("%5s %11.9e %11.9e %11.9e\n", "h", hmass_Tp(T1, p1), hmass_Tp(T2, p2), hmass_Tp(T3, p3));
    printf("%5s %11.9e %11.9e %11.9e\n", "u", umass_Tp(T1, p1), umass_Tp(T2, p2), umass_Tp(T3, p3));
    printf("%5s %11.9e %11.9e %11.9e\n", "s", smass_Tp(T1, p1), smass_Tp(T2, p2), smass_Tp(T3, p3));
    printf("%5s %11.9e %11.9e %11.9e\n", "cp", cpmass_Tp(T1, p1), cpmass_Tp(T2, p2), cpmass_Tp(T3, p3));
    printf("%5s %11.9e %11.9e %11.9e\n", "w", speed_sound_Tp(T1, p1), speed_sound_Tp(T2, p2), speed_sound_Tp(T3, p3));
    printf("***************************************************************\n\n");
    
    T1 = 300, T2 = 700, T3 = 700, p1 = 0.0035e6, p2 = 0.0035e6, p3 = 30e6;
    printf("***************************************************************\n");
    printf("******************* Table 15 - Region 2 ***********************\n");
    printf("***************************************************************\n");
    printf("%5s %11.9e %11.9e %11.9e\n", "v", 1/rhomass_Tp(T1, p1), 1/rhomass_Tp(T2, p2), 1/rhomass_Tp(T3, p3));
    printf("%5s %11.9e %11.9e %11.9e\n", "h", hmass_Tp(T1, p1), hmass_Tp(T2, p2), hmass_Tp(T3, p3));
    printf("%5s %11.9e %11.9e %11.9e\n", "s", smass_Tp(T1, p1), smass_Tp(T2, p2), smass_Tp(T3, p3));
    printf("%5s %11.9e %11.9e %11.9e\n", "cp", cpmass_Tp(T1, p1), cpmass_Tp(T2, p2), cpmass_Tp(T3, p3));
    printf("%5s %11.9e %11.9e %11.9e\n", "w", speed_sound_Tp(T1, p1), speed_sound_Tp(T2, p2), speed_sound_Tp(T3, p3));
    printf("***************************************************************\n\n");

    T1 = 650, T2 = 650, T3 = 750, p1 = 25.5837018e6, p2 = 22.2930643e6, p3 = 78.3095639e6;
    printf("***************************************************************\n");
    printf("******************* Table 33 - Region 3 ***********************\n");
    printf("***************************************************************\n");
    printf("%5s %11.9e %11.9e %11.9e\n", "rho", rhomass_Tp(T1, p1), rhomass_Tp(T2, p2), rhomass_Tp(T3, p3));
    printf("%5s %11.9e %11.9e %11.9e\n", "h", hmass_Tp(T1, p1), hmass_Tp(T2, p2), hmass_Tp(T3, p3));
    printf("%5s %11.9e %11.9e %11.9e\n", "s", smass_Tp(T1, p1), smass_Tp(T2, p2), smass_Tp(T3, p3));
    printf("%5s %11.9e %11.9e %11.9e\n", "cp", cpmass_Tp(T1, p1), cpmass_Tp(T2, p2), cpmass_Tp(T3, p3));
    printf("%5s %11.9e %11.9e %11.9e\n", "w", speed_sound_Tp(T1, p1), speed_sound_Tp(T2, p2), speed_sound_Tp(T3, p3));
    printf("***************************************************************\n\n");

    T1 = 1500, T2 = 1500, T3 = 2000, p1 = 0.5e6, p2 = 30e6, p3 = 30e6;
    printf("***************************************************************\n");
    printf("******************* Table 42 - Region 5 ***********************\n");
    printf("***************************************************************\n");
    printf("%5s %11.9e %11.9e %11.9e\n", "v", 1/rhomass_Tp(T1, p1), 1/rhomass_Tp(T2, p2), 1/rhomass_Tp(T3, p3));
    printf("%5s %11.9e %11.9e %11.9e\n", "h", hmass_Tp(T1, p1), hmass_Tp(T2, p2), hmass_Tp(T3, p3));
    printf("%5s %11.9e %11.9e %11.9e\n", "s", smass_Tp(T1, p1), smass_Tp(T2, p2), smass_Tp(T3, p3));
    printf("%5s %11.9e %11.9e %11.9e\n", "cp", cpmass_Tp(T1, p1), cpmass_Tp(T2, p2), cpmass_Tp(T3, p3));
    printf("%5s %11.9e %11.9e %11.9e\n", "w", speed_sound_Tp(T1, p1), speed_sound_Tp(T2, p2), speed_sound_Tp(T3, p3));
    printf("***************************************************************\n");

    Region3 R3;
    double T = 650, rho = 500;
    double p_3 = R3.p(T, rho);
    double u_3 = R3.umass(T, rho);
    double s_3 = R3.smass(T, rho);
    double cp_3 = R3.cpmass(T, rho);

    print_IF97_Table5();
    print_boundary_line_Table3();

    Region4 R4;
    double p623 = R4.p_T(623.15);

    IF97::Region3Backwards::Region3a R3a;
    double vv = R3a.v(630, 50e6);
    return 0;
}