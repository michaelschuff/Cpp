//
//  SplinePoint2D.hpp
//  SplineGeneration
//
//  Created by Michael Schuff on 3/27/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#ifndef SplinePoint2D_hpp
#define SplinePoint2D_hpp

#include <stdio.h>
#include <vector>
#include "Point2D.hpp"
#include "Vector2D.hpp"

class SplinePoint2D : public Point2D {
public:
    vector<Point2D> controlPoints;
    SplinePoint2D(vector<Point2D>);
    SplinePoint2D(Point2D, vector<Point2D>);
    SplinePoint2D(double, double, vector<Point2D>);
    SplinePoint2D(vector<Vector2D>);
    SplinePoint2D(Vector2D, vector<Vector2D>);
    SplinePoint2D(double, double, vector<Vector2D>);
};

#endif /* SplinePoint2D_hpp */
