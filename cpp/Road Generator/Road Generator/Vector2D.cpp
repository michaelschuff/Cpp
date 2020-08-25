//
//  Vector2D.cpp
//  Road Generator
//
//  Created by Michael Schuff on 6/3/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#include "Vector2D.hpp"
#include <cmath>

using namespace std;

Vector2D::Vector2D(int x, int y) : x((float) x), y((float) y) {
    this->updatePolar();
}

Vector2D::Vector2D(float x, float y) : x(x), y(y) {
    this->updatePolar();
}

Vector2D::Vector2D(double theta, double magnitude) : theta(theta), magnitude(magnitude) {
    this->updateCartesian();
}

Vector2D Vector2D::rotated(double angle) {
    return Vector2D((double) theta + angle, (double) magnitude);
}

void Vector2D::rotate(double angle) {
    this->theta += angle;
    this->updateCartesian();
}

Vector2D Vector2D::unit() {
    return Vector2D((double) theta, (double) 1);
}

void Vector2D::toUnit() {
    this->magnitude = 1;
    updateCartesian();
}

double dot(Vector2D& v1, Vector2D& v2) {
    return v1.x*v2.x+v1.y*v2.y;
}

double area(Vector2D& v1, Vector2D& v2, Vector2D& v3) {
    return abs((v1.x*(v2.y-v3.y) + v2.x*(v3.y-v1.y) + v3.x*(v1.y-v2.y))/2.0);
}


double angleBetween(Vector2D& v1, Vector2D& v2) {
    return acos(dot(v1, v2) / (v1.magnitude * v2.magnitude));
}

void Vector2D::operator+=(Vector2D& other) {
    this->x += other.x;
    this->y += other.y;
    this->updatePolar();
}

void Vector2D::operator-=(Vector2D& other) {
    this->x -= other.x;
    this->y -= other.y;
    this->updatePolar();
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
    this->x = this->magnitude * cos(this->theta);
    this->y = this->magnitude * sin(this->theta);
}
void Vector2D::updatePolar() {
    this->magnitude = sqrt(this->x * this->x + this->y * this->x);
    this->theta = atan2(this->y, this->x);
}

Vector2D Vector2D::operator-() {
    return Vector2D((float) -x,(float)  -y);
}

Vector2D operator+(Vector2D& v1, Vector2D& v2) {
    return Vector2D((float) v1.x+v2.x, (float) v1.y+v2.y);
}

Vector2D operator-(Vector2D& v1, Vector2D& v2) {
    return Vector2D((float) v1.x-v2.x, (float) v1.y-v2.y);
}

Vector2D operator*(Vector2D& v1, double& scalar) {
    return Vector2D((double) v1.theta, (double) v1.magnitude * scalar);
}

Vector2D operator/(Vector2D& v1, double& scalar) {
    return Vector2D((double) v1.theta, (double) v1.magnitude / scalar);
}

bool operator==(Vector2D& v1, Vector2D& v2) {
    return v1.x == v2.x && v1.y == v2.y;
}
