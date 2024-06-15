Wrapper of IF97 for PTC Mathcad Prime
=====================================

This wrapper will provide Custom Functions (user defined) in Mathcad Prime that provide the thermodynamic and transport properties for water/steam at specified state points based on the [IAPWS Industrial Formulation 1997 for the Properties of Water and Steam (IF97)](http://www.iapws.org/relguide/IF97-Rev.html).  While these properties can also be accessed through the [CoolProp add-in](https://github.com/CoolProp/CoolProp/tree/master/wrappers/MathCAD), this wrapper provides **_only_** these steam/water properties without the overhead of CoolProp.

> This wrapper been developed and tested on Mathcad Prime 3.0 through 10.0, although only 7.0 through 10.0 are supported at this time. It **_may_** work on earlier versions of **_Legacy Mathcad (15.0+)_**, but it has not been tested there since Legacy Mathcad was discontinued.

------

To Use (Overview)
=================

* Build the Add-in DLL in VS2015 or later using the build instructions below.

* Install the Add-in files by copying them to the appropriate Mathcad Prime (or Legacy Mathcad) Installation directories as indicated below.  

* View ``if97_verification.pdf`` or ``if97_verification_IAPWS.pdf`` for examples of using the functions.

------

To Build
========

Follow the build procedures below to ceate the IF97 add-in DLL files for either Mathcad 15 or Mathcad Prime.

Pre-Requisites
--------------

* You will need to have at least Visual Studio 2015 or later installed (Express or Community versions work fine).  Builds have be tested on Visual Studio 2010 through 2022.
* You will need CMake version 2.8.12 or later from https://cmake.org/download/
* You will need to install Git-SCM for Windows.  You can install this from https://git-for-windows.github.io

Download the IF97 Repository
----------------------------

* Open a Git window at the drive location where you want to create your local IF97 repository

* Clone the CoolProp/IF97 repository to a local repository (If you haven't already cloned it recursively with CoolProp).::

    git clone https://github.com/CoolProp/IF97

* Change directory (cd) to the IF97 directory you just created.::

    cd IF97

Make the Build for Mathcad Prime (any version above 3.0)
--------------------------------------------------------

* Go to the top level IF97 directory and make a build directory (something like \build or \buildPrime):

    mkdir buildPrime
    cd buildPrime

* Build the makefile using CMake (Note: Mathcad Prime is 64-bit):

    cmake .. -DIF97_PRIME_MODULE=ON 
             -DIF97_PRIME_ROOT="C:/Program Files/PTC/Mathcad 7.0.0.0"  
             -G "Visual Studio 17 2022" -A x64 
             -DCMAKE_VERBOSE_MAKEFILE=ON 
	     
	> Insert your version of Visual Studio for the -G option.  
	> Note that Mathcad Prime is 64-bit and requires the `-A x64` switch on this command.  
    > Prior to VS 2017, use something like: `-G "Visual Studio 14 2015 Win64`

Make the Build for Legacy Mathcad 15 (Discontinued by PTC)
----------------------------------------------------------

* Go to the top level IF97 directory and make a build directory (something like \build15):

    mkdir build15 
    cd build15

* Build the makefile using CMake (Note: Mathcad 15 is 32-bit)::

    cmake .. -DIF97_MATHCAD15_MODULE=ON 
             -DIF97_MATHCAD15_ROOT="C:/Program Files (x86)/Mathcad/Mathcad 15"  
             -G "Visual Studio 17 2022" -A Win32 
             -DCMAKE_VERBOSE_MAKEFILE=ON 
	     
	> Insert your version of Visual Studio for the -G option.  
    > Legacy Mathcad was 32-bit and requires a 32-bit add-in DLL.  
    > Prior to VS2017, use something like `-G "Visual Studio 14 2015` as 32-bit was the default.

Build the Project
-----------------

* Open the resulting IF97.sln file in Visual Studio and build the IF97 project, making sure that ``Release`` configuration is selected in the VS menu toolbar and that the platform is set to ``x64`` for use with Mathcad Prime (64-bit).  Alternatively, you can build the dynamic library (DLL) from the command line using cmake::

    cmake --build . --config Release
  
------
  
Installing
==========

* Build the IF97 DLL as indicated above and then copy the wrapper files to the appropriate Mathcad 15 or Prime directories as follows.

Mathcad Prime (v3.0 or higher)
----------
* Copy the ``Release\IF97.dll`` file to ``C:\Program Files\PTC\Mathcad Prime 7.0.0.0\Custom Functions`` or equivalent for your version of Mathcad Prime.  

Optional:

* For legacty **_Insert Custom Function_** capability in Mathcad Prime, download and install the [CustFunc add-in DLL](https://github.com/henningjp/CustFunc), which will provide a pop-up panel for inserting the custom functions into your worksheet at the cursor location.
* For CustFunc to work, copy the ``IF97_EN.xml`` to ``C:\Program Files\PTC\Mathcad Prime 10.0.0.0\Custom Functions\docs``; switch out `10.0.0.0` for your working version of Mathcad Prime.  Functions and descriptions will then be available in the Mathcad Mathcad interface via **_hot-key_** `<Shift><F2>`.  See the README for the [CustFunc add-in DLL](https://github.com/henningjp/CustFunc) for further installation and usage instructions.
  
Legacy Mathcad 15 (Discontinued)
----------
* Copy the ``Release\IF97.dll`` file to ``C:\Program Files (x86)\Mathcad\Mathcad 15\userefi`` or equivalent for your version of Mathcad.    
* **Legacy Mathcad Only:** Copy the ``IF97_EN.xml`` to ``C:\Program Files (x86)\Mathcad\Mathcad 15\doc\funcdoc``.  Functions and descriptions will then be available in the Mathcad 15 interface under Insert|Function or the Functions button on the toolbar.  This functionality is **_still_** not available in Mathcad Prime as of version 8.0.

------
  
Compiler Flags
==============
The Mathcad wrapper code uses the ``REGION3_ITERATE`` flag to provide more accurate (but slightly slower) calculation of density in Region 3 (mostly super-critical), but does **_not_** use the ``IAPWS_UNITS`` flag by default, leaving all input/output values in SI units.

The `IAPWS_UNITS` flag can be set (uncommented) in the top of the IF97.cpp file to input and output IAPWS units (Pressures in MPa and energy in kJ) for easy comparison with IAPWS release documents.