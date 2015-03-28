#ifndef IF97_H
#define IF97_H

#include <vector>
#include <cmath>

struct RegionIdealElement
{
    int J; ///< The first index
    double n; ///< The leading numerical constant
};
struct RegionResidualElement
{
    int I, ///< The first index
        J; ///< The second index
    double n; ///< The leading numerical constant
};

class BaseRegion
{
public:
    BaseRegion(std::vector<RegionResidualElement> resid, std::vector<RegionIdealElement> ideal) : R(461.526){
        for (std::size_t i = 0; i < resid.size(); ++i){
            nr.push_back(resid[i].n);
            Ir.push_back(resid[i].I);
            Jr.push_back(resid[i].J);
        }
        for (std::size_t i = 0; i < ideal.size(); ++i){
            n0.push_back(ideal[i].n);
            J0.push_back(ideal[i].J);
        }
    }
    double rhomass(double T, double p){
        double PI = p/p_star;
        return p/(PI*R*T*(dgamma0_dPI(T,p) + dgammar_dPI(T,p)));
    }
    double hmass(double T, double p){
        double tau = T_star/T;
        return R*T*tau*(dgamma0_dTAU(T, p) + dgammar_dTAU(T, p));
    }
    double smass(double T, double p){
        double tau = T_star/T;
        return R*(tau*(dgamma0_dTAU(T, p) + dgammar_dTAU(T, p)) - (gammar(T, p) + gamma0(T, p)));
    }
    double umass(double T, double p){
        double tau = T_star/T, PI = p/p_star;
        return R*T*(tau*(dgamma0_dTAU(T, p) + dgammar_dTAU(T, p)) - PI*(dgamma0_dPI(T, p) + dgammar_dPI(T, p)));
    }
    double cpmass(double T, double p){
        double tau = T_star/T;
        return -R*tau*tau*(d2gammar_dTAU2(T, p) + d2gamma0_dTAU2(T, p));
    }
    double cvmass(double T, double p){
        double tau = T_star/T, PI = p/p_star;
        return cpmass(T,p)-R*pow(1 + PI*dgammar_dPI(T,p) - tau*PI*d2gammar_dPIdTAU(T,p),2)/(1-PI*PI*d2gammar_dPI2(T, p));
    }
    double speed_sound(double T, double p){
        double tau = T_star/T, PI = p/p_star;
        double RHS = (1 + 2*PI*dgammar_dPI(T,p) + PI*PI*pow(dgammar_dPI(T,p),2))/((1-PI*PI*d2gammar_dPI2(T,p)) +pow(1 + PI*dgammar_dPI(T,p) - tau*PI*d2gammar_dPIdTAU(T,p), 2)/(tau*tau*(d2gamma0_dTAU2(T,p) + d2gammar_dTAU2(T,p))));
        return sqrt(R*T*RHS);
    }
    virtual double PIrterm(double) = 0;
    virtual double TAUrterm(double) = 0;
    virtual double TAU0term(double) = 0;

protected:
    std::vector<int> Ir, Jr;
    std::vector<double> nr;
    std::vector<int> J0;
    std::vector<double> n0;
    double T_star, p_star;
    const double R;
   
