// This compiler flag causes input/output units on the Thermodynamic Properties in IF97.h
// to take pressure units of [MPa] and Energy units of [kJ] for comparison with IAPWS
// table values.  If not set, the default behavior of IF97.h is to use straight SI units
// with pressure in [Pa] and enthalpy in [J].
#define IAPWS_UNITS
// This compiler flag causes the Region 3 v(p,T) function to be iterated to improve
// accuracy.  If not defined, the Region 3 v(p,T) function will return the direct
// value from the supplementary release IAPWS SR5-05(2016), which may be in error
// by up to 1E-6 of the iterative solution in Region 3.
#define REGION3_ITERATE

#include "IF97.h"
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <chrono>

int main() {

    using namespace IF97;
    using namespace std;
    using namespace chrono;

    cout << "                                      Verification Tables" << std::endl << std::endl;
    std::cout << "The tables below are printed for verification purposes.  Developers should check the error levels below\n";
    std::cout << "to verify that there are no code regressions in new code updates.  Unless otherwise noted, tables are\n";
    std::cout << "reproduced from the \"Revised Release on the IAPWS Industrial Formulation 1997\" IAPWS R7-97(2012).\n\n\n";

    //
    // IAPWS-IF97 Verification Tables 5, 15, 33 from IAPWS R7-97(2012)
    //
    // Print all three tables together since they are all T,p tables and follow with a table of relative error.
    //
    double T[12] = {300, 300, 500, 300, 700, 700, 650, 650, 750, 1500, 1500, 2000};
    double p[12] = {3, 80, 3, 0.0035, 0.0035, 30, 25.5837018, 22.2930643, 78.3095639, 0.5, 30, 30};
    double v[12] = {0.00100215168, 0.000971180894, 0.001202418, 39.4913866, 92.3015898,   0.00542946619,
                    0.002,         0.005,          0.002,       1.3845509,  0.0230761299, 0.0311385219};
    double h[12] = { 115.331273, 184.142828, 975.542239, 2549.91145, 3335.68375, 2631.49474, 1863.43019,
                     2375.12401, 2258.68845, 5219.76855, 5167.23514, 6571.22604};
    double u[12] = {112.324818, 106.448356, 971.934985, 2411.6916, 3012.62819, 2468.61076, 1812.26279,
                    2263.65868, 2102.06932, 4527.4931, 4474.95124, 5637.07038};
    double s[12] = {0.392294792, 0.368563852, 2.58041912, 8.52238967, 10.1749996, 5.17540298,
                    4.05427273,  4.85438792,  4.46971906, 9.65408875, 7.72970133, 8.53640523};
    double cp[12] = { 4.17301218, 4.01008987, 4.65580682, 1.91300162, 2.08141274, 10.3505092,
                      13.8935717, 44.6579342, 6.34165359, 2.61609445, 2.72724317, 2.88569882};
    double w[12] = { 1507.73921, 1634.69054, 1240.71337, 427.920172, 644.289068, 480.386523,
                     502.005554, 383.444594, 760.696041, 917.06869, 928.548002, 1067.36948};
    double sum2 = 0, RMS1 = 0, RMS2 = 0;
    int ecount = 0;

    const char* div1 = "__________________________________________________________________________________________________________________\n";
    const char* div2 = "_______________________________________________________\n";

    cout << div1;
    cout << "                                   Verification Tables 5, 15, 33, and 42" << endl;
    cout << "                                    (Regions 1, 2, 3, 5 - 3 pts. each)" << endl;
    cout << div1;
    cout << div1;
    cout << "   T       p            v               h                u              s               cp              w" << endl;
    cout << "  [K]    [MPa]       [m^3/kg]        [kJ/kg]          [kJ/kg]        [kJ/kg-K]       [kJ/kg-K]        [m/s]" << endl;
    cout << div1;
    for (int i = 0; i < 12; i++) {
        cout << "  " << right << fixed << setprecision(0) << setw(4) << T[i];
        cout << resetiosflags(ios_base::fixed);
        cout << setprecision(7) << setw(10) << p[i];
        if (i >= 6 && i <= 8) {
            cout << fixed << setprecision(3) << setw(16) << 1.0 / rhomass_Tp(T[i], p[i]);
            cout << resetiosflags(ios_base::fixed);
            cout << scientific << setprecision(8) << setw(16);
        } else {
            cout << scientific << setprecision(8) << setw(16) << 1.0 / rhomass_Tp(T[i], p[i]);
        };
        cout << setw(16) << hmass_Tp(T[i], p[i]);
        cout << setw(16) << umass_Tp(T[i], p[i]);
        cout << setw(16) << smass_Tp(T[i], p[i]);
        cout << setw(16) << cpmass_Tp(T[i], p[i]);
        cout << setw(16) << speed_sound_Tp(T[i], p[i]);
        cout << "  " << endl;
    };
    cout << div1;
    cout << "                                                  RELATIVE ERROR" << endl;
    cout << div1;
    cout << "   T       p            v               h                u              s               cp              w" << endl;
    cout << "  [K]    [MPa]       [error]         [error]          [error]        [error]         [error]         [error]" << endl;
    cout << div1;
    for (int i = 0; i < 12; i++) {
        cout << "  " << right << fixed << setprecision(0) << setw(4) << T[i];
        cout << resetiosflags(ios_base::fixed);
        cout << setprecision(7) << setw(10) << p[i];
        cout << "    " << scientific << setprecision(4) << setw(10) << abs(1.0 / rhomass_Tp(T[i], p[i]) - v[i]) / v[i];
        sum2 += powi((1.0 / rhomass_Tp(T[i], p[i]) - v[i]) / v[i], 2); ecount++;
        cout << "      " << setw(10) << abs(hmass_Tp(T[i], p[i]) - h[i]) / h[i];
        sum2 += powi((hmass_Tp(T[i], p[i]) - h[i]) / h[i], 2); ecount++;
        cout << "      " << setw(10) << abs(umass_Tp(T[i], p[i]) - u[i]) / u[i];
        sum2 += powi((umass_Tp(T[i], p[i]) - u[i]) / u[i], 2); ecount++;
        cout << "      " << setw(10) << abs(smass_Tp(T[i], p[i]) - s[i]) / s[i];
        sum2 += powi((smass_Tp(T[i], p[i]) - s[i]) / s[i], 2); ecount++;
        cout << "      " << setw(10) << abs(cpmass_Tp(T[i], p[i]) - cp[i]) / cp[i];
        sum2 += powi((cpmass_Tp(T[i], p[i]) - cp[i]) / cp[i], 2); ecount++;
        cout << "      " << setw(10) << abs(speed_sound_Tp(T[i], p[i]) - w[i]) / w[i];
        sum2 += powi((speed_sound_Tp(T[i], p[i]) - w[i]) / w[i], 2); ecount++;
        cout << "    " << endl;
    };
    RMS1 = sqrt(sum2 / ecount);
    cout << div1;
    cout << "NOTE 1: Relative errors above should be on the order of 1E-8 or lower." << endl;
    cout << "        The RMS all relative errors (" << ecount << ") is " << scientific << setprecision(3) << RMS1 << endl << endl;
    cout << "NOTE 2: The values of v in region 3 in the above table (rows 6-8) are evaluated first using the supplemental\n"
              << "        backward equations for v(T,p) from IAPWS SR5-05(2016).  These values are then used as the initial\n"
              << "        values to iterate on the p(T,v) equation from IAPWS R7-97(2012).  IAPWS explains that the values\n"
              << "        from v(T,p) could be used directly, but that they may be up to 1E-6 in error.  By iterating on\n"
              << "        p(T,v) using the v(T,p) values as initial estimates, the relative error is reduced to the order\n"
              << "        of 1E-8 and computation time is greatly reduced." << endl << endl << endl;

    //**************************************************************************************************************
    //
    // IAPWS-IF97 Verification Tables 5, 13 from IAPWS SR5-05(2016)
    //
    // This section provides verification of the Region 3, algebraic 
    //
    //**************************************************************************************************************
    double pv3[51] = {80,   50,   80, 20, 30,   26,   30,   26,   30,   26,    30,   23.6,  24,   23.6, 24,     23.6, 24,
                      23.5, 24,   23, 24, 22.6, 23,   22.6, 22.8, 22.6, 22.8,  22.6, 22.8,  22.6, 22.8, 21.1,   21.8, 21.1,
                      21.8, 19.1, 20, 17, 20,   21.5, 22,   22.5, 22.3, 22.15, 22.3, 22.11, 22.3, 22,   22.064, 22,   22.064};
    double Tv3[51] = {670, 710, 750, 630, 650, 656,   670,   661,   675,   671,   690,   649,   650,   652,    654,    653,    655,
                     655, 660, 660, 670, 646, 646,   648.6, 649.3, 649,   649.7, 649.1, 649.9, 649.4, 650.2,  640,    643,    644,
                     648, 635, 638, 626, 640, 644.6, 646.1, 648.6, 647.9, 647.5, 648.1, 648,   649,   646.84, 647.05, 646.89, 647.15};
    double vv3[51] = {1.503831359E-3, 2.204728587E-3, 1.97369294E-3,  1.761696406E-3, 1.819560617E-3, 2.24558772E-3,  2.506897702E-3, 2.970225962E-3,
                      3.004627086E-3, 5.019029401E-3, 4.656470142E-3, 2.163198378E-3, 2.166044161E-3, 2.651081407E-3, 2.967802335E-3, 3.273916816E-3,
                      3.550329864E-3, 4.545001142E-3, 5.100267704E-3, 6.109525997E-3, 6.427325645E-3, 2.117860851E-3, 2.062374674E-3, 2.53306378E-3,
                      2.572971781E-3, 2.923432711E-3, 2.913311494E-3, 3.131208996E-3, 3.221160278E-3, 3.715596186E-3, 3.66475479E-3,  1.970999272E-3,
                      2.043919161E-3, 5.251009921E-3, 5.256844741E-3, 1.932829079E-3, 1.985387227E-3, 8.483262001E-3, 6.227528101E-3, 2.268366647E-3,
                      2.296350553E-3, 2.83237326E-3,  2.811424405E-3, 3.694032281E-3, 3.622226305E-3, 4.528072649E-3, 4.556905799E-3, 2.698354719E-3,
                      2.717655648E-3, 3.798732962E-3, 3.70194001E-3};
    cout << div2;
    cout << "   Verification Tables 5, 13 - IAPWS SR5-05(2016)" << endl;
    cout << "      (Region 3 direct formulation for v(T,p))" << endl;
    cout << div2;
    cout << div2;
    cout << "        T        p            v            Error" << endl;
    cout << "       [K]     [MPa]      [m^3/kg]         [rel]" << endl;
    cout << div2;
    sum2 = 0; ecount = 0;
    cout << resetiosflags(ios_base::fixed);
    for (int i = 0; i < 51; i++) {
        cout << defaultfloat << setprecision(5) << setw(10) << Tv3[i];
        cout << setw(10) << pv3[i];
        cout << scientific << setprecision(8) << setw(16) << 1.0 / rhomass_Tp(Tv3[i], pv3[i]) << "    ";
        cout << scientific << setprecision(4) << setw(10) << abs(1.0 / rhomass_Tp(Tv3[i], pv3[i]) - vv3[i]) / vv3[i] << " ";
        sum2 += powi((1.0 / rhomass_Tp(Tv3[i], pv3[i]) - vv3[i]) / vv3[i], 2); ecount++;
        cout << endl;
    };
    cout << div1;
    // RMS2 = sqrt(sum2 / ecount);  // Don't print RMS here since it will be high (see Note 3)
    // cout << "RMS Error = " << scientific << setprecision(3) << RMS2 << endl << endl;

    cout << "NOTE 3: Error values above should be on the order of 1E-6 or lower, except the last dozen, which are very near\n";
    cout << "        the critical point and can be as high as 1.5E-2.  However, since the calculated values are actually\n";
    cout << "        using the IF97 iterative solution in region 3, the error is actually the distance from these initial guess\n";
    cout << "        values to the more accurate iterative solution, not the actual error in the formulation.  See NOTE 3 below.\n";
    cout << "        To see the actual error in this explicit equation, undefine the REGION3_ITERATE flag at the top of this \n";
    cout << "        file to turn off the iterative solution and provide just the explicit results from v(p,T).  Doing so will\n";
    cout << "        increase the error in the previous verification table to the order of 1E-6 for points in region 3, but\n";
    cout << "        drop the relative error in this table to on the order of 1E-10.\n\n";
    cout << "NOTE 4: IAPWS-IF97 is covered by a basic equation for the Helmholtz free energy, f(v,T).  In some steam\n";
    cout << "        power cycles, thermodynamic properties as a function of (p,T) are required in region 3.  This\n";
    cout << "        requires iteration of the Helmhotz equation to find v from p and T.  To avoid this iterative\n";
    cout << "        solution, IAPWS has provided a supplementary release with explicit equations for v as a function\n";
    cout << "        of T and P in region 3, dramatically speeding up these calculations.\n\n\n\n";


    //**************************************************************************************************************
    //
    // IAPWS-IF97 Verification Tables 35 & 36 from IAPWS R7-97(2012)
    //
    // This section provides verification of the Region 3, algebraic
    //
    //**************************************************************************************************************
    double Ts[3] = {300.0, 500.0, 600.0};
    double ps[3] = {0.1, 1.0, 10.0};
    double pact[3] = {0.353658941E-2, 0.263889776E+1, 0.123443146E+2};
    double Tact[3] = {0.372755919E+3, 0.453035632E+3, 0.584149488E+3};
    double Tout = 0, pout = 0, Terr = 0, perr = 0;
    sum2 = 0; ecount = 0;

    printf("_______________________________________________________________________\n");
    printf("         Region 4: Saturation Temperature/Pressure Equations           \n");
    printf("_______________________________________________________________________\n");
    printf("_______________________________________________________________________\n");
    printf("              Table 35            |               Table 36             \n");
    printf("       Saturation Pressures       |        Saturation Temperatures     \n");
    printf("__________________________________|____________________________________\n");
    printf("  T/K       p/MPa        rel err  |  p/MPa         T/K        rel err  \n");
    printf("__________________________________|____________________________________\n");
    for (int i = 0; i < 3; i++) {
        pout = psat97(Ts[i]);
        perr = abs(pout - pact[i]) / pact[i];
        sum2 += powi((pout - pact[i]) / pact[i], 2); ecount++;
        Tout = Tsat97(ps[i]);
        Terr = abs(Tout - Tact[i]) / Tact[i];
        sum2 += powi((Tout - Tact[i]) / Tact[i], 2); ecount++;
        printf("  %3.0f  %11.9e  %8.1e  |  %4.1f     %11.8e  %8.1e\n", Ts[i], pout, perr, ps[i], Tout, Terr);
    };
    printf("_______________________________________________________________________\n");
    printf("  Relative errors above should be on the order of 1E-9 or lower.\n");
    RMS1 = sqrt(sum2 / ecount);
    printf("  The RMS of all relative errors (%d) is %5.3e\n\n", ecount, RMS1);
    //
    //  Timing test for Tsat97 and psat97 vectorization
    //
    printf("_______________________________________________________________________\n");
    printf("   Timing Test for Tsat97 and psat97 optimization \n");
    printf("_______________________________________________________________________\n");
    double tsat, psat;
    double pt = get_ptrip();                     // triple point pressure
    double pc = get_pcrit();                     // critical point pressure
    double n = 100000;                           // number of calls to Tsat97 for timing test
    double dp = (pc - pt) / n;                   // step size
    high_resolution_clock::time_point start, end;
    start = high_resolution_clock::now();        // start time
    for (double p = pt; p <= pc; p += dp) {      //    loop over n calls to Tsat97
        tsat = Tsat97(p);
    }
    end = high_resolution_clock::now();          // end time
    duration<double> dif = duration_cast<duration<double>>(end - start) * 1000.0;  // time in ms
    printf("  Timing (100k Tsat calls): %5g ms\n",dif.count());
    double Tt = get_Ttrip();                     // triple point temperature
    double Tc = get_Tcrit();                     // critical point temperature
    double dt = (Tc - Tt) / n;                   // step size
    start = high_resolution_clock::now();        // start time
    for (double T = Tt; T <= Tc; T += dt) {      //    loop over n calls to psat97
        psat = psat97(T);
    }
    end = high_resolution_clock::now();          // end time
    dif = duration_cast<duration<double>>(end - start) * 1000.0;  // time in ms
    printf("  Timing (100k psat calls): %5g ms\n",dif.count());
    printf("_______________________________________________________________________\n\n\n\n");



    cout << div1;
    cout << "                                           REVERSE FUNCTIONS\n";
    cout << div1 << endl << endl;



    // ******************************************************************************
    // Reverse Functions T(p,h) & T(p,s) from IAPWS R7-97(2012) & *IAPWS SR3-03(2014)
    // ******************************************************************************
    cout << div1;
    cout << "                                         Reverse Functions T(p,h) and T(p,s)\n\n";
    cout << "The verification table below contains contain the published T(p,h) and T(p,s) values for verification of computer\n";
    cout << "programs from Table 7 (p. 11) and Table 24 (p. 25) of [IAPWS R7-97(2012)], as well as Table 5 (p. 8) of Reference\n";
    cout << "[IAPWS SR3-03(2014)].\n";
    cout << div1;

    // Verification Points for Reverse Functions T(p,h) & T(p,s)
    char* region[18] = {"1", "1", "1", "2a", "2a", "2a", "2b", "2b", "2b", "2c", "2c", "2c", "3a", "3a", "3a", "3b", "3b", "3b"};
    double pR[18] = {3.0,   80.0,  80.0,   // Region 1,   Table 7
                     0.001,  3.0,   3.0,   // Region 2a,  Table 24
                     5.0,    5.0,  25.0,   // Region 2b,  Table 24
                     40.0,  60.0,  60.0,   // Region 2c,  Table 24
                     20.0,  50.0, 100.0,   // Region 3a,  Table 5*
                     20.0,  50.0, 100.0};  // Region 3b,  Table 5*
    double hR[18] = {500,  500,  1500,     // Region 1,   Table 7
                     3000, 3000, 4000,     // Region 2a,  Table 24
                     3500, 4000, 3500,     // Region 2b,  Table 24
                     2700, 2700, 3200,     // Region 2c,  Table 24
                     1700, 2000, 2100,     // Region 3a,  Table 5*
                     2500, 2400, 2700};    // Region 3b,  Table 5*
    double TR[18] = { 391.798509, 378.108626, 611.041229,    // Region 1,   Table 7
                      534.433241, 575.373370, 1010.77577,    // Region 2a,  Table 24
                      801.299102, 1015.31583, 875.279054,    // Region 2b,  Table 24
                      743.056411, 791.137067, 882.756860,    // Region 2c,  Table 24
                      629.3083892,690.5718338,733.6163014,   // Region 3a,  Table 5*
                      641.8418053,735.1848618,842.0460876 }; // Region 3b,  Table 5*
    //
    double pRs[18] = {3.0,  80.0,  80.0,                      // Region 1,   Table 7
                      0.1,   0.1,   2.5,                      // Region 2a,  Table 24
                      8.0,   8.0,  90.0,                      // Region 2b,  Table 24
                     20.0,  80.0,  80.0,                      // Region 2c,  Table 24
                     20.0,  50.0, 100.0,                      // Region 3a,  Table 5*
                     20.0,  50.0, 100.0};                     // Region 3b,  Table 5*
    double sR[18] = { 0.5, 0.5, 3.0,                          // Region 1,   Table 7
                      7.5, 8.0, 8.0,                          // Region 2a,  Table 24
                      6.0, 7.5, 6.0,                          // Region 2b,  Table 24
                      5.75,5.25,5.75,                         // Region 2c,  Table 24
                      3.8, 3.6, 4.0,                          // Region 3a,  Table 5*
                      5.0, 4.5, 5.0};                         // Region 3b,  Table 5*
    double TRs[18] = {307.842258,  309.979785,  565.899909,   // Region 1,   Table 7
                      399.517097,  514.127081,  1039.84917,   // Region 2a,  Table 24
                      600.48404,   1064.95556,  1038.01126,   // Region 2b,  Table 24
                      697.992849,  854.011484,  949.017998,   // Region 2c,  Table 24
                      628.2959869, 629.7158726, 705.6880237,  // Region 3a,  Table 5*
                      640.1176443, 716.3687517, 847.4332825}; // Region 3b,  Table 5*
    sum2 = 0; ecount = 0;
    cout << div1;
    printf("Region|  p/MPa  h/(kJ/kg)          T/K       rel. err. |  p/MPa  s/(kJ/kg/K)        T/K       rel. err.\n");
    cout << div1;

    for (int i = 0; i < 18; i++) {
        Tout = T_phmass(pR[i], hR[i]);
        Terr = abs(Tout - TR[i]) / TR[i];
        sum2 += powi((Tout - TR[i]) / TR[i], 2); ecount++;
        printf("  %2s  |  %5g     %4.0f     %15.8e %10.3e ",region[i],pR[i],hR[i],Tout,Terr);
        Tout = T_psmass(pRs[i], sR[i]);
        Terr = abs(Tout - TRs[i]) / TRs[i];
        sum2 += powi((Tout - TRs[i]) / TRs[i], 2); ecount++;
        printf("|  %5g     %4.2g     %15.8e %10.3e\n", pRs[i], sR[i], Tout, Terr);
    }
    cout << div1;
    RMS1 = sqrt(sum2 / ecount);
    cout << "Relative errors above should be on the order of 1E-9 or lower.\n";
    cout << "The RMS of all relative errors (" << ecount << ") is " << scientific << setprecision(3) << RMS1 << endl << endl;
    cout << "* NOTE 5: The Region 3a, 3b validation comes from Table 5 & 12 of the 2014\n";
    cout << "          \"Revised Supplementary Release on Backward Equations for the \n";
    cout << "          functions T(p,h), v(p,h) and T(p,s), v(p,s) for Region 3\"\n";
    cout << "          [IAPWS SR3-03(2014)]\" \n\n";
    cout << "  NOTE 6: While [IAPWS SR3-03(2014)] provides direct reverse functions for v(p,h) and v(p,s)\n";
    cout << "          in region 3, these are not used in this implementation because [IAPWS R7-97(2012)]\n";
    cout << "          does not provide them for regions 1, 2, and 5.  Instead, the reverse functions T(p,h)\n";
    cout << "          and T(p,s) are used to determine T, which is then used to determine v from v(p,T) in\n ";
    cout << "          all regions.  This provides a consistent approach for all regions.\n\n\n\n";



    // ******************************************************************************
    // Reverse Functions P(h,s) from IAPWS SR2-01(2014) & IAPWS SR4-04(2014)
    // ******************************************************************************
    cout << div2;
    cout << "             Reverse Function p(h,s)\n\n";
    cout << "The Enthalpy-Entropy table below contains the published p(h,s) values for \n";
    cout << "verification of computer programs from Table 3 (p.6) and Table 9 (p.10) of \n";
    cout << "[IAPWS SR2-01(2014)], as well as Table 5 (p.10) of [IAPWS SR4-04(2014)].\n";
    cout << "The last three values are Tsat points from Table 29 of [IAPWS SR4-04(2014)].\n";
    cout << div2;

    // Verification Points for Reverse Functions p(h,s)
    double hv[21] = {0.001, 90,   1500,   // Region 1,   Table 3
                     2800,  2800, 4100,   // Region 2a,  Table 9
                     2800,  3600, 3600,   // Region 2b,  Table 9
                     2800,  2800, 3400,   // Region 2c,  Table 9
                     1700,  2000, 2100,   // Region 3a,  Table 5
                     2600,  2400, 2700,   // Region 3b,  Table 5
                     1800,  2400, 2500};  // Region 4,   Table 29

    double sv[21] = {0.0, 0.0, 3.4,     // Region 1,   Table 3
                     6.5, 9.5, 9.5,     // Region 2a,  Table 9
                     6.0, 6.0, 7.0,     // Region 2b,  Table 9
                     5.1, 5.8, 5.8,     // Region 2c,  Table 9
                     3.8, 4.2, 4.3,     // Region 3a,  Table 5
                     5.1, 4.7, 5.0,     // Region 3b,  Table 5
                     5.3, 6.0, 5.5};    // Region 4,   Table 29
     
    double ptv[21] = {9.800980614e-4, 91.92954727,     58.68294423,    // Region 1,   Table 3
                     1.371012767,     1.879743844e-3,  0.1024788997,  // Region 2a,  Table 9
                     4.793911442,    83.95519209,      7.527161441,   // Region 2b,  Table 9
                     94.3920206,     8.414574124,     83.76903879,    // Region 2c,  Table 9
                     25.55703246,    45.40873468,     60.7812334,     // Region 3a,  Table 5
                     34.34999263,    63.63924887,     88.39043281,    // Region 3b,  Table 5
                     346.8475498,    425.1373305,    522.5579013};    // Region 4,   Table 29
    sum2 = 0; ecount = 0;

    cout << div2;
    printf("      |    h         s            P          error\n");
    printf("Region| [kJ/kg]  [kJ/kg/K]      [MPa]        [rel]\n");
    cout << div2;

    for (int i = 0; i < 18; i++) {
        pout = p_hsmass(hv[i], sv[i]);
        perr = abs(pout - ptv[i]) / ptv[i];
        sum2 += powi((pout - ptv[i]) / ptv[i], 2); ecount++;
        printf("  %2s  |  %5g    %5g   %15.8e %10.3e \n", region[i], hv[i], sv[i], pout, perr);
    }
    cout << div2;
    printf("      |                       Tsat/[K]\n");
    cout << div2;
    for (int i = 18; i < 21; i++) {
        Tout = T_hsmass(hv[i], sv[i]);
        Terr = abs(Tout - ptv[i]) / ptv[i];
        sum2 += powi((Tout - ptv[i]) / ptv[i], 2); ecount++;
        printf("  %2s  |  %5g    %5g   %15.8e %10.3e \n", "4", hv[i], sv[i], Tout, Terr);
    }
    cout << div2;
    RMS1 = sqrt(sum2 / ecount);
    cout << "Relative errors above should be on the order of 1E-10 or lower.\n";
    cout << "The RMS of all relative errors (" << ecount << ") is " << scientific << setprecision(3) << RMS1 << endl << endl << endl;

    cout << div1;
    cout << "                                           TRANSPORT PROPERTIES\n";
    cout << div1 << endl << endl;

    // ******************************************************************************
    // VISCOSITY Verification Values from IAPWS R12-08
    // ******************************************************************************
    cout << div2;
    cout << "                 Water Viscosity Verification\n\n";
    cout << "Pressure and Temperature points based on the tabulated computer program\n";
    cout << "verification values from [IAPWS R12-08], page 8, Table 4. Per guidance\n";
    cout << "from IAPWS, the critical enhancement, mu2, is set to 1, resulting in\n";
    cout << "slightly greater error in the lower portion of this table, very near\n";
    cout << "the critical point.  This function is temperature and density based.\n ";
    cout << "The density is determined from the IF97 formulation for the function\n";
    cout << "visc_Tp(T,p).  However, the direct density function, visc_TRho(T,rho)\n";
    cout << "is used for the verificsation table below.\n";
    cout << div2;

    double Tmu[17] = {298.15, 298.15, 373.15, 433.15, 433.15, 873.15, 873.15, 873.15, 1173.15,
                      1173.15, 1173.15, 647.35, 647.35, 647.35, 647.35, 647.35, 647.35};
    double rhomu[17] = {998, 1200, 1000, 1, 1000, 1, 100, 600, 1, 100, 400, 122, 222, 272, 322, 372, 422};
    double mu[17] = {889.7351,  1437.649467, 307.883622, 14.538324, 217.685358, 32.619287, 35.802262, 77.430195, 44.217245,
                     47.640433, 64.154608,   25.520677,  31.337589, 36.228143,  42.961579, 45.688204, 49.436256};
    double mout = 0, merr = 0;
    sum2 = 0;    ecount = 0;
    cout << "     T        rho           visc            error\n";
    cout << "    [K]    [kg/m^3]       [uPa*s]           [rel]\n";
    cout << div2;

    for (int i = 0; i < 11; i++) {
        mout = visc_TRho(Tmu[i], rhomu[i]) * 1.0e6;  // convert from Pa-s to uPa-s
        merr = abs(mout - mu[i]) / mu[i];
        sum2 += merr * merr; ecount++;
        printf("  %7.2f    %5g   %14.6f     %10.3e \n", Tmu[i], rhomu[i], mout, merr);
    }
    cout << div2;
    RMS1 = sqrt(sum2 / ecount);  // RMS1 includes first eleven points away from critical point
    sum2 = 0; ecount = 0;
    for (int i = 11; i < 17; i++) {
        mout = visc_TRho(Tmu[i], rhomu[i]) * 1.0e6;  // convert from Pa-s to uPa-s
        merr = abs(mout - mu[i]) / mu[i];
        sum2 += merr * merr; ecount++;
        printf("  %7.2f    %5g   %14.6f     %10.3e \n", Tmu[i], rhomu[i], mout, merr);
    }
    cout << div2;
    RMS2 = sqrt(sum2 / ecount);  // RMS2 includes last six points near critical point
    cout << "Relative errors above should be on the order of 1E-8 or lower, except near the critical point, where they\n";
    cout << "may be as high as 8.417E-2.  This is due to the critical enhancement, mu2, being set to 1, per IAPWS guidance\n";
    cout << "for industrial use.  RMS error for first eleven points is " << scientific << setprecision(3) << RMS1;
    cout << " (should be 1.095e-8 or less)." << endl;
    cout << "RMS error for last six points is " << fixed << setprecision(2) << RMS2 * 100.0 << "% near the critical point." << endl << endl << endl;

    // ******************************************************************************
    // THERMAL CONDUCTIVITY Verification Values from IAPWS R15-11
    // ******************************************************************************
    cout << div2;
    cout << "       Water Thermal Conductivity Verification         \n\n";
    cout << "Pressure and Temperature points based on the tabulated\n";
    cout << "computer program verification values from [IAPWS R15-11],\n";
    cout << "page 13, Tables 7,8,9. Per guidance from IAPWS, all input\n";
    cout << "properties are calculated using the standard IF97 forward\n";
    cout << "functions and the dimensionless isothermal compressibility,\n";
    cout << "zeta, is set to a simplified correlation, resulting in \n";
    cout << "slightly greater error in the lower portion of this table,\n";
    cout << "very near the critical point.\n";
    cout << "This function is temperature, pressure, and density based\n";
    cout << "with density determined from the IF97 density function.\n";
    cout << div2;

    double Tk[13] = {620, 620, 650, 800, 647.35, 647.35, 647.35, 647.35, 647.35, 647.35, 647.35, 647.35, 647.35};
    double Pk[13] = {20,          50,          0.3,         50,          21.98406271345, 22.1321600249828, 0.297422657,
                     19.45771946, 21.98406271, 22.11526557, 22.13216002, 22.15298122,    22.33268694};
    double rhok[13] = {613.227777440321, 699.226043285397, 1.00452140735385, 218.030012152047, 222,
                       322, 1, 122, 222, 272, 322, 372, 422};
    double k[13] = {0.481485195, 0.54503894, 0.0522311024, 0.177709914, 0.36687941, 1.24182415, 51.9298924,
                    130.922885,  367.787459, 757.959776,   1443.75556,  650.319402, 448.883487};
    double kout = 0, kerr = 0;
    sum2 = 0; ecount = 0;
    cout << "   T         P        rho      Conductivity     error\n";
    cout << "  [K]      [MPa]    [kg/m^3]     [mW/m/K]       [rel]\n";
    cout << div2;

    for (int i = 0; i < 6; i++) {
        kout = tcond_Tp(Tk[i], Pk[i]);  // use 2-input function
        kerr = abs(kout - k[i]) / k[i];
        sum2 += kerr * kerr; ecount++;
        printf("%6.2f %11.10g %10.9g %13.7f  %10.3e \n", Tk[i], Pk[i], rhok[i], kout*1000.0, kerr);
    }
    cout << div2;
    RMS1 = sqrt(sum2 / ecount);  // RMS1 includes first eleven points away from critical point
    sum2 = 0; ecount = 0;
    for (int i = 6; i < 13; i++) {
        kout = tcond_Tp(Tk[i], Pk[i]) * 1000.0 ;  // use 2-input function
        kerr = abs(kout - k[i]) / k[i];
        sum2 += kerr * kerr;
        ecount++;
        printf("%6.2f %11.10g %10g %13.6f  %10.3e \n", Tk[i], Pk[i], rhok[i], kout, kerr);
    }
    cout << div2;
    RMS2 = sqrt(sum2 / ecount);  // RMS2 includes last seven points near critical point
    cout << "Relative errors above should be on the order of 1E-9 or lower, except near the critical point, where they\n";
    cout << "may be as high as 1.4E-1.  This is due to the critical enhancement being simplified, per IAPWS guidance\n";
    cout << "for industrial use.  RMS error for first six points is " << scientific << setprecision(3) << RMS1;
    cout << " (should be 1.763e-9 or less)." << endl;
    cout << "RMS error for last seven points is " << fixed << setprecision(2) << RMS2 * 100.0 << "% near the critical point." << endl << endl << endl;

    // ******************************************************************************
    // SURFACE TENSION Verification Values from IAPWS R1-76(2014)
    // ******************************************************************************
    cout << div2;
    cout << "         Water Surface Tension Verification           \n\n";
    cout << "Temperature points based on the tabulated computer program\n";
    cout << "verification values from [IAPWS R1-76(2014)],\n";
    cout << "pages 4-5, Table 1.\n";
    cout << div2;

    double Tsig[] = {0.01, 5,   10,  15,  20,  25,  30,  35,  40,  45,  50,  55,  60,  65,  70,  75,  80,  85,  90,  95,  100, 105, 110, 115, 120,
                     125,  130, 135, 140, 145, 150, 155, 160, 165, 170, 175, 180, 185, 190, 195, 200, 205, 210, 215, 220, 225, 230, 235, 240, 245,
                     250,  255, 260, 265, 270, 275, 280, 285, 290, 295, 300, 305, 310, 315, 320, 325, 330, 335, 340, 345, 350, 355, 360, 365, 370};
    double sig[] = {75.64, 74.94, 74.23, 73.49, 72.74, 71.98, 71.19, 70.41, 69.59, 68.78, 67.93, 67.09, 66.24, 65.36, 64.47,
                    63.57, 62.68, 61.76, 60.82, 59.88, 58.92, 57.95, 56.97, 55.98, 54.97, 53.96, 52.94, 51.9,  50.86, 49.81,
                    48.75, 47.67, 46.58, 45.49, 44.4,  43.3,  42.19, 41.07, 39.95, 38.82, 37.68, 36.54, 35.4,  34.24, 33.09,
                    31.92, 30.76, 29.58, 28.4,  27.22, 26.05, 24.86, 23.66, 22.46, 21.29, 20.14, 18.93, 17.76, 16.6,  15.45,
                    14.3,  13.18, 12.04, 10.92, 9.81,  8.73,  7.66,  6.61,  5.59,  4.6,   3.64,  2.74,  1.89,  1.12,  0.45};
    int nsig = sizeof(Tsig) / sizeof(Tsig[0]);
    double sigout = 0, sigerr = 0;

    sum2 = 0; ecount = 0;

    cout << div2;
    cout << "     T           sigma          error\n";
    cout << "    [K]          [mN/m]         [rel]\n";
    cout << div2;
    for (int i = 0; i < nsig; i++) {
        sigout = sigma97(Tsig[i] + 273.15) * 1000.0;  // convert from N/m to mN/m
        sigerr = abs(sigout - sig[i]) / sig[i];
        sum2 += sigerr * sigerr;
        ecount++;
        printf(" %6g      %10.2f      %10.3e \n", Tsig[i], sigout, sigerr);
    }
    cout << div2;
    RMS1 = sqrt(sum2 / ecount);
    cout << "Relative errors above should be on the order of 1E-3 or lower @ T < 260 C\nand on the order of 1E-2 @ T >= 260 C.\n";
    cout << "The RMS of all relative errors (" << ecount << ") is " << scientific << setprecision(3) << RMS1 << endl << endl;

    return 0;
}
