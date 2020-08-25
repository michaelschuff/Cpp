//
//  Point2D.hpp
//  SplineGeneration
//
//  Created by Michael Schuff on 3/26/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#ifndef Point2D_hpp
#define Point2D_hpp

#include <stdio.h>
#include <cmath>

using namespace std;

class Point2D {
public:
    double x, y;
    
    Point2D();
    Point2D(double, double);
    
    Point2D operator-();
    void operator+=(Point2D&);
    void operator-=(Point2D&);
};
#endif /* Point2D_hpp */