    double gammar(double T, double p){
        double _PI = PIrterm(p), _TAU = TAUrterm(T), summer = 0;
        for (std::size_t i = 0; i < Jr.size(); ++i){
            summer += nr[i]*pow(_PI, Ir[i])*pow(_TAU, Jr[i]);
        }
        return summer;
    }
    double dgammar_dPI(double T, double p){
        double _PI = PIrterm(p), _TAU = TAUrterm(T), summer = 0;
        for (std::size_t i = 0; i < Jr.size(); ++i){
            summer += nr[i]*Ir[i]*pow(_PI, Ir[i]-1)*pow(_TAU, Jr[i]);
        }
        return summer;
    }
    double d2gammar_dPI2(double T, double p){
        double _PI = PIrterm(p), _TAU = TAUrterm(T), summer = 0;
        for (std::size_t i = 0; i < Jr.size(); ++i){
            summer += nr[i]*Ir[i]*(Ir[i]-1)*pow(_PI, Ir[i]-2)*pow(_TAU, Jr[i]);
        }
        return summer;
    }
    double dgammar_dTAU(double T, double p){
        double _PI = PIrterm(p), _TAU = TAUrterm(T), summer = 0;
        for (std::size_t i = 0; i < Jr.size(); ++i){
            summer += nr[i]*Jr[i]*pow(_PI, Ir[i])*pow(_TAU, Jr[i]-1);
        }
        return summer;
    }
    double d2gammar_dPIdTAU(double T, double p){
        double _PI = PIrterm(p), _TAU = TAUrterm(T), summer = 0;
        for (std::size_t i = 0; i < Jr.size(); ++i){
            summer += nr[i]*Jr[i]*Ir[i]*pow(_PI, Ir[i]-1)*pow(_TAU, Jr[i]-1);
        }
        return summer;
    }
    double d2gammar_dTAU2(double T, double p){
        double _PI = PIrterm(p), _TAU = TAUrterm(T), summer = 0;
        for (std::size_t i = 0; i < Jr.size(); ++i){
            summer += nr[i]*Jr[i]*(Jr[i]-1)*pow(_PI, Ir[i])*pow(_TAU, Jr[i]-2);
        }
        return summer;
    }
    double gamma0(double T, double p){
        if (J0.size() == 0){ return 0; } // Region 1 has no term
        double PI = p/p_star, _TAU = TAU0term(T);
        double summer = log(PI);
        for (std::size_t i = 0; i < n0.size(); ++i){
            summer += n0[i]*pow(_TAU, J0[i]);
        }
        return summer;
    }
    double dgamma0_dPI(double T, double p){
        if (J0.size() == 0){ return 0; } // Region 1 has no term
        double PI = p/p_star;
        return 1/PI;
    }
    double d2gamma0_dPI2(double T, double p){
        if (J0.size() == 0){ return 0; } // Region 1 has no term
        double PI = p/p_star;
        return -1/(PI*PI);
    }
    double dgamma0_dTAU(double T, double p){
        double PI = p/p_star, _TAU = TAU0term(T), summer = 0;
        for (std::size_t i = 0; i < J0.size(); ++i){
            summer += n0[i]*J0[i]*pow(_TAU, J0[i]-1);
        }
        return summer;
    }
    double d2gamma0_dTAU2(double T, double p){
        double PI = p/p_star, _TAU = TAU0term(T), summer = 0;
        for (std::size_t i = 0; i < J0.size(); ++i){
            summer += n0[i]*J0[i]*(J0[i]-1)*pow(_TAU, J0[i]-2);
        }
        return summer;
    }
};

/********************************************************************************/
/**************************       Region #1       *******************************/
/********************************************************************************/
static RegionResidualElement Region1residdata[] = {
    // Note: the coefficients of n_i have been multiplied by -1**I_i such that all Gibbs terms are of the form (PI-7.1)**(I_i) rather than (7.1-PI)**(I_i)
    {0, -2, 0.14632971213167},
    {0, -1, -0.84548187169114},
    {0, 0, -3.756360367204},
    {0, 1, 3.3855169168385},
    {0, 2, -0.95791963387872},
    {0, 3, 0.15772038513228},
    {0, 4, -0.016616417199501},
    {0, 5, 0.00081214629983568},
    {1, -9, -0.00028319080123804},
    {1, -7, 0.00060706301565874},
    {1, -1, 0.018990068218419},
    {1, 0, 0.032529748770505},
    {1, 1, 0.021841717175414},
    {1, 3, 0.00005283835796993},
    {2, -3, -0.00047184321073267},
    {2, 0, -0.00030001780793026},
    {2, 1, 0.000047661393906987},
    {2, 3, -4.4141845330846E-06},
    {2, 17, -7.2694996297594E-16},
    {3, -4, 0.000031679644845054},
    {3, 0, 2.8270797985312E-06},
    {3, 6, 8.5205128120103E-10},
    {4, -5, -0.0000022425281908},
    {4, -2, -6.5171222895601E-07},
    {4, 10, -1.4341729937924E-13},
    {5, -8, 4.0516996860117E-07},
    {8, -11, -1.2734301741641E-09},
    {8, -6, -1.7424871230634E-10},
    {21, -29, 6.8762131295531E-19},
    {23, -31, -1.4478307828521E-20},
    {29, -38, -2.6335781662795E-23},
    {30, -39, -1.1947622640071E-23},
    {31, -40, -1.8228094581404E-24},
    {32, -41, -9.3537087292458E-26}
};
static std::vector<RegionResidualElement> reg1rdata(Region1residdata, Region1residdata + sizeof(Region1residdata)/sizeof(RegionResidualElement));
static std::vector<RegionIdealElement> reg10data;
class Region1 : public BaseRegion
{
public:
    Region1() : BaseRegion(reg1rdata, reg10data)  {
        T_star = 1386; p_star = 16.53e6; 
    };    
    double speed_sound(double T, double p){
        /// Evidently this formulation is special for some reason, and cannot be implemented using the base class formulation
        double tau = T_star/T, PI = p/p_star;
        double RHS = pow(dgammar_dPI(T,p), 2)/(pow(dgammar_dPI(T,p)-tau*d2gammar_dPIdTAU(T,p), 2)/(tau*tau*d2gammar_dTAU2(T,p)) - d2gammar_dPI2(T, p));
        return sqrt(R*T*RHS);
    }
    double TAUrterm(double T){
        return T_star/T - 1.222;
    }
    double PIrterm(double p){
        return p/p_star - 7.1;
    }
    double TAU0term(double T){return 0.0;}
};


