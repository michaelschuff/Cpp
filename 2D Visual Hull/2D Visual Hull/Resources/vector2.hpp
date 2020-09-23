//
//  vector2.hpp
//  2D Visual Hull
//
//  Created by Michael Schuff on 9/23/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#ifndef vector2_hpp
#define vector2_hpp

#include <stdio.h>
#include <cmath>

template <class T>

class vector2 {
public:
    T x, y;
    vector2() : x(0), y(0) {}
    vector2(T x, T y) : x(x), y(y) {}
    vector2(const vector2& v) : x(v.x), y(v.y) {}
    
    vector2& operator=(const vector2& v) {
        x = v.x;
        y = v.y;
        return *this;
    }
    
    vector2 operator+(vector2& v) {
        return vector2(x + v.x, y + v.y);
    }
    vector2 operator-(vector2& v) {
        return vector2(x - v.x, y - v.y);
    }
    
    vector2& operator+=(vector2& v) {
        x += v.x;
        y += v.y;
        return *this;
    }
    vector2& operator-=(vector2& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }
    
    vector2 operator+(double s) {
        return vector2(x + s, y + s);
    }
    vector2 operator-(double s) {
        return vector2(x - s, y - s);
    }
    vector2 operator*(double s) {
        return vector2(x * s, y * s);
    }
    vector2 operator/(double s) {
        return vector2(x / s, y / s);
    }
    
    
    vector2& operator+=(double s) {
        x += s;
        y += s;
        return *this;
    }
    vector2& operator-=(double s) {
        x -= s;
        y -= s;
        return *this;
    }
    vector2& operator*=(double s) {
        x *= s;
        y *= s;
        return *this;
    }
    vector2& operator/=(double s) {
        x /= s;
        y /= s;
        return *this;
    }
    
    void set(T x, T y) {
        this->x = x;
        this->y = y;
    }
    
    void rotate(double deg) {
        double theta = deg / 180.0 * M_PI;
        double c = cos(theta);
        double s = sin(theta);
        double tx = x * c - y * s;
        double ty = x * s + y * c;
        x = tx;
        y = ty;
    }
    
    vector2& normalize() {
        if (length() == 0) return *this;
        *this *= (1.0 / length());
        return *this;
    }
    
    float dist(vector2 v) const {
        vector2 d(v.x - x, v.y - y);
        return d.length();
    }
    float length() const {
        return std::sqrt(x * x + y * y);
    }
    void truncate(double length) {
        double angle = atan2f(y, x);
        x = length * cos(angle);
        y = length * sin(angle);
    }

    vector2 ortho() const {
        return vector2(y, -x);
    }
    
    static float dot(vector2 v1, vector2 v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }
    static float cross(vector2 v1, vector2 v2) {
        return (v1.x * v2.y) - (v1.y * v2.x);
    }
};

#endif /* vector2_hpp */
