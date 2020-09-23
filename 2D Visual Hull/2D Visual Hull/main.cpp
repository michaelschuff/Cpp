//
//  main.cpp
//  Road Generator
//
//  Created by Michael Schuff on 9/23/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "SplinePoint2D.hpp"
#include "Vector2D.hpp"
#include "MathFunctions.hpp"
#include "Spline2D.hpp"
#include "Hamiltonian.hpp"
#include "Camera.hpp"

using namespace std;
using namespace sf;
using namespace MathFunctions;


double degrees(double);
double radians(double);
RectangleShape VectorLine(Vector2D, Vector2D, Color);
RectangleShape Line(double, double, double, double, Color);
void DrawSpline(RenderWindow&, Spline2D, double, double, Color);
void DrawCameras(RenderWindow&, vector<Camera>, double, const int, Color);
vector<vector<Vector2D>> GeneratePoints(int, int, int, int, double);
vector<Vector2D> GenerateDerivatives(vector<Vector2D>);


int main() {
    int width = 800;
    int height = 800;
    bool reverse = false;
    double tInc = 1.0/500;
    
    enum State {leftDown, rightDown, up};
    State mouseState = up;

    srand(time(NULL));
    int rows = 2;
    int columns = 2;
    double randomness = 0;

    double mx, my, controlPointRadius = 5;
    int splinePointIndex = -1, controlPointIndex = -1, camIndex = -1;

    vector<double> multipliers = {1, 5};
    double derivativeScalar = 50;


    vector<vector<Vector2D>> pointLocations = GeneratePoints(rows, columns, width, height, randomness);
    vector<vector<Vector2D>> path = Hamiltonian::ManhattanCycleDiagonal(rows, columns);
    if (path[0][0].y != 0) {
        reverse = true;
    }


    vector<SplinePoint2D> controlPoints;
    vector<Vector2D> pathLocations;
    vector<Vector2D> pointDirections;

    Vector2D pathIndex(0, 0);
    for (int i = 0; i < rows * columns; i++) {
        pathLocations.push_back(pointLocations[pathIndex.y][pathIndex.x]);
        pathIndex -= path[pathIndex.y][pathIndex.x];
    }

    for (int i = 0; i < pathLocations.size(); i++) {
        int rIndex = (i + 1) % pathLocations.size(), lIndex = (i - 1 + pathLocations.size()) % pathLocations.size();
        Vector2D right(pathLocations[rIndex]);
        Vector2D left(pathLocations[lIndex]);
        
        right.toUnit();
        left.toUnit();
        Vector2D temp2(right - left);
        temp2.magnitude = 50;
        temp2.updateCartesian();
        pointDirections.push_back(temp2);
        
        
    }

    for (int i = 0; i < rows * columns; i++) {
        controlPoints.push_back(SplinePoint2D(vector<Vector2D> {pathLocations[i], pointDirections[i]}, multipliers));
    }
    Spline2D spline(controlPoints, true);
    
    if (reverse) {
        spline.Reverse();
    }

    const int numOfCams = 4;
    vector<Camera> cams;
    Vector2D camPos[numOfCams] = {  Vector2D(100, 100),
                                    Vector2D(100, 700),
                                    Vector2D(700, 100),
                                    Vector2D(700, 700)
    };
    for (int i = 0; i < numOfCams; i++) {
        cams.push_back(Camera(camPos[i].x, camPos[i].y));
    }
    
    RenderWindow window(VideoMode(width, height), "Road Generator");
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            } else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
               window.close();
            }

        }

        if (Mouse::isButtonPressed(Mouse::Left)) {
            mouseState = leftDown;
        } else if (Mouse::isButtonPressed(Mouse::Right)) {
            mouseState = rightDown;
        } else {
            mouseState = up;
        }

        if (mouseState != up) {
            mx = Mouse::getPosition(window).x;
            my = Mouse::getPosition(window).y;
            double minDistance = controlPointRadius;
            for (int i = 0; i < spline.controlPoints.size(); i++) {
                double x = 0, y = 0;
                for (int j = 0; j < controlPoints[i].controlPoints.size(); j++) {
                    x += spline.controlPoints[i].GetX(j);
                    y += spline.controlPoints[i].GetY(j);
                    double distFromPoint = sqrt(pow(mx-x, 2) + pow(my-y, 2));
                    if (distFromPoint < minDistance) {
                        minDistance = distFromPoint;
                        if (splinePointIndex == -1 && camIndex == -1) {
                            splinePointIndex = i;
                            controlPointIndex = j;
                        }
                    }
                }
            }
            
            for (int i = 0; i < numOfCams; i++) {
                double distFromPoint = sqrt(pow(mx-cams[i].x, 2) + pow(my-cams[i].y, 2));
                if (distFromPoint < minDistance) {
                    minDistance = distFromPoint;
                    if (camIndex == -1 && splinePointIndex == -1) {
                        camIndex = i;
                    }
                }
            }
            
            if (splinePointIndex != -1) {
                if (mouseState == leftDown) {
                    controlPoints[splinePointIndex].SetPositionKeepLocal(mx, my, controlPointIndex);
                } else if (mouseState == rightDown) {
                    controlPoints[splinePointIndex].SetPosition(mx, my, controlPointIndex);
                }
            }
            
            if (camIndex != -1) {
                cams[camIndex].x = mx;
                cams[camIndex].y = my;
                if (mouseState == leftDown) {
                    cams[camIndex].GetRays(spline, tInc);
                } else if (mouseState == rightDown) {
                    cams[camIndex].rays.clear();
                }
            }
        } else {
            splinePointIndex = -1;
            controlPointIndex = -1;
            camIndex = -1;
        }
        window.clear();
        spline.SetControlPoints(controlPoints);
        DrawSpline(window, spline, controlPointRadius, tInc, Color(255, 255, 255));
        DrawCameras(window, cams, controlPointRadius, numOfCams, Color(100, 100, 100));
        window.display();
    }
}

