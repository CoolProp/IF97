#include "IF97.h"
#include <cstdio>

int main(){

    using namespace IF97;

    double T1 = 300, T2 = 300, T3 = 500, p1 = 3e6, p2 = 80e6, p3 = 3e6;
    printf("***************************************************************\n");
    printf("******************** Table 5 - Region 1 ***********************\n");
    printf("***************************************************************\n");
    printf("%5s %11.9e %11.9e %11.9e\n", "v", 1/IF97_rhomass_Tp(T1, p1), 1/IF97_rhomass_Tp(T2, p2), 1/IF97_rhomass_Tp(T3, p3));
    printf("%5s %11.9e %11.9e %11.9e\n", "h", IF97_hmass_Tp(T1, p1), IF97_hmass_Tp(T2, p2), IF97_hmass_Tp(T3, p3));
    printf("%5s %11.9e %11.9e %11.9e\n", "u", IF97_umass_Tp(T1, p1), IF97_umass_Tp(T2, p2), IF97_umass_Tp(T3, p3));
    printf("%5s %11.9e %11.9e %11.9e\n", "s", IF97_smass_Tp(T1, p1), IF97_smass_Tp(T2, p2), IF97_smass_Tp(T3, p3));
    printf("%5s %11.9e %11.9e %11.9e\n", "cp", IF97_cpmass_Tp(T1, p1), IF97_cpmass_Tp(T2, p2), IF97_cpmass_Tp(T3, p3));
    printf("%5s %11.9e %11.9e %11.9e\n", "w", IF97_speed_sound_Tp(T1, p1), IF97_speed_sound_Tp(T2, p2), IF97_speed_sound_Tp(T3, p3));
    printf("***************************************************************\n\n");
    
    T1 = 300, T2 = 700, T3 = 700, p1 = 0.0035e6, p2 = 0.0035e6, p3 = 30e6;
    printf("***************************************************************\n");
    printf("******************* Table 15 - Region 2 ***********************\n");
    printf("***************************************************************\n");
    printf("%5s %11.9e %11.9e %11.9e\n", "v", 1/IF97_rhomass_Tp(T1, p1), 1/IF97_rhomass_Tp(T2, p2), 1/IF97_rhomass_Tp(T3, p3));
    printf("%5s %11.9e %11.9e %11.9e\n", "h", IF97_hmass_Tp(T1, p1), IF97_hmass_Tp(T2, p2), IF97_hmass_Tp(T3, p3));
    printf("%5s %11.9e %11.9e %11.9e\n", "s", IF97_smass_Tp(T1, p1), IF97_smass_Tp(T2, p2), IF97_smass_Tp(T3, p3));
    printf("%5s %11.9e %11.9e %11.9e\n", "cp", IF97_cpmass_Tp(T1, p1), IF97_cpmass_Tp(T2, p2), IF97_cpmass_Tp(T3, p3));
    printf("%5s %11.9e %11.9e %11.9e\n", "w", IF97_speed_sound_Tp(T1, p1), IF97_speed_sound_Tp(T2, p2), IF97_speed_sound_Tp(T3, p3));
    printf("***************************************************************\n\n");

    T1 = 1500, T2 = 1500, T3 = 2000, p1 = 0.5e6, p2 = 30e6, p3 = 30e6;
    printf("***************************************************************\n");
    printf("******************* Table 42 - Region 5 ***********************\n");
    printf("***************************************************************\n");
    printf("%5s %11.9e %11.9e %11.9e\n", "v", 1/IF97_rhomass_Tp(T1, p1), 1/IF97_rhomass_Tp(T2, p2), 1/IF97_rhomass_Tp(T3, p3));
    printf("%5s %11.9e %11.9e %11.9e\n", "h", IF97_hmass_Tp(T1, p1), IF97_hmass_Tp(T2, p2), IF97_hmass_Tp(T3, p3));
    printf("%5s %11.9e %11.9e %11.9e\n", "s", IF97_smass_Tp(T1, p1), IF97_smass_Tp(T2, p2), IF97_smass_Tp(T3, p3));
    printf("%5s %11.9e %11.9e %11.9e\n", "cp", IF97_cpmass_Tp(T1, p1), IF97_cpmass_Tp(T2, p2), IF97_cpmass_Tp(T3, p3));
    printf("%5s %11.9e %11.9e %11.9e\n", "w", IF97_speed_sound_Tp(T1, p1), IF97_speed_sound_Tp(T2, p2), IF97_speed_sound_Tp(T3, p3));
    printf("***************************************************************\n");

    Region3 R3;
    double T = 650, rho = 500;
    double p_3 = R3.p(T, rho);
    double u_3 = R3.umass(T, rho);
    double s_3 = R3.smass(T, rho);
    double cp_3 = R3.cpmass(T, rho);
    return 0;
}