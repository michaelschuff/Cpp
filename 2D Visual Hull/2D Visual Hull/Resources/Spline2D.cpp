//
//  Spline2D.cpp
//  2D Visual Hull
//
//  Created by Michael Schuff on 9/23/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#include "Spline2D.hpp"
Spline2D::Spline2D(vector<SplinePoint2D> controls, bool continuous) {
    this->continuous = continuous;
    degree = 2 * controls[0].controlPoints.size() - 1;
    for(int i = 0; i < controls.size(); i++) {
        this->controlPoints.push_back(controls[i]);
    }
    this->Update();
}

void Spline2D::Update() {
    if (this->continuous) {
        for (int i = 0; i < controlPoints.size(); i++) {
            Calculate(controlPoints[i], controlPoints[(i + 1) % controlPoints.size()]);
        }
    } else {
        for (int i = 1; i < controlPoints.size(); i++) {
            Calculate(controlPoints[i - 1], controlPoints[i]);
        }
    }
    
    double tInc = 0.0001, lastx, lasty;
    for (int i = 0; i < coefficients.size(); i++) {
        curveLengths.push_back(0);
        lastx = coefficients[i][coefficients[i].size() - 1].x;
        lasty = coefficients[i][coefficients[i].size() - 1].y;
        for (double t = tInc; t <= 1; t += tInc) {
            Vector2D p = GetPoint(t, i);
            curveLengths[i] += sqrt(pow(p.x-lastx, 2)+pow(p.y-lasty, 2));
            lastx = p.x;
            lasty = p.y;
        }
    }
    
    length = 0;
    for (int i = 0; i < curveLengths.size(); i++) {
        length += curveLengths[i];
    }
}


void Spline2D::Calculate(SplinePoint2D start, SplinePoint2D end) {
    vector<double> startCoeffs, endCoeffs;
    for (int i = 0; i < degree+1; i++) {
        startCoeffs.push_back(0);
        endCoeffs.push_back(1);
    }
    startCoeffs[degree] = 1;
    
    vector<vector<double>> xMatrix;
    int maxPow = degree;
    for (int i = 0; i < start.controlPoints.size(); i++) {
        xMatrix.push_back(startCoeffs);
        xMatrix[xMatrix.size() - 1].push_back(start.controlPoints[i].x);
        
        swap(startCoeffs[startCoeffs.size() - 1 - i], startCoeffs[startCoeffs.size() - 2 - i]);
    }
    
    for (int i = 0; i < end.controlPoints.size(); i++) {
        xMatrix.push_back(endCoeffs);
        xMatrix[xMatrix.size() - 1].push_back(end.controlPoints[i].x);
        
        for (int j = maxPow; j >= 0; j--) {
            endCoeffs[maxPow-j] *= j;
        }
        maxPow--;
    }
    
    vector<vector<double>> yMatrix(xMatrix);
    for (int i = 0; i < end.controlPoints.size(); i++) {
        yMatrix[i + end.controlPoints.size()][yMatrix[i].size() - 1] = end.controlPoints[i].y;
        yMatrix[i][yMatrix[i].size() - 1] = start.controlPoints[i].y;
    }
    vector<double> xCoefficients = MathFunctions::RREFOutput(MathFunctions::ReducedRowEchelonForm(xMatrix));
    vector<double> yCoefficients = MathFunctions::RREFOutput(MathFunctions::ReducedRowEchelonForm(yMatrix));
    vector<Vector2D> c;
    
    for (int i = 0; i < xCoefficients.size(); i++) {
        c.push_back(Vector2D((float) xCoefficients[i], (float) yCoefficients[i]));
    }
    
    this->coefficients.push_back(c);
    
}

Vector2D Spline2D::Get(double p) {
    if (reversed) {
        p = 1 - p;
    }
    double distanceAlongPath = p * length;
    for (int i = 0; i < curveLengths.size(); i++) {
        if (distanceAlongPath - curveLengths[i] > 0) {
            distanceAlongPath -= curveLengths[i];
        } else {
            double t = distanceAlongPath / curveLengths[i];
            return GetPoint(t, i);
        }
    }
}
Vector2D Spline2D::GetPoint(double t, int index) {
    Vector2D point((float) 0, (float) 0);
    for (int i = 0; i < coefficients[index].size(); i++) {
        point.x += coefficients[index][i].x * pow(t, coefficients[index].size() - 1 - i);
        point.y += coefficients[index][i].y * pow(t, coefficients[index].size() - 1 - i);
    }
    return point;
}

void Spline2D::SetControlPoints(vector<SplinePoint2D> controls) {
    this->controlPoints = controls;
    this->curveLengths = vector<double>();
    this->coefficients = vector<vector<Vector2D>>();
    degree = 2 * controls[0].controlPoints.size() - 1;
    
    this->Update();
}

void Spline2D::Reverse() {
    this->reversed = !this->reversed;
}
