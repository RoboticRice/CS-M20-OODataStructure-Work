//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2017 __Pearson Education__. All rights reserved.

/** Listing 7-5.
    @file PrecondViolatedExcep.h */

#ifndef _PRECOND_VIOLATED_EXCEPT
#define _PRECOND_VIOLATED_EXCEPT

#include <stdexcept>
#include <string>

using namespace std;

class PrecondViolatedExcept : public logic_error
{
public:
   PrecondViolatedExcept(const string& message = "");
}; // end PrecondViolatedExcept 
#endif
