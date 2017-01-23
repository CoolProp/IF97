=============
CoolProp IF97
=============

(c) Ian Bell and the CoolProp team

This repository implements the IF97 formulation for the properties of pure water substance.

Why?
----

Almost all of the other implementations of IF97 are not free and closed-source.  This implementation is:

* Entirely free and open-source (see license below)
* Written in optimized standard C++ code so it will compile anywhere
* Fast
* Easy-to-use (just a single header)

Try it
------

Build the cmake project doing something like 
    
```
mkdir build
cd build
cmake ..
cmake --build .
```

This will spit out the values for the computer-program verification, they should agree with the values from http://www.iapws.org/relguide/IF97-Rev.pdf and other IAPWS documents as noted in the output.  In Region 3, the backwards equations are used, which results in some loss of precision, but it is usually less than 0.001%

Usage
-----

See ``IF97.cpp``.  

The primary functions needed are ``rhomass_Tp(T,p)``, ``hmass_Tp(T,p)``, etc. where in all cases, the units are base-SI units (Pa, K, J/kg, etc.)  
  
Liquid and vapor values along the saturation curve can be obtained using ``rholiq_p(p)``, ``rhovap_p(p)``, ``sliq_p(p)``, ``svap_p(p)``, etc.; all as a function of pressure.

There are also ``Tsat97(p)`` and ``psat97(T)`` functions to get values from the saturation line.

Backward functions have been implemented to return temperature as a function of pressure and either enthalpy or entropy; ``T_phmass(p,h)`` and ``T_psmass(p,s)``.  Backward functions have also been implemented to return temperature or pressure as a function of enthalpy and entropy, ``p_hsmass(h,s)`` and ``T_hsmass(h,s)``, to facilitate thermodynamic cycle calculations.

Transport property functions have been implemented for temperature/pressure state points as well as along the saturation curve.  These include
- Viscosity functions: ``visc_Tp(T,p)``, ``viscliq_p(p)``, and ``viscvap_p(p)``
- Thermal Conductivity functions: ``tcond_Tp(T,p)``, ``tcondliq_p(p)``, and ``tcondvap_p(p)``
- Surface Tension: ``sigma97(t)``
- Prandtl Number: ``prandtl_Tp(T,p)``, ``prandtlliq_p(p)``, and ``prandtlvap_p(p)``  

As of IF97 v2.0.0, a utility function ``get_if97_version()`` will return the official version string for this IF97 implementation.

License
-------

MIT-style license (see LICENSE)

Basically, you can do anything you like with the code.  The MIT license is a very permissive license, allowing you to modify, distribute, sell, etc. the code.  It is *not* a copy-left license, you can use this in commercial code.  

You are strongly requested, but not required, to cite both this repository and that of CoolProp: www.coolprop.org

Wrappers
--------

Wrappers directory started for 3rd Party Apps, including:
- Mathcad 15 (Jeff Henning main contributor)
