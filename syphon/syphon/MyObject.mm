//
//  MyObject.m
//  syphon
//
//  Created by Michael Schuff on 10/19/20.
//

#import "MyObject.h"

@implementation MyObject

// C "trampoline" function to invoke Objective-C method
int MyObjectDoSomethingWith (void *self, void *aParameter)
{
    // Call the Objective-C method using Objective-C syntax
    return [(id) self doSomethingWith:aParameter];
}

- (int) doSomethingWith:(void *) aParameter
{
    // The Objective-C function you wanted to call from C++.
    // do work here..
    return 21 ; // half of 42
}
@end
