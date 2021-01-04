//
//  MyObject-C-Interface.h
//  syphon
//
//  Created by Michael Schuff on 10/19/20.
//

#ifndef __MYOBJECT_C_INTERFACE_H__
#define __MYOBJECT_C_INTERFACE_H__

// This is the C "trampoline" function that will be used
// to invoke a specific Objective-C method FROM C++
int MyObjectDoSomethingWith (void *myObjectInstance, void *parameter);
#endif
