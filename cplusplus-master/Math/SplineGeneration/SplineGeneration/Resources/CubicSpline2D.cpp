//
//  CubicSpline2D.cpp
//  SplineGeneration
//
//  Created by Michael Schuff on 3/27/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#include "CubicSpline2D.hpp"

CubicSpline2D::CubicSpline2D(vector<CubicSplinePoint2D> points, bool continuous) : Spline2D(3, continuous) {
    for (int i = 0; i < points.size(); i++) {
        this->controlPoints.push_back(points[i].controlPoints);
//        controlPoints[i].insert(controlPoints[i].begin(), Point2D(points[i].x, points[i].y));
    }
}

CubicSpline2D::CubicSpline2D(CubicSplinePoint2D start, CubicSplinePoint2D end, bool continuous) : Spline2D(3, continuous) {
    this->controlPoints.push_back(start.controlPoints);
    this->controlPoints[0].insert(controlPoints[0].begin(), Point2D(start.x, start.y));
    this->controlPoints.push_back(end.controlPoints);
    this->controlPoints[1].insert(controlPoints[1].begin(), Point2D(end.x, end.y));
}

CubicSpline2D::CubicSpline2D(vector<Point2D> points, bool continuous) : Spline2D(3, continuous) {
//    for (int i = 0; i < points.size(); i++) {
//        CubicSplinePoint2D point(points[i], 0, 1);
//        controlPoints.push_back(point.controlPoints);
//        controlPoints[i].insert(controlPoints[i].begin(), Point2D(point.x, point.y));
//    }
}

CubicSpline2D::CubicSpline2D(Point2D start, Point2D end, bool continuous) : Spline2D(3, continuous) {
//    controlPoints.push_back(CubicSplinePoint2D(start, 0, 1).controlPoints);
//    controlPoints[0].insert(controlPoints[0].begin(), Point2D(start.x, start.y));
//
//    controlPoints.push_back(CubicSplinePoint2D(end, 0, 1).controlPoints);
//    controlPoints[1].insert(controlPoints[1].begin(), Point2D(end.x, end.y));
}

CubicSpline2D::CubicSpline2D(vector<Vector2D> points, bool continuous) : Spline2D(3, continuous) {
//    for (int i = 0; i < points.size(); i++) {
//        CubicSplinePoint2D point(points[i], 0, 1);
//        controlPoints.push_back(point.controlPoints);
//        controlPoints[i].insert(controlPoints[i].begin(), Point2D(point.x, point.y));
//    }
}

CubicSpline2D::CubicSpline2D(Vector2D start, Vector2D end, bool continuous) : Spline2D(3, continuous) {
//    controlPoints.push_back(CubicSplinePoint2D(start, 0, 1).controlPoints);
//    controlPoints[0].insert(controlPoints[0].begin(), Point2D(start.x, start.y));
//    
//    controlPoints.push_back(CubicSplinePoint2D(end, 0, 1).controlPoints);
//    controlPoints[1].insert(controlPoints[1].begin(), Point2D(end.x, end.y));
}
