/**
 * This file provides a define "AGEXPORT" to be used for exporting functions and classes
 * out of DLLs on Windows.
 * For this to function you'll just insert it:
 * 1) before a function declaration:
 *    AGEXPORT void myFunction();
 * 2) or inbetween a class-definition:
 *    class AGEXPORT MyClass {
 *    .....
 *    };
 * No additional configuration should be needed.
 * including within swig is taken care of. 
 *  
 * */

#ifndef AG_BASE_H
#define AG_BASE_H

#ifdef WIN32
#ifdef AGIMPORT
#define AGEXPORT __declspec(dllimport)
#else
#undef AGEXPORT
#define AGEXPORT __declspec(dllexport)
#endif // AGIMPORT
#else

#undef AGEXPORT
#define AGEXPORT

#endif // WIN32

#ifdef SWIG
#undef AGEXPORT
#define AGEXPORT
#endif

#ifdef NOTDEF

#include <iostream>

class AGRubyObject;


#endif
#endif