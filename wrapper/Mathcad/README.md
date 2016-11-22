Wrapper of IF97 for MathCAD 15
==================================

Has been developed and tested on Mathcad 15.0 (any maintenance release).  May work on earlier versions, but it has not been tested there.

To Use
======

* Compile in VS2010 or later using the solution and project files

* Copy the if97.dll file to C:\\Program Files (x86)\\Mathcad\\Mathcad 15\\userefi or equivalent for your version (this will be done automatically by the project)  
  
* Copy the IF97_EN.xml to C:\\Program Files (x86)\\Mathcad\\Mathcad 15\\doc\\funcdoc.  Functions and descriptions will then be available in the Mathcad 15 interface under Insert|Function or the Functions button on the toolbar.

* View if97_verification.pdf for examples of using the functions.

To Build
========

* You will need to have Visual Studio 2008 installed (Express version is fine).  Alternatively newer versions of Microsoft Visual Studio C++ should be fine, you'll just have to update the solution and project files

* Build the if97 DLL in Visual Studio.  The project will auotmatically copy the DLL to the appropriate Mathcad installation directory.  You may have to allow user write access to both:

	``C:\\Program Files (x86)\\Mathcad\\Mathcad 15\\userefi``
	
    and
		
	``C:\\Program Files (x86)\\Mathcad\\Mathcad 15\\doc\\funcdoc``

* Follow the above instructions for use.
