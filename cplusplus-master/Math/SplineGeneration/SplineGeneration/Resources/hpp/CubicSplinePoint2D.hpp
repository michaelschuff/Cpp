//
//  CubicSplinePoint2D.hpp
//  SplineGeneration
//
//  Created by Michael Schuff on 3/26/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#ifndef CubicSplinePoint2D_hpp
#define CubicSplinePoint2D_hpp

#include <stdio.h>
#include "SplinePoint2D.hpp"
#include "Point2D.hpp"
#include "Vector2D.hpp"

class CubicSplinePoint2D : public SplinePoint2D {
public:
    double direction, magnitude;
    
//    CubicSplinePoint2D(double, double, double, double);
//    CubicSplinePoint2D(Vector2D, double, double);
//    CubicSplinePoint2D(Point2D, double, double);
//    CubicSplinePoint2D(double, double, Vector2D);
//    CubicSplinePoint2D(double, double, Point2D);
//    CubicSplinePoint2D(Vector2D, Vector2D);
    CubicSplinePoint2D(Point2D, Point2D);
//    CubicSplinePoint2D(Vector2D, Point2D);
//    CubicSplinePoint2D(Point2D, Vector2D);
};
#endif /* CubicSplinePoint2D_hpp */
