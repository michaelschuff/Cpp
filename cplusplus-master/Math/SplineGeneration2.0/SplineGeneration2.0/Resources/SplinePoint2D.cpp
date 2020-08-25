//
//  SplinePoint2D.cpp
//  SplineGeneration2.0
//
//  Created by Michael Schuff on 4/9/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#include "SplinePoint2D.hpp"

SplinePoint2D::SplinePoint2D(vector<Vector2D> controls, vector<double> multipliers) : Vector2D((float) controls[0].x, (float) controls[0].y), multipliers(multipliers) {
    for (int i = 0; i < controls.size(); i++) {
        this->controlPoints.push_back(Vector2D((float) (multipliers[i] * controls[i].x), (float) (multipliers[i] * controls[i].y)));
    }
}

SplinePoint2D::SplinePoint2D(vector<vector<double>> controls, vector<double> multipliers) : Vector2D((float) controls[0][0], (float) controls[0][1]), multipliers(multipliers) {
    for (int i = 0; i < controls.size(); i++) {
        this->controlPoints.push_back(Vector2D((float) (multipliers[i] * controls[i][0]), (float) (multipliers[i] * controls[i][1])));
    }
}

void SplinePoint2D::SetPositionKeepLocal(double newX, double newY, int baseIndex) {
    for (int i = 0; i < baseIndex; i++) {
        newX -= controlPoints[i].x * multipliers[i];
        newY -= controlPoints[i].y * multipliers[i];
    }
    controlPoints[baseIndex] = Vector2D((float) (newX * multipliers[baseIndex]), (float) (newY * multipliers[baseIndex]));
}

void SplinePoint2D::SetPosition(double newX, double newY, int baseIndex) {
    for (int i = 0; i < baseIndex; i++) {
        newX -= controlPoints[i].x * multipliers[i];
        newY -= controlPoints[i].y * multipliers[i];
    }
    newX = newX * multipliers[baseIndex];
    newY = newY * multipliers[baseIndex];
    double offX = newX - controlPoints[baseIndex].x;
    double offY = newY - controlPoints[baseIndex].y;
    controlPoints[baseIndex] = Vector2D((float) newX, (float) newY);
    for (int i = baseIndex + 1; i < controlPoints.size(); i++) {
        controlPoints[i].x -= offX * multipliers[i];
        controlPoints[i].y -= offY * multipliers[i];
    }
}

double SplinePoint2D::GetX(int i) {
    return controlPoints[i].x / multipliers[i];
}

double SplinePoint2D::GetY(int i) {
    return controlPoints[i].y / multipliers[i];
}


