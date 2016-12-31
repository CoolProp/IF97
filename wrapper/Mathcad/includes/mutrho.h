// if97_mutrho stub - Interfaces CoolProp IF97 function to Mathcad
// 
// NOTE: This stub is for verification purposes only.  It will not be advertised
//       in the Mathcad function documentation for user reference.

// this code executes the user function if97_mutrho(rho), which is a wrapper for
// the CoolProp-IF97 function, visc_TRho(T,rho).
LRESULT  if97_MUTRHO(
    LPCOMPLEXSCALAR c,  // pointer to the result
    LPCCOMPLEXSCALAR a,
    LPCCOMPLEXSCALAR b) // pointer to the parameter received from Mathcad
{  
    // first check to make sure "a" and "b" have no imaginary component
    if ( a->imag != 0.0 )
        return MAKELRESULT(MUST_BE_REAL,1);
    if ( b->imag != 0.0 )
        return MAKELRESULT(MUST_BE_REAL,2);

    //otherwise, all is well, evaluate function
    try {
        c->real = IF97::visc_TRho(a->real,b->real);
    }
    catch (const std::out_of_range& e) { 
        if (e.what()[0] == 'T') 
            return MAKELRESULT(T_OUT_OF_RANGE,1);
        else // (e.what == "P")
            return MAKELRESULT(P_OUT_OF_RANGE,2);
    }
    catch (const std::logic_error&) {
        return MAKELRESULT(NO_SOLUTION_FOUND,1);
    }
    // normal return
    return 0;
}

FUNCTIONINFO    if97_mutrho = 
{
    "if97_mutrho",                     // name by which Mathcad will recognize the function
    "T,rho",                           // if97_mutrho will be called as if97_mutrho(T,p)
    // description of if97_mutrho(p)
    "Obtains the mass viscosity [Pa-s] as a function of T [K] and rho [kg/m�].",
    (LPCFUNCTION)if97_MUTRHO,          // pointer to executable code
    COMPLEX_SCALAR,                    // the return type is a complex scalar
    2,                                 // there are two input parameters
    { COMPLEX_SCALAR, COMPLEX_SCALAR } //    that are both complex scalars
};