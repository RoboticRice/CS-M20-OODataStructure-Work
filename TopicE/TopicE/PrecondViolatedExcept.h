/** Listing 7-5.
    @file PrecondViolatedExcept.h */

#ifndef _PRECOND_VIOLATED_EXCEPT
#define _PRECOND_VIOLATED_EXCEPT

#include <stdexcept>
#include <string>

using namespace std;

class PrecondViolatedExcept : public logic_error
{
public:
   PrecondViolatedExcept(const string& message = "");
}; // end PrecondViolatedExcep 

   /** Listing 7-6.
   @file PrecondViolatedExcept.cpp */
//#include "PrecondViolatedExcept.h"  

PrecondViolatedExcept::PrecondViolatedExcept(const string& message) : logic_error("Precondition Violated Exception: " + message)
{
}  // end constructor

   // End of implementation file.
#endif
