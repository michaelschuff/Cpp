//
//  main.cpp
//  HamiltonianCycle
//
//  Created by Michael Schuff on 4/10/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Vector2D.hpp"
#include "Hamiltonian.hpp"
#include "CustomMath.hpp"
#include <unistd.h>

using namespace std;
using namespace sf;

double degrees(double);
RectangleShape Line(double, double, double, double, Color);

int main() {
    float width = 800, height = 800, rows = 5, columns = 5;
    double pxPerRow = (double) height / rows, pxPerColumns = (double) height / columns;
    vector<vector<Vector2D>> path = Hamiltonian::ManhattanCycleDiagonal(rows, columns);
    vector<RectangleShape> walls, nextWalls;
    for (int i = 0; i < path.size(); i++) {
        for (int j = 0; j < path[i].size(); j++) {
            walls.push_back(Line(((float) j + 0.5) * pxPerColumns, ((float) i + 0.5) * pxPerRow, ((float) j + 0.5 - path[i][j].x) * pxPerColumns, ((float) i + 0.5 - path[i][j].y) * pxPerRow, Color(255, 255, 255)));
        }
        cout << endl;
    }
    cout << endl;
    nextWalls = vector<RectangleShape>();
    nextWalls = walls;
    RenderWindow window(VideoMode(width, height), "Hamiltonian Cycles");
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            } else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
               window.close();
            } else if (event.type == Event::KeyPressed) {
                switch (event.key.code) {
                    case Keyboard::Up:
                        rows++;
                        break;
                    case Keyboard::W:
                        rows++;
                        break;
                    case Keyboard::Down:
                        rows--;
                        break;
                    case Keyboard::S:
                        rows--;
                        break;
                    case Keyboard::Right:
                        columns++;
                        break;
                    case Keyboard::D:
                        columns++;
                        break;
                    case Keyboard::Left:
                        columns--;
                        break;
                    case Keyboard::A:
                        columns--;
                        break;
                    default:
                        break;
                }
                pxPerRow = (double) height / rows;
                pxPerColumns = (double) height / columns;
                path = Hamiltonian::ManhattanCycleDiagonal(rows, columns);
                nextWalls = vector<RectangleShape>();
                for (int i = 0; i < path.size(); i++) {
                    for (int j = 0; j < path[i].size(); j++) {
                        nextWalls.push_back(Line(((float) j + 0.5) * pxPerColumns, ((float) i + 0.5) * pxPerRow, ((float) j + 0.5 - path[i][j].x) * pxPerColumns, ((float) i + 0.5 - path[i][j].y) * pxPerRow, Color(255, 255, 255)));
                    }
                    cout << endl;
                }
                cout << endl;
            } else if (event.type == Event::KeyReleased) {
                walls = vector<RectangleShape>();
                walls = nextWalls;
            }

        }
        window.clear();
        for (int i = 0; i < walls.size(); i++) {
            window.draw(walls[i]);
            CircleShape c(5);
            c.setFillColor(Color(255,255,255));
            c.setPosition(walls[i].getPosition().x - 5, walls[i].getPosition().y - 5);
            window.draw(c);
        }
        window.display();
    }
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

double degrees(double rad) {
    return rad * 180 / 3.1415626535;
}
