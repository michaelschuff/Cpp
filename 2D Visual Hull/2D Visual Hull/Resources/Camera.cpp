//
//  Camera.cpp
//  2D Visual Hull
//
//  Created by Michael Schuff on 9/23/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#include "Camera.hpp"
#include "Vector2D.hpp"
#include "Spline2D.hpp"
#include <iostream>

using namespace std;

Camera::Camera(int x, int y) : Vector2D(x, y) {}

void Camera::GetRays(Spline2D &spline, double tInc) {
    rays.clear();
    Vector2D prevPoint = spline.Get(0);
    for (double t = tInc; t <= 1 + tInc; t += tInc) {
        Vector2D point = spline.Get(t);
        Vector2D ray(point.x - this->x, point.y - this->y);
        Vector2D pp = spline.Get(0);
        bool temp = false;
        for (double t2 = tInc; t2 <= 1 + tInc; t2 += tInc) {
            Vector2D p = spline.Get(t2);
            if (intersection(this->x, this->y, point.x, point.y, pp.x, pp.y, p.x, p.y)) {
                temp = true;
                break;
            }
            pp = p;
        }
        if (!temp) {
            rays.push_back(ray);
        }
        prevPoint = point;
    }
}

bool Camera::intersection(double p0_x, double p0_y, double p1_x, double p1_y, double p2_x, double p2_y, double p3_x, double p3_y) {
    double s1_x, s1_y, s2_x, s2_y;
    s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
    s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

    double s, t;
    s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
    t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

    if (s >= 0 && s <= 1 && t > 0 && t < 1) {
//        if (i_x != NULL)
//            *i_x = p0_x + (t * s1_x);
//        if (i_y != NULL)
//            *i_y = p0_y + (t * s1_y);
        return true;
    }

    return false;
}
