//
//  Vector2D.hpp
//  2D Visual Hull
//
//  Created by Michael Schuff on 9/23/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#ifndef Vector2D_hpp
#define Vector2D_hpp

#include <stdio.h>

using namespace std;

class Vector2D {
public:
    float x, y;
    double theta, magnitude;
    
    Vector2D(int, int);
    Vector2D(float, float);
    Vector2D(double, double);
    
    Vector2D rotated(double angle);
    void rotate(double angle);
    Vector2D unit();
    void toUnit();
    
    Vector2D operator-();
    void operator+=(Vector2D&);
    void operator-=(Vector2D&);
    void operator*=(double&);
    void operator/=(double&);
    
    void updateCartesian();
    void updatePolar();
};

Vector2D operator+(Vector2D&, Vector2D&);

Vector2D operator-(Vector2D&, Vector2D&);

Vector2D operator*(Vector2D&, double&);

Vector2D operator/(Vector2D&, double&);

double angleBetween(Vector2D&, Vector2D&);

double dot(Vector2D&, Vector2D&);

double area(Vector2D&, Vector2D&, Vector2D&);

bool operator==(Vector2D&, Vector2D&);

#endif /* Vector2D_hpp */

