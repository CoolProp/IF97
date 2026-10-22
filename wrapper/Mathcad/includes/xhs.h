// if97_xhs stub - Interfaces CoolProp IF97 function to Mathcad
//

// this code executes the user function if97_xhs(h,s), which is a wrapper for
// the CoolProp-IF97 function, Q_hsmass(h,s).
LRESULT  if97_XHS(
    LPCOMPLEXSCALAR x,  // pointer to the result
    LPCCOMPLEXSCALAR h,
    LPCCOMPLEXSCALAR s) // pointer to the parameter received from Mathcad
{  
    // first check to make sure "h" and "s" have no imaginary component
    if ( h->imag != 0.0 )
        return MAKELRESULT(MUST_BE_REAL,1);
    if ( s->imag != 0.0 )
        return MAKELRESULT(MUST_BE_REAL,2);

    //otherwise, all is well, evaluate function
    try {
        x->real = IF97::Q_hsmass(h->real,s->real);
    }
    catch (const std::out_of_range& e) { 
        if ((e.what()[0] == 'E') && (e.what()[3] == 'h'))
            return MAKELRESULT(H_OUT_OF_RANGE,1);
        else if ((e.what()[0] == 'E') && (e.what()[3] == 'r'))
            return MAKELRESULT(S_OUT_OF_RANGE,2);
        else if (e.what()[0] == 'U')                            // e.what == "Unable to determine region"
            return MAKELRESULT(REGION_NOT_FOUND, 2);
        else
            return MAKELRESULT(UNKNOWN,0);
    }
    catch (const std::logic_error&) {
        return MAKELRESULT(NO_SOLUTION_FOUND,1);
    }
    // normal return
    return 0;
}

FUNCTIONINFO    if97_xhs = 
{
    "if97_xhs",                         // name by which Mathcad will recognize the function
    "h,s",                              // if97_xhs will be called as if97_xhs(h,s)
    // description of if97_xhs(h,s)
    "Obtains the steam quality, x, as a function of enthalpy, h [J/kg], and mass entropy, s [J/kg-K].",
    (LPCFUNCTION)if97_XHS,              // pointer to executable code
    COMPLEX_SCALAR,                     // the return type is a complex scalar
    2,                                  // there are two input parameters
    { COMPLEX_SCALAR, COMPLEX_SCALAR }  //    that are both complex scalars
};