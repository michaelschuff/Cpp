//
//  Spline2D.hpp
//  SplineGeneration
//
//  Created by Michael Schuff on 3/26/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#ifndef Spline2D_hpp
#define Spline2D_hpp

#include <stdio.h>
#include <vector>
#include "SplinePoint2D.hpp"

class Spline2D {
public:
    vector<vector<Point2D>> controlPoints;
    
    Spline2D(int, bool);
    Point2D Get(double);
    void Calculate();
private:
    int degree;
    bool continuous;
    vector<vector<double>> xCoefficients;
    vector<vector<double>> yCoefficients;
    void AddCoefficients(vector<double>, vector<double>);
    void CalculateCoefficients(vector<Point2D>, vector<Point2D>);
};

#endif /* Spline2D_hpp */
