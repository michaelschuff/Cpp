#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "CubicSpline2D.hpp"
#include "CubicSplinePoint2D.hpp"
#include "Point2D.hpp"
#include "MathFunctions.hpp"

using namespace std;
using namespace sf;

double degrees(double);
double radians(double);
RectangleShape PointLine(CircleShape, CircleShape);
RectangleShape Line(double, double, double, double, Color);

int main() {
    double x1 = 200, y1 = 200, x2 = 500, y2 = 700;
    double dx1=-100,dy1=0,dx2=0,dy2=100;
    double d1mult = 1, d2mult = 1;
    double prevX, prevY, newX, newY;
    double tInc = 0.01;
    int pointIndex = -1, pointIndex2 = -1;
    bool left;

    int diffx, diffy;
    
    CircleShape p1(5), dp1(5), ddp1(5);
    p1.setOrigin(2.5, 2.5);
    p1.setPosition(x1, y1);
    p1.setFillColor(Color(200, 0, 0));
    dp1.setOrigin(2.5, 2.5);
    dp1.setPosition(x1+dx1, y1+dy1);
    dp1.setFillColor(Color(0, 200, 0));

    CircleShape p2(5), dp2(5), ddp2(5);
    p2.setOrigin(2.5, 2.5);
    p2.setPosition(x2, y2);
    p2.setFillColor(Color(200, 0, 0));
    dp2.setOrigin(2.5, 2.5);
    dp2.setPosition(x2+dx2, y2+dy2);
    dp2.setFillColor(Color(0, 200, 0));

    CircleShape points[2][2] = {{p1, dp1}, {p2, dp2}};
    
    


    prevX = points[0][0].getPosition().x;
    prevY = points[0][0].getPosition().y;
    RenderWindow window(VideoMode(800, 800), "Cubic Spline");
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
               window.close();
            }

        }
        if (Mouse::isButtonPressed(Mouse::Left)) {
            left = true;
            if (pointIndex == -1) {
                double minDistance = 100;
                for (int i = 0; i < 2; i++) {
                    for (int j = 0; j < 2; j++) {
                        double distFromPoint = sqrt(pow(Mouse::getPosition(window).x-points[i][j].getPosition().x, 2) + pow(Mouse::getPosition(window).y-points[i][j].getPosition().y, 2));
                        if (distFromPoint < points[i][j].getRadius() && distFromPoint < minDistance) {
                            minDistance = distFromPoint;
                            pointIndex = i;
                            pointIndex2 = j;
                        }

                    }
                }
            }
        } else if (Mouse::isButtonPressed(Mouse::Right)) {
            left = false;
            if (pointIndex == -1) {
                double minDistance = 100;
                for (int i = 0; i < 2; i++) {
                    for (int j = 0; j < 2; j++) {
                        double distFromPoint = sqrt(pow(Mouse::getPosition(window).x-points[i][j].getPosition().x, 2) + pow(Mouse::getPosition(window).y-points[i][j].getPosition().y, 2));
                        if (distFromPoint < points[i][j].getRadius() && distFromPoint < minDistance) {
                            minDistance = distFromPoint;
                            pointIndex = i;
                            pointIndex2 = j;
                        }

                    }
                }
            }
        } else {
            pointIndex = -1;
            pointIndex2 = -1;
            left = false;
        }
        window.clear();
        if (pointIndex != -1) {
            double mx = Mouse::getPosition(window).x;
            double my = Mouse::getPosition(window).y;
            if (left) {
                points[pointIndex][pointIndex2].setPosition(mx, my);
            } else {
                if (pointIndex2 == 0) {
                    diffx = points[pointIndex][1].getPosition().x - points[pointIndex][0].getPosition().x;
                    diffy = points[pointIndex][1].getPosition().y - points[pointIndex][0].getPosition().y;
                    points[pointIndex][1].setPosition(mx + diffx, my + diffy);
                }
                points[pointIndex][pointIndex2].setPosition(mx, my);
            }
        }

        CubicSplinePoint2D splinePoint1(Point2D(points[0][0].getPosition().x, points[0][0].getPosition().y), Point2D(points[0][1].getPosition().x, points[0][1].getPosition().y));
        CubicSplinePoint2D splinePoint2(Point2D(points[1][0].getPosition().x, points[1][0].getPosition().y), Point2D(points[1][1].getPosition().x, points[1][1].getPosition().y));
        vector<CubicSplinePoint2D> splinePoints;
        splinePoints.push_back(splinePoint1);
        splinePoints.push_back(splinePoint2);
        CubicSpline2D spline(splinePoints, false);
        spline.Calculate();

        prevX = spline.Get(0).x;
        prevY = spline.Get(0).y;
        for (double t = tInc; t <= 1; t+=tInc) {
            Point2D p = spline.Get(t);
            newX = p.x;
            newY = p.y;
            window.draw(Line(prevX+2.5, prevY+2.5, newX+2.5, newY+2.5, Color(255, 255, 255)));

            prevX = newX;
            prevY = newY;
        }
        window.draw(Line(prevX+2.5, prevY+2.5, points[1][0].getPosition().x+2.5, points[1][0].getPosition().y+2.5, Color(255, 255, 255)));
        window.draw(PointLine(points[0][0], points[0][1]));
        window.draw(PointLine(points[1][0], points[1][1]));
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                window.draw(points[i][j]);
            }
        }
        window.display();
    }
}

RectangleShape PointLine(CircleShape p1, CircleShape p2) {
    return Line(p1.getPosition().x+2.5, p1.getPosition().y+2.5, p2.getPosition().x+2.5, p2.getPosition().y+2.5, Color(100, 100, 100));
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
