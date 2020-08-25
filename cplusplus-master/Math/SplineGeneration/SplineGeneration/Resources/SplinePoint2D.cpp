//
//  SplinePoint2D.cpp
//  SplineGeneration
//
//  Created by Michael Schuff on 3/27/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#include "SplinePoint2D.hpp"


SplinePoint2D::SplinePoint2D(vector<Point2D> controls) : Point2D(controls[0]), controlPoints(controls) {
    
}

SplinePoint2D::SplinePoint2D(Point2D point, vector<Point2D> controls) : Point2D(point), controlPoints(controls) {
    controlPoints.insert(controlPoints.begin(), point);
}

SplinePoint2D::SplinePoint2D(double x, double y, vector<Point2D> controls) : Point2D(x, y), controlPoints(controls){
    controlPoints.insert(controlPoints.begin(), Point2D(x, y));
}

SplinePoint2D::SplinePoint2D(vector<Vector2D> controls) : Point2D(controls[0]) {
    for (int i = 0; i < controls.size(); i++) {
//        controlPoints.push_back(controls[i].toPoint2D());
    }
}

SplinePoint2D::SplinePoint2D(Vector2D start, vector<Vector2D> controls) : Point2D(start.x, start.y) {
    for (int i = 0; i < controlPoints.size(); i++) {
        this->controlPoints.push_back(controls[i].toPoint2D());
    }
}

SplinePoint2D::SplinePoint2D(double x, double y, vector<Vector2D> controls) : Point2D(x, y) {
    for (int i = 0; i < controlPoints.size(); i++) {
        this->controlPoints.push_back(controls[i].toPoint2D());
    }
}
