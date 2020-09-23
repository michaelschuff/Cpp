//
//  Spline2D.hpp
//  2D Visual Hull
//
//  Created by Michael Schuff on 9/23/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#ifndef Spline2D_hpp
#define Spline2D_hpp

#include <stdio.h>
#include <vector>
#include <cmath>
#include "MathFunctions.hpp"
#include "SplinePoint2D.hpp"

using namespace std;

class Spline2D {
public:
    vector<SplinePoint2D> controlPoints;
    Spline2D(vector<SplinePoint2D>, bool);
    Vector2D Get(double);
    void SetControlPoints(vector<SplinePoint2D>);
    void Reverse();
private:
    int degree;
    bool continuous;
    bool reversed;
    double length;
    vector<double> curveLengths;
    vector<vector<Vector2D>> coefficients;
    void Update();
    void Calculate(SplinePoint2D, SplinePoint2D);
    Vector2D GetPoint(double, int);
};


#endif /* Spline2D_hpp */
