// if97_sph stub - Interfaces CoolProp IF97 function to Mathcad
//

// this code executes the user function if97_sph(P,S), which is a wrapper for
// the CoolProp-IF97 function, hmass_psmass(P,S), used to calculate the density
// in terms of pressure and entropy
LRESULT  if97_SPH(
    LPCOMPLEXSCALAR c,  // pointer to the result (density)
    LPCCOMPLEXSCALAR a, // pointer to the pressure parameter received from Mathcad
    LPCCOMPLEXSCALAR b) // pointer to the entropy parameter received from Mathcad
{  
    // first check to make sure "a" and "b" have no imaginary component
    if ( a->imag != 0.0 )
        return MAKELRESULT(MUST_BE_REAL,1);
    if ( b->imag != 0.0 )
        return MAKELRESULT(MUST_BE_REAL,2);

    //otherwise, all is well, evaluate function
    try {
        c->real = IF97::smass_phmass(a->real,b->real);
    }
    catch (const std::out_of_range& e) { 
        if (e.what()[0] == 'P') 
            return MAKELRESULT(P_OUT_OF_RANGE,1);
        else if (e.what()[0] == 'T')  // (e.what == "Temperature")
            return MAKELRESULT(T_OUT_OF_RANGE,2);
        else if (e.what()[0] == 'E')  // (e.what == "Ent")
        {
            if (e.what()[3] == 'h')       // (e.what == "Enthalpy")
                return MAKELRESULT(H_OUT_OF_RANGE, 2);
            else if (e.what()[3] == 'r') // (e.what == 'Entropy')
                return MAKELRESULT(S_OUT_OF_RANGE, 2);
            else
                return MAKELRESULT(UNKNOWN, 2);
        }
        else
            return MAKELRESULT(UNKNOWN, 2);
    } 
    catch (const std::logic_error&) {
        return MAKELRESULT(NO_SOLUTION_FOUND,1);
    }
    // normal return
    return 0;
}

FUNCTIONINFO    if97_sph = 
{
    "if97_sph",                          // name by which Mathcad will recognize the function
    "p,h",                               // if97_SPH will be called as if97_sph(p,s)
    // description of if97_sph(p)
    "Obtains the entropy [J/kg-K] as a function of p [Pa] and enthalpy, h [kJ/kg].",
    (LPCFUNCTION)if97_SPH,               // pointer to executable code
    COMPLEX_SCALAR,                      // the return type is a complex scalar
    2,                                   // there are two input parameters
    { COMPLEX_SCALAR, COMPLEX_SCALAR }   //    that are both complex scalars
};