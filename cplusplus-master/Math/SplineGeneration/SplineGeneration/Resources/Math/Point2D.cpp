//
//  Point2D.cpp
//  SplineGeneration
//
//  Created by Michael Schuff on 3/26/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#include "Point2D.hpp"

using namespace std;

Point2D::Point2D() : x(0), y(0) {
    
}

Point2D::Point2D(double x, double y) : x(x), y(y) {
    
}

Point2D Point2D::operator-() {
    return Point2D(-x, -y);
}

Point2D operator+(Point2D& p1, Point2D& p2) {
    return Point2D(p1.x+p2.x, p1.y+p2.y);
}

Point2D operator-(Point2D& p1, Point2D& p2) {
    return Point2D(p1.x-p2.x, p1.y-p2.y);
}

void Point2D::operator+=(Point2D& other) {
    this->x += other.x;
    this->y += other.y;
}

void Point2D::operator-=(Point2D& other) {
    this->x -= other.x;
    this->y -= other.y;
}