void DrawCameras(RenderWindow &window, vector<Camera> cams, double controlPointRadius, const int numOfCams, Color color) {
    for (int i = 0; i < numOfCams; i++) {
        for (int j = 0; j < cams[i].rays.size(); j++) {
            window.draw(VectorLine(cams[i], cams[i] + cams[i].rays[j], color));
        }
        CircleShape p(controlPointRadius);
        p.setOrigin(controlPointRadius, controlPointRadius);
        p.setFillColor(Color(255, 255, 255));
        p.setPosition(cams[i].x, cams[i].y);
        window.draw(p);
    }
}

void DrawSpline(RenderWindow &window, Spline2D spline, double controlPointRadius = 5.0, double tInc = 0.001, Color color = Color(255, 255, 255)) {
    vector<Color> controlPointColors = {Color(255, 0, 0), Color(255, 255, 0), Color(0, 255, 0), Color(0, 255, 255), Color(0, 0, 255), Color(255, 0, 255)};
    Vector2D last = spline.Get(0), current(0, 0);
    for (double t = tInc; t <= 1; t+=tInc) {
        current = spline.Get(t);
        window.draw(VectorLine(last, current, color));
        last = current;
    }

    for (int i = 0; i < spline.controlPoints.size(); i++) {
        double x = spline.controlPoints[i].GetX(0), y = spline.controlPoints[i].GetY(0);
        for (int j = 0; j < spline.controlPoints[i].controlPoints.size() - 1; j++) {
            CircleShape p(controlPointRadius);
            p.setOrigin(controlPointRadius, controlPointRadius);
            p.setFillColor(controlPointColors[j % controlPointColors.size()]);
            p.setPosition(x, y);
            window.draw(Line(x, y, x+spline.controlPoints[i].GetX(j+1), y+spline.controlPoints[i].GetY(j+1), Color(100, 100, 100)));
            window.draw(p);
            x += spline.controlPoints[i].GetX(j+1);
            y += spline.controlPoints[i].GetY(j+1);

        }
        CircleShape p(controlPointRadius);
        p.setOrigin(controlPointRadius, controlPointRadius);
        p.setFillColor(controlPointColors[spline.controlPoints[i].controlPoints.size() % controlPointColors.size()]);
        p.setPosition(x, y);
        window.draw(p);
    }
}

RectangleShape VectorLine(Vector2D v1, Vector2D v2, Color color) {
    return Line(v1.x, v1.y, v2.x, v2.y, color);
}

RectangleShape Line(double x1, double y1, double x2, double y2, Color color) {
    double x = x2 - x1;
    double y = y2 - y1;
    RectangleShape line(Vector2f(sqrt(x*x+y*y),1));
    line.setOrigin(0.5, 0.5);
    line.rotate(degrees(atan2(y,x)));
    line.setPosition(x1, y1);
    line.setFillColor(color);
    return line;
}

double radians(double deg) {
    return deg * 3.1415626535 / 180;
}

double degrees(double rad) {
    return rad * 180 / 3.1415626535;
}

vector<vector<Vector2D>> GeneratePoints(int rows, int columns, int width, int height, double randomness) {
    double pxlPerRow = (double) height / rows;
    double pxlPerColumn = (double) width / columns;
    double rX = randomness * pxlPerColumn / 2;
    double rY = randomness * pxlPerRow / 2;
    
    vector<vector<Vector2D>> points;
    
    for (double y = 0.5; y < rows; y++) {
        points.push_back(vector<Vector2D>());
        for (double x = 0.5; x < columns; x++) {
            points[(int) y].push_back(Vector2D((int) (x * pxlPerColumn + RandomRange(-rX, rX)), (int) (y * pxlPerRow + RandomRange(-rY, rY))));
        }
    }
    
    return points;
}

vector<Vector2D> GenerateDerivatives(vector<Vector2D> points) {
    for (int i = 0; i < points.size(); i++) {
        Vector2D right(points[(i + 1) % points.size()]);
        Vector2D left(points[(i - 1 + points.size()) % points.size()]);
    }
}
