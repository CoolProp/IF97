// if97_ktp stub - Interfaces CoolProp IF97 function to Mathcad
//

// this code executes the user function if97_ktp(P), which is a wrapper for
// the CoolProp-IF97 function, tcond_Tp(T,P).
LRESULT  if97_KTPRHO(
    LPCOMPLEXSCALAR k,  // pointer to the result
    LPCCOMPLEXSCALAR T,
    LPCCOMPLEXSCALAR P,
    LPCCOMPLEXSCALAR rho) // pointer to the parameter received from Mathcad
{  
    // first check to make sure "a" and "b" have no imaginary component
    if ( T->imag != 0.0 )
        return MAKELRESULT(MUST_BE_REAL,1);
    if ( P->imag != 0.0 )
        return MAKELRESULT(MUST_BE_REAL,2);
    if ( rho->imag != 0.0)
        return MAKELRESULT(MUST_BE_REAL,3);

    //otherwise, all is well, evaluate function
    try {
        k->real = IF97::tcond_TpRho(T->real,P->real,rho->real);
    }
    catch (const std::out_of_range& e) { 
        if (e.what()[0] == 'T') 
            return MAKELRESULT(T_OUT_OF_RANGE,1);
        else if (e.what()[0] == 'P')
            return MAKELRESULT(P_OUT_OF_RANGE,2);
        else if (e.what()[0] == 'C')
            return MAKELRESULT(SATURATED,1);
        else
            return MAKELRESULT(UNKNOWN,1);
    }
    catch (const std::logic_error&) {
        return MAKELRESULT(NO_SOLUTION_FOUND,1);
    }
    // normal return
    return 0;
}

FUNCTIONINFO    if97_ktprho = 
{
    "if97_ktprho",                             // Name by which Mathcad will recognize the function
    "T,p,rho",                                 // if97_ktprho will be called as if97_ktp(T,p,rho)
    // description of if97_ktp(p)
    "Obtains the Thermal Conductivity [W/m-K] as a function of T [K], p [Pa], and rho [kg/m³].",
    (LPCFUNCTION)if97_KTP,                  // Pointer to executable code
    COMPLEX_SCALAR,                         // The return type is a complex scalar
    3,                                      // There are three input parameters
    { COMPLEX_SCALAR,
      COMPLEX_SCALAR,
      COMPLEX_SCALAR }                      //    that are all complex scalars.
};
