//
//  MathFunctions.hpp
//  SplineGeneration
//
//  Created by Michael Schuff on 3/26/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#ifndef MathFunctions_hpp
#define MathFunctions_hpp

#include <stdio.h>
#include <cmath>
#include <vector>
#include "Point2D.hpp"

namespace MathFunctions {
    double Magnitude(double, double);
    double Distance(Point2D, Point2D);
    double Direction(Point2D);
    double Magnitude(Point2D);
    vector<vector<double>> ReducedRowEchelonForm(vector<vector<double>>);
    void ReducedRowEchelonForm(double arr[4][5]);


    template<typename T>
    vector<T> slice(vector<T> &v, int m, int n);
};

#endif /* MathFunctions_hpp */
