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

This will spit out the values for the computer-program verification, they should agree with the values from http://www.iapws.org/relguide/IF97-Rev.pdf .  In Region 3, the backwards equations are used, which results in some loss of precision, but it is usually less than 0.001%

Usage
-----

See ``IF97.cpp``.  

The primary functions needed are ``rhomass_TP(T,p)``, ``hmass_Tp(T,p)``, etc. where in all cases, the units are base-SI units (Pa, K, J/kg, etc.)

There are also ``Tsat97(p)`` and ``psat97(T)`` functions to get values from the saturation line.

License
-------

MIT-style license (see LICENSE)

Basically, you can do anything you like with the code.  The MIT license is a very permissive license, allowing you to modify, distribute, sell, etc. the code.  It is *not* a copy-left license, you can use this in commercial code.  

You are strongly requested, but not required, to cite both this repository and that of coolprop: www.coolprop.org