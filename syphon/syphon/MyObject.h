//
//  MyObject.h
//  syphon
//
//  Created by Michael Schuff on 10/19/20.
//

#import "MyObject-C-Interface.h"

// An Objective-C class that needs to be accessed from C++
@interface MyObject : NSObject
{
    int someVar;
}

// The Objective-C member function you want to call from C++
- (int) doSomethingWith:(void *) aParameter;
@end
