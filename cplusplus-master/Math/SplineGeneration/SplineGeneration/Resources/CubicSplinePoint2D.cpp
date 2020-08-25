//
//  CubicSplinePoint2D.cpp
//  SplineGeneration
//
//  Created by Michael Schuff on 3/26/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#include "CubicSplinePoint2D.hpp"
#include "SplinePoint2D.hpp"
#include "Point2D.hpp"
#include "Vector2D.hpp"

//CubicSplinePoint2D::CubicSplinePoint2D(double x, double y, double direction, double magnitude) : SplinePoint2D(x, y, vector<Vector2D> {Vector2D(direction, magnitude)}), direction(direction), magnitude(magnitude) {
//
//}
//
//CubicSplinePoint2D::CubicSplinePoint2D(Vector2D target, double direction, double magnitude) : SplinePoint2D(target, vector<Vector2D> {Vector2D(direction, magnitude)}), direction(direction), magnitude(magnitude) {
//
//}
//
//CubicSplinePoint2D::CubicSplinePoint2D(Point2D target, double direction, double magnitude) : SplinePoint2D(target, vector<Vector2D> {Vector2D(direction, magnitude)}), direction(direction), magnitude(magnitude) {
//
//}
//
//CubicSplinePoint2D::CubicSplinePoint2D(double x, double y, Vector2D control): SplinePoint2D(x, y, vector<Vector2D> {control}), direction(control.theta), magnitude(control.magnitude) {
//
//}
//
//CubicSplinePoint2D::CubicSplinePoint2D(double x, double y, Point2D control): SplinePoint2D(x, y, vector<Vector2D> {Vector2D(control)}), direction(MathFunctions::Direction(control)), magnitude(MathFunctions::Magnitude(control)) {
//
//}
//
//CubicSplinePoint2D::CubicSplinePoint2D(Vector2D target, Vector2D control) : SplinePoint2D(vector<Vector2D> {target, control}), direction(control.theta), magnitude(control.magnitude) {
//
//}

CubicSplinePoint2D::CubicSplinePoint2D(Point2D target, Point2D control) : SplinePoint2D(vector<Vector2D> {Vector2D(target), Vector2D(control.x-target.x, control.y-target.y)}), direction(atan2(control.y-target.y, control.x-target.x)), magnitude(sqrt(pow(control.x-target.x, 2)+pow(control.y-target.y, 2))) {
    controlPoints.push_back(target);
    controlPoints.push_back(Point2D(control.x - target.x, control.y - target.y));
}

//CubicSplinePoint2D::CubicSplinePoint2D(Point2D target, Vector2D control) : SplinePoint2D(vector<Vector2D> {Vector2D(target), control}), direction(control.theta), magnitude(control.magnitude) {
//
//}
//
//CubicSplinePoint2D::CubicSplinePoint2D(Vector2D target, Point2D control) : SplinePoint2D(vector<Vector2D> {target, Vector2D(control)}), direction(MathFunctions::Direction(control)), magnitude(MathFunctions::Magnitude(control)) {
//
//}
