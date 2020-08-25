//
//  Vector2D.hpp
//  SplineGeneration2.0
//
//  Created by Michael Schuff on 4/9/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#ifndef Vector2D_hpp
#define Vector2D_hpp

#include <stdio.h>

class Vector2D {
public:
    float x, y;
    double theta, magnitude;
    
    Vector2D(int, int);
    Vector2D(float, float);
    Vector2D(double, double);
    
    Vector2D rotated(double angle);
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
