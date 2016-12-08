//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2017 __Pearson Education__. All rights reserved.

/** Listing 7-6.
    @file PrecondViolatedExcept.cpp */
#include "PrecondViolatedExcept.h"  

PrecondViolatedExcept::PrecondViolatedExcept(const string& message): logic_error("Precondition Violated Exception: " + message)
{
}  // end constructor

// End of implementation file.

