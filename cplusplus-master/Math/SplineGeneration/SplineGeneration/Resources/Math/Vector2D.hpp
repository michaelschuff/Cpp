//
//  Vector2D.hpp
//  SplineGeneration
//
//  Created by Michael Schuff on 3/26/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#ifndef Vector2D_hpp
#define Vector2D_hpp

#include <stdio.h>
#include "Point2D.hpp"
#include "MathFunctions.hpp"

using namespace std;

class Vector2D : public Point2D {
public:
    double theta, magnitude;
    
    Vector2D(Point2D);
    Vector2D(float, float);
    Vector2D(double, double);
    
    Vector2D rotated(double angle);
    Point2D toPoint2D();
    void rotate(double angle);
    
    Vector2D operator-();
    void operator+=(Vector2D&);
    void operator-=(Vector2D&);
    void operator*=(double&);
    void operator/=(double&);
    
private:
    void updateCartesian();
    void updatePolar();
};

#endif /* Vector2D_hpp */
