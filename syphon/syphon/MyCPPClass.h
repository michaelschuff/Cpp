//
//  MyCPPClass.h
//  syphon
//
//  Created by Michael Schuff on 10/19/20.
//

#ifndef __MYCPP_CLASS_H__
#define __MYCPP_CLASS_H__

class MyClassImpl;

class MyCPPClass
{
    enum { cANSWER_TO_LIFE_THE_UNIVERSE_AND_EVERYTHING = 42 };
public:
    MyCPPClass ( void );
    ~MyCPPClass( void );

    void init( void );
    void doSomethingWithMyClass( void );

private:
    MyClassImpl * _impl;
    int           _myValue;
};

#endif /* MyCPPClass_h */
