// CoolProp IF97.cpp : Defines the exported functions for the DLL application.
//

#include <string>
#include "mcadincl.h"

//  By default, IF97.h uses the supplemental curve fit equations in Region 3 which are less accurate, but faster than iterating
//  to find the density in terms of T & p.  Defining REGION3_ITERATE will use these equations to find density and then use it 
//  as an initial guess for a more accurate reverse calculation using a Newton-Raphson technique.  This technique takes about 
//  2.6X longer than the supplemental equations alone.
#define REGION3_ITERATE

// #define IAPWS_UNITS          // Set to use IAPWS Units of [MPa] and [kJ] (instead of [Pa] and [J] )
#include "../../IF97.h"

// Mathcad Error Codes
enum EC  {MUST_BE_REAL = 1, INSUFFICIENT_MEMORY, INTERRUPTED, T_OUT_OF_RANGE, P_OUT_OF_RANGE, SATURATED, NO_SOLUTION_FOUND, 
          D_OUT_OF_RANGE, H_OUT_OF_RANGE, S_OUT_OF_RANGE, REGION_NOT_FOUND, NUMBER_OF_ERRORS};

    // Table of Error Messages
    // These message strings MUST be in the order of the Error Code enumeration above, with the last being a dummy value for error count
    char * myErrorMessageTable[NUMBER_OF_ERRORS] =  
    {   
        "Argument must be real",
        "Insufficient Memory",
        "Interrupted",
        "Temperature out of Range",
        "Pressure out of Range",
        "Saturated Conditions",
        "No Solution Found",
        "Density out of Range",
        "Enthalpy out of Range",
        "Entropy out of Range",
        "Region not found",
        "Error Count - Not Used"
    };

    // Include the Function call stubs here:
    //
    // *************************************************************
    // Basic function stubs
    // *************************************************************
    #include ".\includes\tsatp.h"
    #include ".\includes\ttrip.h"
    #include ".\includes\tcrit.h"
    #include ".\includes\psatt.h"
    #include ".\includes\ptrip.h"
    #include ".\includes\pcrit.h"
    #include ".\includes\rhotp.h"
    #include ".\includes\vtp.h"
    #include ".\includes\htp.h"
    #include ".\includes\utp.h"
    #include ".\includes\stp.h"
    #include ".\includes\cptp.h"
    #include ".\includes\cvtp.h"
    #include ".\includes\wtp.h"
    // *************************************************************
    // Saturation function stubs
    // *************************************************************
    #include ".\includes\rhof.h"
    #include ".\includes\rhog.h"
    #include ".\includes\vf.h"
    #include ".\includes\vg.h"
    #include ".\includes\hf.h"
    #include ".\includes\hg.h"
    #include ".\includes\uf.h"
    #include ".\includes\ug.h"
    #include ".\includes\sf.h"
    #include ".\includes\sg.h"
    #include ".\includes\cpf.h"
    #include ".\includes\cpg.h"
    #include ".\includes\cvf.h"
    #include ".\includes\cvg.h"
    #include ".\includes\wf.h"
    #include ".\includes\wg.h"
    // *************************************************************
    // Transport Property Stubs
    // *************************************************************
    #include ".\includes\sigma.h"
    #include ".\includes\mutp.h"
    #include ".\includes\mutrho.h"  // this function provided for validation work only
    #include ".\includes\muf.h"
    #include ".\includes\mug.h"
    #include ".\includes\ktp.h"
    #include ".\includes\kf.h"
    #include ".\includes\kg.h"
    #include ".\includes\prtp.h"
    #include ".\includes\prf.h"
    #include ".\includes\prg.h"
    // *************************************************************
    // Test Functions
    // *************************************************************
    #include ".\includes\p23.h"
    #include ".\includes\t23.h"
    #include ".\includes\regionph.h"
    #include ".\includes\regionps.h"
    #include ".\includes\h3ab.h"
    #include ".\includes\h2ab.h"
    #include ".\includes\h2bc.h"
    #include ".\includes\h13.h"
    #include ".\includes\hsats.h"
    #include ".\includes\hmaxs.h"
    #include ".\includes\hmins.h"
    #include ".\includes\drhodp.h"
    // *************************************************************
    // Reverse Functions
    // *************************************************************
    #include ".\includes\tph.h"
    #include ".\includes\tps.h"
    #include ".\includes\phs.h"
    #include ".\includes\ths.h"

    // DLL entry point code.  the _CRT_INIT function is needed
    // if you are using Microsoft's 32 bit compiler
 
    extern "C" BOOL WINAPI _CRT_INIT(HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpReserved);

    extern "C" BOOL WINAPI  DllEntryPoint (HINSTANCE hDLL, DWORD dwReason, LPVOID lpReserved)
    {
        switch (dwReason)
        {
                case DLL_PROCESS_ATTACH:
                    {
                    //
                    // DLL is attaching to the address space of 
                    // the current process.
                    //
                    if (!_CRT_INIT(hDLL, dwReason, lpReserved)) 
                        return FALSE;
                
                    // register the error message table
                    // Note, that if your function never returns
                    // an error -- you do not need to 
                    // register an error message table
                    if ( !CreateUserErrorMessageTable( hDLL, NUMBER_OF_ERRORS, myErrorMessageTable ) )
                        break;


                    // and if the errors register OK
                    // go ahead and
                    // register user function
                    // *************************************************************
                    // Basic functions
                    // *************************************************************
                    CreateUserFunction( hDLL, &if97_tsatp );
                    CreateUserFunction( hDLL, &if97_tcrit );
                    CreateUserFunction( hDLL, &if97_ttrip );
                    CreateUserFunction( hDLL, &if97_psatt );
                    CreateUserFunction( hDLL, &if97_pcrit );
                    CreateUserFunction( hDLL, &if97_ptrip );
                    CreateUserFunction( hDLL, &if97_rhotp );
                    CreateUserFunction( hDLL, &if97_vtp );
                    CreateUserFunction( hDLL, &if97_htp );
                    CreateUserFunction( hDLL, &if97_stp );
                    CreateUserFunction( hDLL, &if97_utp );
                    CreateUserFunction( hDLL, &if97_cptp );
                    CreateUserFunction( hDLL, &if97_cvtp );
                    CreateUserFunction( hDLL, &if97_wtp );
                    // *************************************************************
                    // Saturation functions
                    // *************************************************************
                    CreateUserFunction( hDLL, &if97_rhof );
                    CreateUserFunction( hDLL, &if97_rhog );
                    CreateUserFunction( hDLL, &if97_vf );
                    CreateUserFunction( hDLL, &if97_vg );
                    CreateUserFunction( hDLL, &if97_hf );
                    CreateUserFunction( hDLL, &if97_hg );
                    CreateUserFunction( hDLL, &if97_sf );
                    CreateUserFunction( hDLL, &if97_sg );
                    CreateUserFunction( hDLL, &if97_uf );
                    CreateUserFunction( hDLL, &if97_ug );
                    CreateUserFunction( hDLL, &if97_cpf );
                    CreateUserFunction( hDLL, &if97_cpg );
                    CreateUserFunction( hDLL, &if97_cvf );
                    CreateUserFunction( hDLL, &if97_cvg );
                    CreateUserFunction( hDLL, &if97_wf );
                    CreateUserFunction( hDLL, &if97_wg );
                    // *************************************************************
                    // Transport Property functions
                    // *************************************************************
                    CreateUserFunction( hDLL, &if97_mutp );
                    CreateUserFunction( hDLL, &if97_mutrho );  // for checking only
                    CreateUserFunction( hDLL, &if97_muf );
                    CreateUserFunction( hDLL, &if97_mug );
                    CreateUserFunction( hDLL, &if97_ktp );
                    CreateUserFunction( hDLL, &if97_kf );
                    CreateUserFunction( hDLL, &if97_kg );
                    CreateUserFunction( hDLL, &if97_prtp );
                    CreateUserFunction( hDLL, &if97_prf );
                    CreateUserFunction( hDLL, &if97_prg );
                    // *************************************************************
                    // Additional Property functions
                    // *************************************************************
                    CreateUserFunction( hDLL, &if97_sigma );
                    // *************************************************************
                    // Test functions
                    // *************************************************************
                    CreateUserFunction( hDLL, &if97_p23 );
                    CreateUserFunction( hDLL, &if97_t23 );
                    CreateUserFunction( hDLL, &if97_h2bc );
                    CreateUserFunction( hDLL, &if97_h3ab );
                    CreateUserFunction( hDLL, &if97_h2ab );
                    CreateUserFunction( hDLL, &if97_h13s );
                    CreateUserFunction( hDLL, &if97_hsats );
                    CreateUserFunction( hDLL, &if97_hmaxs );
                    CreateUserFunction( hDLL, &if97_hmins );
                    CreateUserFunction( hDLL, &if97_regionph );
                    CreateUserFunction( hDLL, &if97_regionps );
                    CreateUserFunction( hDLL, &if97_drhodp );
                    // *************************************************************
                    // Reverse functions
                    // *************************************************************
                    CreateUserFunction( hDLL, &if97_tph );
                    CreateUserFunction( hDLL, &if97_tps );
                    CreateUserFunction( hDLL, &if97_phs );
                    CreateUserFunction( hDLL, &if97_ths );
                    break;
                    }

                case DLL_THREAD_ATTACH:
                case DLL_THREAD_DETACH:
                case DLL_PROCESS_DETACH:

                    if (!_CRT_INIT(hDLL, dwReason, lpReserved))
                    {
                        Sleep(1000);   // Attempt to keep CRT_INIT from detaching before all threads are closed
                        return FALSE;
                    }
                    break;                   
        }
        return TRUE;
    }

  