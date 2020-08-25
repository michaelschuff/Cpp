//
//  Spline2D.cpp
//  SplineGeneration
//
//  Created by Michael Schuff on 3/26/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#include "Spline2D.hpp"

using namespace std;

Spline2D::Spline2D(int degree, bool continuous) : degree(degree), continuous(continuous) {
    
}

Point2D Spline2D::Get(double time) {
    double x = 0, y = 0;

    for (int i = degree; i >= 0; i--) {
        x += pow(time, i) * xCoefficients[0][degree - i];
        y += pow(time, i) * yCoefficients[0][degree - i];
    }
    return Point2D(x, y);
}

void Spline2D::AddCoefficients(vector<double> xCoeffs, vector<double> yCoeffs) {
    xCoefficients.push_back(xCoeffs);
    yCoefficients.push_back(yCoeffs);
}

void Spline2D::Calculate() {
    for (int i = 1; i < controlPoints.size(); i++) {
        CalculateCoefficients(controlPoints[i - 1], controlPoints[i]);
    }
    
}

void Spline2D::CalculateCoefficients(vector<Point2D> start, vector<Point2D> end) {
//    double x[][5] = {
//        {3, 2, 1, 0, end[1].x},
//        {1, 1, 1, 1, end[0].x},
//        {0, 0, 1, 0, start[1].x},
//        {0, 0, 0, 1, start[0].x}
//    };
//    double y[][5] = {
//        {3, 2, 1, 0, end[1].y},
//        {1, 1, 1, 1, end[0].y},
//        {0, 0, 1, 0, start[1].y},
//        {0, 0, 0, 1, start[0].y}
//    };
    if (degree == 3) {
        vector<vector<double>> x = {
            {3, 2, 1, 0, end[1].x},
            {1, 1, 1, 1, end[0].x},
            {0, 0, 1, 0, start[1].x},
            {0, 0, 0, 1, start[0].x}
        };
        vector<vector<double>> y = {
            {3, 2, 1, 0, end[1].y},
            {1, 1, 1, 1, end[0].y},
            {0, 0, 1, 0, start[1].y},
            {0, 0, 0, 1, start[0].y}
        };
        x = MathFunctions::ReducedRowEchelonForm(x);
        y = MathFunctions::ReducedRowEchelonForm(y);
        
        this->AddCoefficients({x[0][4], x[1][4], x[2][4], x[3][4]}, {y[0][4], y[1][4], y[2][4], y[3][4]});
    }
}
