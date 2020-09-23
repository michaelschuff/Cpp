//
//  SplinePoint2D.hpp
//  2D Visual Hull
//
//  Created by Michael Schuff on 9/23/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#ifndef SplinePoint2D_hpp
#define SplinePoint2D_hpp

#include <stdio.h>
#include <vector>
#include "Vector2D.hpp"

using namespace std;

class SplinePoint2D : public Vector2D {
public:
    vector<Vector2D> controlPoints;
    SplinePoint2D(vector<Vector2D>, vector<double>);
    SplinePoint2D(vector<vector<double>>, vector<double>);
    void SetPositionKeepLocal(double, double, int);
    void SetPosition(double, double, int);
    double GetX(int);
    double GetY(int);
private:
    vector<double> multipliers;
};

#endif /* SplinePoint_hpp */
