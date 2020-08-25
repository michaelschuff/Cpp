//
//  Hamiltonian.cpp
//  Hamiltonian
//
//  Created by Michael Schuff on 4/10/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#include "Hamiltonian.hpp"

namespace Hamiltonian {
    vector<vector<Vector2D>> ManhattanCycle(int rows, int columns) {
        srand(time(NULL));
        Vector2D none(0, 0);
        if (rows%2 == 1 && columns % 2 == 1) {
            return vector<vector<Vector2D>>();
        }
        Vector2D start(0, 0);
        vector<vector<bool>> visited;
        vector<vector<Vector2D>> path;
        vector<Vector2D> orderedDirections = {
            Vector2D((int) 1, (int) 0),
            Vector2D((int) 0, (int) 1),
            Vector2D((int) -1, (int) 0),
            Vector2D((int) 0, (int) -1)
        };
        
        
        for (int i = 0; i < rows; i++) {
            visited.push_back(vector<bool>());
            path.push_back(vector<Vector2D>());
            for (int j = 0; j < columns; j++) {
                visited[i].push_back(false);
                path[i].push_back(none);
            }
        }
        
        auto visitedAll = [&] () {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    if (!visited[i][j]) {
                        return false;
                    }
                }
            }
            return true;
        };
        
        auto withinBounds = [&] (Vector2D pos) {
            return 0 <= pos.x && 0 <= pos.y && pos.x < columns && pos.y < rows;
        };
        
        function<bool(vector<vector<Vector2D>>)> multipleIslands;
        multipleIslands = [&rows, &columns, &orderedDirections, &withinBounds, &none] (vector<vector<Vector2D>> path) -> bool {
            vector<vector<bool>> counted;
            for (int i = 0; i < rows; i++) {
                counted.push_back(vector<bool>());
                for (int j = 0; j < columns; j++) {
                    counted[i].push_back(false);
                }
            }
            int numOfIslands = 0;
            
            function<void(Vector2D)> fillIsland;
            fillIsland = [&] (Vector2D pos) {
                for (int i = 0; i < orderedDirections.size(); i++) {
                    Vector2D next = pos+orderedDirections[i];
                    if (withinBounds(next)) {
                        if (path[next.y][next.x] == none) {
                            if (!counted[next.y][next.x]) {
                                counted[next.y][next.x] = true;
                                fillIsland(next);
                            }
                        }
                    }
                }
            };
            
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    if (path[i][j] == none) {
                        if (!counted[i][j]) {
                            counted[i][j] = true;
                            numOfIslands++;
                            if (numOfIslands > 1) {
                                return true;
                            }
                            fillIsland(Vector2D(j, i));
                        }
                    }
                }
            }
            return false;
        };
        
        function<bool(Vector2D)> recurse;
        recurse = [&visited, &withinBounds, &start, &visitedAll, &recurse, &orderedDirections, &path, &multipleIslands, &none] (Vector2D pos) {
            vector<Vector2D> dir = {
                Vector2D(1, 0),
                Vector2D(0, 1),
                Vector2D(-1, 0),
                Vector2D(0, -1)
            };
            for (int i = 0; i < 5; i++) {
                int a = rand() % 4;
                swap(dir[i % 4], dir[a]);
            }
            for (int i = 0; i < dir.size(); i++) {
                Vector2D next(pos.x + dir[i].x, pos.y + dir[i].y);
                if (withinBounds(next) && !visited[next.y][next.x]) {
                    path[next.y][next.x] = dir[i];
                    visited[next.y][next.x] = true;
                    if (!multipleIslands(path)) {
                        if (next == start) {
                            if (visitedAll()) {
                                return true;
                            }
                        } else {
                            if (recurse(next)) {
                                return true;
                            }
                        }
                    }
                    path[next.y][next.x] = none;
                    visited[next.y][next.x] = false;
                }
            }
            return false;
        };
        
        bool exists = recurse(start);
        return path;
    }

    vector<vector<Vector2D>> ManhattanCycleDiagonal(int rows, int columns) {
        srand(time(NULL));
        Vector2D none(0, 0);
        Vector2D start(0, 0);
        vector<vector<bool>> visited;
        vector<vector<Vector2D>> path;
        vector<Vector2D> orderedDirections = {
                Vector2D(1, 0),
                Vector2D(1, 1),
                Vector2D(0, 1),
                Vector2D(-1, 1),
                Vector2D(-1, 0),
                Vector2D(-1, -1),
                Vector2D(0, -1),
                Vector2D(1, -1)
        };
        
        
        for (int i = 0; i < rows; i++) {
            visited.push_back(vector<bool>());
            path.push_back(vector<Vector2D>());
            for (int j = 0; j < columns; j++) {
                visited[i].push_back(false);
                path[i].push_back(none);
            }
        }
        
        auto visitedAll = [&] () {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    if (!visited[i][j]) {
                        return false;
                    }
                }
            }
            return true;
        };
        
        auto withinBounds = [&] (Vector2D pos) {
            return 0 <= pos.x && 0 <= pos.y && pos.x < columns && pos.y < rows;
        };
        
        function<bool(vector<vector<Vector2D>>)> multipleIslands;
        multipleIslands = [&rows, &columns, &orderedDirections, &withinBounds, &none] (vector<vector<Vector2D>> path) -> bool {
            vector<vector<bool>> counted;
            for (int i = 0; i < rows; i++) {
                counted.push_back(vector<bool>());
                for (int j = 0; j < columns; j++) {
                    counted[i].push_back(false);
                }
            }
            int numOfIslands = 0;
            
            function<void(Vector2D)> fillIsland;
            fillIsland = [&] (Vector2D pos) {
                for (int i = 0; i < orderedDirections.size(); i++) {
                    Vector2D next = pos+orderedDirections[i];
                    if (withinBounds(next)) {
                        if (path[next.y][next.x] == none) {
                            if (!counted[next.y][next.x]) {
                                counted[next.y][next.x] = true;
                                fillIsland(next);
                            }
                        }
                    }
                }
            };
            
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    if (path[i][j] == none) {
                        if (!counted[i][j]) {
                            counted[i][j] = true;
                            numOfIslands++;
                            if (numOfIslands > 1) {
                                return true;
                            }
                            fillIsland(Vector2D(j, i));
                        }
                    }
                }
            }
            return false;
        };
        
        function<bool(Vector2D)> recurse;
        recurse = [&visited, &withinBounds, &start, &visitedAll, &recurse, &orderedDirections, &path, &multipleIslands, &none] (Vector2D pos) {
            vector<Vector2D> dir = {
                Vector2D(1, 0),
                Vector2D(1, 1),
                Vector2D(0, 1),
                Vector2D(-1, 1),
                Vector2D(-1, 0),
                Vector2D(-1, -1),
                Vector2D(0, -1),
                Vector2D(1, -1)
            };
            for (int i = 0; i < 16; i++) {
                int a = rand() % 8;
                swap(dir[i % 8], dir[a]);
            }
            for (int i = 0; i < dir.size(); i++) {
                bool a = true;
                if (dir[i].x != 0 && dir[i].y != 0) {
                    if (withinBounds(pos+dir[i])) {
                        Vector2D left((int) pos.x, (int) (pos.y+dir[i].y));
                        Vector2D right((int) (pos.x+dir[i].x), (int) pos.y);
                        Vector2D l((int) (left.x - path[left.y][left.x].x), (int) (left.y - path[left.y][left.x].y));
                        Vector2D r((int) (right.x - path[right.y][right.x].x), (int) (right.y - path[right.y][right.x].y));
                        if (l==right||r==left) {
                            a = false;
                        }
//                        if ((int)pos.x==(int)(right.x + path[right.y][right.x].x)&&(int)(pos.y+dir[i].y)==(int)(right.y + path[right.y][right.x].y)) {
//                            a = false;
//                        } else if ((int)(pos.x+dir[i].x)==(int)(left.x + path[left.y][left.x].x)&&(int)pos.y==(int)(left.y + path[left.y][left.x].y)) {
//                            a = false;
//                        }
                    }
                }
                if (a) {
                    Vector2D next(pos.x + dir[i].x, pos.y + dir[i].y);
                    if (withinBounds(next) && !visited[next.y][next.x]) {
                        path[next.y][next.x] = dir[i];
                        visited[next.y][next.x] = true;
                        if (!multipleIslands(path)) {
                            if (next == start) {
                                if (visitedAll()) {
                                    return true;
                                }
                            } else {
                                if (recurse(next)) {
                                    return true;
                                }
                            }
                        }
                        path[next.y][next.x] = none;
                        visited[next.y][next.x] = false;
                    }
                }
            }
            return false;
        };
        
        bool exists = recurse(start);
        return path;
    }
}
