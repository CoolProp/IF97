*************
CoolProp IF97
*************

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

This will spit out the values for the computer-program verification, they should agree with the values from http://www.iapws.org/relguide/IF97-Rev.pdf

Caveats
-------

For now, only the forward (X = f(T,p)) properties have been implemented.  The backwards formulations are on the way.