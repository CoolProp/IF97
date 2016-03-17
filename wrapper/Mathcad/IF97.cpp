// CoolProp IF97.cpp : Defines the exported functions for the DLL application.
//

#include <string>
#include "mcadincl.h"

//  By default, IF97.h uses the supplemental curve fit equations in Region 3 which are less accurate, but faster than iterating
//  to find the density in terms of T & p.  Defining REGION3_ITERATE will use these equations to find density and then use it 
//  as an initial guess for a more accurate reverse calculation using a Newton-Raphson technique.  This technique takes about 
//  2.6X longer than the supplemental equations alone.
#define REGION3_ITERATE

#define PSTAR 1e6          // Used to put [MPa] values in [Pa]
#include "../../IF97.h"

// Mathcad Error Codes
enum EC  {MUST_BE_REAL = 1, INSUFFICIENT_MEMORY, INTERRUPTED, T_OUT_OF_RANGE, P_OUT_OF_RANGE, SATURATED, NO_SOLUTION_FOUND, D_OUT_OF_RANGE, NUMBER_OF_ERRORS};

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
		"Error Count - Not Used"
    };

	const double Ttrip   = 273.16;				// Triple point in [K]
	const double Ptrip   = 611.657e-6*PSTAR;	// Triple point in [MPa] 
	const double Tcrit   = 647.096;				// Critical point in [K]
	const double Pcrit   = 22.064*PSTAR;		// Critical point in [MPa]
	const double rhocrit = 322.0;				// Critical point in [kg/m³]
	const double Tmax    = 1073.15;				// Max Temperature [K]
	const double Pmax    = 100.0*PSTAR;			// Max Pressure [MPa] 
	const double Text    = 2273.15;				// Extended (Region 5) Temperature Limit (Region 5) [K]
	const double Pext    = 50.0*PSTAR;			// Extended (Region 5) Pressure Limit (Region 5) [MPa]
	const double P23min  = 16.5292*PSTAR;       // Min Pressure on Region23 boundary curve; Max is Pmax
	const double T23min  = 623.15;              // Min Temperature on Region23 boundary curve
	const double T23max  = 863.15;              // Max Temperature on Region23 boundary curve

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
	// Saturation function stubs (to be implemented soon)
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
	/*
	// *************************************************************
	// Transport Property Stubs (to be implemented soon)
	// *************************************************************
	#include "sigma.h"
	#include "mutp.h"
	#include "mutrho.h"  // this function provided for validatation work only
	#include "muf.h"
	#include "mug.h"
	*/
	// *************************************************************
	// Test Functions (to be implemented soon)
	// *************************************************************
	#include ".\includes\p23.h"
	#include ".\includes\t23.h"

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
					/*
					// *************************************************************
					// Transport Property functions
					// *************************************************************
                    CreateUserFunction( hDLL, &if97_mutp );
                    CreateUserFunction( hDLL, &if97_mutrho );  // for checking only
                    CreateUserFunction( hDLL, &if97_muf );
                    CreateUserFunction( hDLL, &if97_mug );
					// *************************************************************
					// Additional Property functions
					// *************************************************************
                    CreateUserFunction( hDLL, &if97_sigma );
					*/
					// *************************************************************
					// Test functions
					// *************************************************************
					CreateUserFunction( hDLL, &if97_p23 );
					CreateUserFunction( hDLL, &if97_t23 );
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

  
#undef  PSTAR
#undef  MUST_BE_REAL
#undef  INSUFFICIENT_MEMORY
#undef  INTERRUPTED
#undef  T_OUT_OF_RANGE
#undef  P_OUT_OF_RANGE
#undef  SATURATED
#undef  NO_SOLUTION_FOUND
#undef  D_OUT_OF_RANGE
#undef  NUMBER_OF_ERRORS
