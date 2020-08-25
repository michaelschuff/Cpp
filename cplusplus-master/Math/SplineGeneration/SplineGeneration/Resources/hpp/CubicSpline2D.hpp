//
//  CubicSpline2D.hpp
//  SplineGeneration
//
//  Created by Michael Schuff on 3/27/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#ifndef CubicSpline2D_hpp
#define CubicSpline2D_hpp

#include <stdio.h>
#include <vector>
#include "Spline2D.hpp"
#include "Point2D.hpp"
#include "Vector2D.hpp"
#include "CubicSplinePoint2D.hpp"


class CubicSpline2D : public Spline2D {
public:
    CubicSpline2D(vector<CubicSplinePoint2D>, bool);
    CubicSpline2D(CubicSplinePoint2D, CubicSplinePoint2D, bool);
    CubicSpline2D(vector<Point2D>, bool);
    CubicSpline2D(Point2D, Point2D, bool);
    CubicSpline2D(vector<Vector2D>, bool);
    CubicSpline2D(Vector2D, Vector2D, bool);
};

#endif /* CubicSpline2D_hpp */