/********************************************************************************/
/**************************       Region #2       *******************************/
/********************************************************************************/
static RegionResidualElement Region2residdata[] = {
    {1,0,-0.0017731742473213},
    {1,1,-0.017834862292358},
    {1,2,-0.045996013696365},
    {1,3,-0.057581259083432},
    {1,6,-0.05032527872793},
    {2,1,-0.000033032641670203},
    {2,2,-0.00018948987516315},
    {2,4,-0.0039392777243355},
    {2,7,-0.043797295650573},
    {2,36,-0.000026674547914087},
    {3,0,2.0481737692309E-08},
    {3,1,4.3870667284435E-07},
    {3,3,-0.00003227767723857},
    {3,6,-0.0015033924542148},
    {3,35,-0.040668253562649},
    {4,1,-7.8847309559367E-10},
    {4,2,1.2790717852285E-08},
    {4,3,4.8225372718507E-07},
    {5,7,2.2922076337661E-06},
    {6,3,-1.6714766451061E-11},
    {6,16,-0.0021171472321355},
    {6,35,-23.895741934104},
    {7,0,-5.905956432427E-18},
    {7,11,-1.2621808899101E-06},
    {7,25,-0.038946842435739},
    {8,8,1.1256211360459E-11},
    {8,36,-8.2311340897998},
    {9,13,1.9809712802088E-08},
    {10,4,1.0406965210174E-19},
    {10,10,-1.0234747095929E-13},
    {10,14,-1.0018179379511E-09},
    {16,29,-8.0882908646985E-11},
    {16,50,0.10693031879409},
    {18,57,-0.33662250574171},
    {20,20,8.9185845355421E-25},
    {20,35,3.0629316876232E-13},
    {20,48,-4.2002467698208E-06},
    {21,21,-5.9056029685639E-26},
    {22,53,3.7826947613457E-06},
    {23,39,-1.2768608934681E-15},
    {24,26,7.3087610595061E-29},
    {24,40,5.5414715350778E-17},
    {24,58,-9.436970724121E-07}
};

static RegionIdealElement Region2idealdata[] = {
{0, -0.96927686500217e1},
{1, 0.10086655968018e2},
{-5, -0.56087911283020e-2 },
{-4, 0.71452738081455e-1},
{-3, -0.40710498223928},
{-2, 0.14240819171444e1},
{-1, -0.43839511319450e1},
{2, -0.28408632460772},
{3, 0.21268463753307e-1},
};
static std::vector<RegionResidualElement> reg2rdata(Region2residdata, Region2residdata + sizeof(Region2residdata)/sizeof(RegionResidualElement));
static std::vector<RegionIdealElement> reg20data(Region2idealdata, Region2idealdata + sizeof(Region2idealdata)/sizeof(RegionIdealElement));
class Region2 : public BaseRegion
{
public:
    Region2() : BaseRegion(reg2rdata, reg20data)  {
        T_star = 540; p_star = 1e6; 
    };
    double TAUrterm(double T){
        return T_star/T - 0.5;
    }
    double PIrterm(double p){
        return p/p_star;
    }
    double TAU0term(double T){return T_star/T;}
};



/********************************************************************************/
/**************************       Region #5       *******************************/
/********************************************************************************/
static RegionResidualElement Region5residdata[] = {
    {1, 1,  0.15736404855259e-2},
    {1, 2,  0.90153761673944e-3},
    {1, 3, -0.50270077677648e-2},
    {2, 3,  0.22440037409485e-5},
    {2, 9, -0.41163275453471e-5},
    {3, 7,  0.37919454822955e-7}
};
static RegionIdealElement Region5idealdata[] = {
    { 0, -0.13179983674201e2},
    { 1,  0.68540841634434e1},
    {-3, -0.24805148933466e-1},
    {-2,  0.36901534980333},
    {-1, -0.31161318213925e1},
    { 2, -0.32961626538917}
};
static std::vector<RegionResidualElement> reg5rdata(Region5residdata, Region5residdata + sizeof(Region5residdata)/sizeof(RegionResidualElement));
static std::vector<RegionIdealElement> reg50data(Region5idealdata, Region5idealdata + sizeof(Region5idealdata)/sizeof(RegionIdealElement));

class Region5 : public BaseRegion
{
public:
    Region5() : BaseRegion(reg5rdata, reg50data)  {
        T_star = 1000; p_star = 1e6; 
    };
    double TAUrterm(double T){
        return T_star/T;
    }
    double PIrterm(double p){
        return p/p_star;
    }
    double TAU0term(double T){return T_star/T;}
};

#endif
