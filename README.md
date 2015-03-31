=============
CoolProp IF97
=============

(c) Ian Bell and the CoolProp team

This repository implements the IF97 formulation for the properties of pure water substance.

Try it
------

Build the cmake project doing something like 
    
```
mkdir build
cd build
cmake ..
cmake --build .
```

This will spit out the values for the computer-program verification, they should agree with the values from http://www.iapws.org/relguide/IF97-Rev.pdf .  In Region 3, the backwards equations are used, which results in some loss of precision, but it is usually less than 0.001%

Usage
-----

See ``IF97.cpp``.  

The primary functions needed are ``rhomass_TP(T,p)``, ``hmass_Tp(T,p)``, etc. where in all cases, the units are base-SI units (Pa, K, J/kg, etc.)

There are also ``Tsat97(p)`` and ``psat97(T)`` functions to get values from the saturation line
