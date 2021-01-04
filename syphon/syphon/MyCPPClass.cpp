//
//  MyCPPClass.cpp
//  syphon
//
//  Created by Michael Schuff on 10/19/20.
//
#include "MyCPPClass.h"
#include "MyObject-C-Interface.h"

int MyCPPClass::someMethod (void *objectiveCObject, void *aParameter)
{
    // To invoke an Objective-C method from C++, use
    // the C trampoline function
    return MyObjectDoSomethingWith (objectiveCObject, aParameter);
}
