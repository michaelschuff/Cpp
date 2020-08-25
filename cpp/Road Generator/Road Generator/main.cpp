//
//  main.cpp
//  Road Generator
//
//  Created by Michael Schuff on 6/3/20.
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

using namespace std;
using namespace sf;
using namespace MathFunctions;

struct circle {
    double x, y, r;
};


double degrees(double);
double radians(double);
RectangleShape VectorLine(Vector2D, Vector2D, Color);
RectangleShape Line(double, double, double, double, Color);
void DrawSpline(RenderWindow&, Spline2D, double, Color);
vector<vector<Vector2D>> GeneratePoints(int, int, int, int, double);
vector<Vector2D> GenerateDerivatives(vector<Vector2D>);
circle CircleFromPoints(Vector2D, Vector2D, Vector2D);
void drawCircle(circle, RenderWindow&);
bool InTriangle(Vector2D, Vector2D, Vector2D, Vector2D);


int main() {
    int cIndex = 0;
    int width = 800;
    int height = 800;
    bool reverse = false;

    enum State {leftDown, rightDown, up};
    State mouseState = up;

    srand(time(NULL));
    int rows = RandomRange((int) 2, (int)  4);
    int columns = RandomRange((int) 2, (int) 4);
    double randomness = 0.5;

    double mx, my, controlPointRadius = 5;
    int splinePointIndex = -1, controlPointIndex = -1;

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


    vector<vector<Vector2D>> circleDerivs;
    for (int i = 0; i < pathLocations.size(); i++) {
        circleDerivs.push_back(vector<Vector2D>());
        circleDerivs[i].push_back(Vector2D(0, 0));
        circleDerivs[i].push_back(Vector2D(0, 0));
        circleDerivs[i].push_back(Vector2D(0, 0));
    }
    vector<circle> circs;
    for (int i = 0; i < pathLocations.size(); i++) {
        int rIndex = (i + 1) % pathLocations.size(), lIndex = (i - 1 + pathLocations.size()) % pathLocations.size();
        Vector2D right(pathLocations[rIndex]);
        Vector2D left(pathLocations[lIndex]);
        
        circle s = CircleFromPoints(left, pathLocations[i], right);
        circs.push_back(s);
        right.toUnit();
        left.toUnit();
        s.r = 50;
//        Vector2D temp3((double) atan2((pathLocations[i].y - s.y), (pathLocations[i].x-s.x)) - radians(90), (double) s.r);
//        Vector2D temp4((double) atan2((pathLocations[i].y - s.y), (pathLocations[i].x-s.x)) + radians(90), (double) s.r);
//        Vector2D temp5((float) (pathLocations[i].x - right.x), (float) (pathLocations[i].y - right.y));
//        temp5.magnitude = 50;
//        temp5.updateCartesian();
//
//
//        Vector2D temp1(right - left);
//        temp1.magnitude = 50;
//        temp1.updateCartesian();
//        right.toUnit();
//        left.toUnit();
        Vector2D temp2(right - left);
        temp2.magnitude = 50;
        temp2.updateCartesian();
        
//        Vector2D fin1((int) temp2.x + temp3.x, temp2.y+temp3.y);
//        Vector2D fin2((int) temp2.x + temp4.x, temp2.y+temp4.y);
//        if (temp5.x*fin1.x + temp5.y*fin1.y < temp5.x*fin2.x + temp5.y*fin2.y) {
//            pointDirections.push_back(fin1);
//        } else {
//            pointDirections.push_back(fin2);
//        }
        pointDirections.push_back(temp2);
        
        
    }
    
    vector<vector<Vector2D>> outer;
    vector<vector<Vector2D>> inner;
    
    
    for (int i = 0; i < pointDirections.size(); i++) {
        outer.push_back(vector<Vector2D>());
        inner.push_back(vector<Vector2D>());
        Vector2D temp(pointDirections[i]);
        temp.magnitude = 50;
        temp.rotate(radians(90));
        temp = temp + pathLocations[i];
        outer[i].push_back(temp);
        
        Vector2D temp2(pointDirections[i]);
        temp2.rotate(radians(270));
        temp2 = temp2 + pathLocations[i];
        inner[i].push_back(temp2);
    }
    
    for (int i = 0; i < inner.size(); i++) {
        int rIndex = (i + 1) % inner.size(), lIndex = (i - 1 + inner.size()) % inner.size();
        Vector2D right(inner[rIndex][0]);
        Vector2D left(inner[lIndex][0]);
        
        right.toUnit();
        left.toUnit();
        Vector2D temp2(right - left);
        temp2.magnitude = 50;
        if (reverse) {
            temp2.magnitude = 25;
        }
        temp2.updateCartesian();
        inner[i].push_back(temp2);
    }
    for (int i = 0; i < outer.size(); i++) {
        int rIndex = (i + 1) % outer.size(), lIndex = (i - 1 + outer.size()) % outer.size();
        Vector2D right(outer[rIndex][0]);
        Vector2D left(outer[lIndex][0]);
        
        right.toUnit();
        left.toUnit();
        Vector2D temp2(right - left);
        temp2.magnitude = 25;
        if (reverse) {
            temp2.magnitude = 50;
        }
        temp2.updateCartesian();
        outer[i].push_back(temp2);
    }
    
    
//    for (int i = 0; i < circleDerivs.size(); i++) {
//        Vector2D avg((int) 0, (int) 0);
//        double mag = 0;
//        for (int j = 0; j < circleDerivs[i].size(); j++) {
//            avg.x += circleDerivs[i][j].x;
//            avg.y += circleDerivs[i][j].y;
//            mag += circleDerivs[i][j].magnitude;
//        }
//        mag /= circleDerivs[i].size();
//        avg.theta = atan2(avg.y, avg.x);
//        avg.x = mag * cos(avg.theta);
//        avg.y = mag * sin(avg.theta);
//        pointDirections.push_back(avg);
//    }
    
    vector<SplinePoint2D> innerControlPoints;
    vector<SplinePoint2D> outerControlPoints;

    for (int i = 0; i < rows * columns; i++) {
        controlPoints.push_back(SplinePoint2D(vector<Vector2D> {pathLocations[i], pointDirections[i]}, multipliers));
        innerControlPoints.push_back(SplinePoint2D(vector<Vector2D> {inner[i][0], pointDirections[i]}, multipliers));
        outerControlPoints.push_back(SplinePoint2D(vector<Vector2D> {outer[i][0], pointDirections[i]}, multipliers));
    }

    Spline2D innerSpline(innerControlPoints, true);
    Spline2D outerSpline(outerControlPoints, true);
    Spline2D spline(controlPoints, true);
    
    if (reverse) {
        innerSpline.Reverse();
        outerSpline.Reverse();
        spline.Reverse();
    }


    RenderWindow window(VideoMode(width, height), "Road Generator");
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            } else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
               window.close();
            } else if (event.type == Event:: KeyReleased && event.key.code == Keyboard::Space) {
                cIndex = (cIndex+1) % circs.size();
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
            for (int i = 0; i < controlPoints.size(); i++) {
                double x = 0, y = 0;
                for (int j = 0; j < controlPoints[i].controlPoints.size(); j++) {
                    x += controlPoints[i].GetX(j);
                    y += controlPoints[i].GetY(j);
                    double distFromPoint = sqrt(pow(mx-x, 2) + pow(my-y, 2));
                    if (distFromPoint < minDistance) {
                        minDistance = distFromPoint;
                        splinePointIndex = i;
                        controlPointIndex = j;
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
        } else {
            splinePointIndex = -1;
            controlPointIndex = -1;
        }
        window.clear();
        drawCircle(circs[cIndex], window);
        DrawSpline(window, spline, controlPointRadius, Color(255, 255, 255));
//        DrawSpline(window, innerSpline, controlPointRadius, Color(255, 255, 255));
//        DrawSpline(window, outerSpline, controlPointRadius, Color(255, 255, 255));
//        for (int i = 0; i < circleDerivs.size(); i++) {
//            for (int j = 0; j < 3; j++) {
//                CircleShape a(3);
//
//                a.setPosition(pathLocations[i].x + circleDerivs[i][j].x, pathLocations[i].y + circleDerivs[i][j].y);
//                a.setOrigin(a.getRadius(), a.getRadius());
//                if ((i == cIndex && j == 0) || ((cIndex - 1 + circleDerivs.size())%circleDerivs.size() == i && j == 1) || ((cIndex + 1)%circleDerivs.size() == i && j == 2)) {
//                    a.setFillColor(Color(255, 255, 0));
//                    window.draw(Line(pathLocations[i].x, pathLocations[i].y, pathLocations[i].x + circleDerivs[i][j].x, pathLocations[i].y + circleDerivs[i][j].y, Color(150, 150, 0)));
//                } else {
//                    window.draw(Line(pathLocations[i].x, pathLocations[i].y, pathLocations[i].x + circleDerivs[i][j].x, pathLocations[i].y + circleDerivs[i][j].y, Color(0, 0, 100)));
//                }
//                window.draw(a);
//            }
//        }
        window.display();
    }
}

void DrawSpline(RenderWindow &window, Spline2D spline, double controlPointRadius = 5.0, Color color = Color(255, 255, 255)) {
    vector<Color> controlPointColors = {Color(255, 0, 0), Color(255, 255, 0), Color(0, 255, 0), Color(0, 255, 255), Color(0, 0, 255), Color(255, 0, 255)};
    Vector2D last = spline.Get(0), current(0, 0);
    double tInc = 0.001;
    for (double t = tInc; t < 1; t+=tInc) {
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

bool InTriangle(Vector2D a, Vector2D b, Vector2D c, Vector2D p) {
    double a1 = area(a, b, c);
    double a2 = area(p, a, b);
    double a3 = area(p, b, c);
    double a4 = area(p, a, c);
    if (abs(a1 - a2 - a3 - a4) < 1) {
        return true;
    } else {
        return false;
    }
    
}

void drawCircle(circle c, RenderWindow& window) {
    double tInc = 0.01;
    for (double t = 0; t < 2 * 3.142; t+=tInc) {
        window.draw(Line(c.x + c.r*cos(t-tInc), c.y + c.r * sin(t-tInc), c.x + c.r*cos(t), c.y + c.r * sin(t), Color(100, 100, 100)));
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

circle CircleFromPoints(Vector2D p1, Vector2D p2, Vector2D p3) {
    vector<vector<double>> equationMatrix;
    
    equationMatrix.push_back(vector<double> {2 * (p2.x-p1.x), 2 * (p2.y-p1.y), (p2.x*p2.x + p2.y*p2.y) - (p1.x*p1.x + p1.y*p1.y)});
    equationMatrix.push_back(vector<double> {2 * (p1.x-p3.x), 2 * (p1.y-p3.y), (p1.x*p1.x + p1.y*p1.y) - (p3.x*p3.x + p3.y*p3.y)});
    
    
    vector<double> center = RREFOutput(ReducedRowEchelonForm(equationMatrix));
    
    circle c;
    c.x = center[0];
    c.y = center[1];
    c.r = sqrt(pow(p1.x-c.x, 2) + pow(p1.y-c.y, 2));
    return c;
}
