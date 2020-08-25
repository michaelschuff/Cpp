//
//  Vector2D.cpp
//  SplineGeneration
//
//  Created by Michael Schuff on 3/26/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#include "Vector2D.hpp"

using namespace std;


Vector2D::Vector2D(Point2D point) : Point2D(point.x, point.y) {
    this->updatePolar();
}

Vector2D::Vector2D(float x, float y) : Point2D(x, y) {
    this->updatePolar();
}

Vector2D::Vector2D(double theta, double magnitude) : Point2D((float) magnitude * cos(theta), (float) magnitude * sin(theta)), theta(theta), magnitude(magnitude) {
    
}

Vector2D Vector2D::rotated(double angle) {
    return Vector2D(theta + angle, magnitude);
}

Point2D Vector2D::toPoint2D() {
    return Point2D(x, y);
}

void Vector2D::rotate(double angle) {
    this->theta += angle;
    this->updateCartesian();
}

Vector2D Vector2D::operator-() {
    return Vector2D(-x, -y);
}

Vector2D operator+(Vector2D& v1, Vector2D& v2) {
    return Vector2D(v1.x+v2.x, v1.y+v2.y);
}

Vector2D operator-(Vector2D& v1, Vector2D& v2) {
    return Vector2D(v1.x-v2.x, v1.y-v2.y);
}

Vector2D operator*(Vector2D& v1, double& scalar) {
    return Vector2D(v1.theta, v1.magnitude * scalar);
}

Vector2D operator/(Vector2D& v1, double& scalar) {
    return Vector2D(v1.theta, v1.magnitude / scalar);
}

void Vector2D::operator+=(Vector2D& other) {
    this->x += other.x;
    this->y += other.y;
}

void Vector2D::operator-=(Vector2D& other) {
    this->x -= other.x;
    this->y -= other.y;
}

void Vector2D::operator*=(double& scalar) {
    this->magnitude *= scalar;
    this->updateCartesian();
}

void Vector2D::operator/=(double& scalar) {
    this->magnitude /= scalar;
    this->updateCartesian();
}

void Vector2D::updateCartesian() {
    this->x = magnitude * cos(theta);
    this->y = magnitude * sin(theta);
}
void Vector2D::updatePolar() {
    this->magnitude = MathFunctions::Magnitude(x, y);
    this->theta = atan2(y, x);
}
