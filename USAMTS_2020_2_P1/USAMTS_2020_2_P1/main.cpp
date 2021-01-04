//
//  main.cpp
//  USAMTS_2020_2_P1
//
//  Created by Michael Schuff on 10/28/20.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n = 0;
struct ret {
    vector<vector<int>> arr;
    bool b;
    ret(vector<vector<int>> _arr, bool _b) : arr(_arr), b(_b) {}
};
bool isLegalBoard(vector<vector<int>> grid) {
    int spots[9][2] = {
        {1, 1},
        {1, 3},
        {1, 5},
        {3, 0},
        {3, 2},
        {3, 4},
        {5, 1},
        {5, 2},
        {5, 4}
    };
    
    int dir[8][2] = {
        {1, 1},
        {1, 0},
        {1, -1},
        {0, -1},
        {-1, -1},
        {-1, 0},
        {-1, 1},
        {0, 1}
    };
    for (int i = 0; i < 9; i++) {
        int x = spots[i][0];
        int y = spots[i][1];
        vector<int> nums;
        int sum = 0;
        bool contains0 = false;
        bool b;
        for (int d = 0; d < 8; d++) {
            b = true;
            int _x = x + dir[d][0];
            int _y = y + dir[d][1];
            for (int j = 0; j < 9; j++) {
                if (_x == spots[j][0] && _y == spots[j][1]) {
                    b = false;
                }
            }
            if (_y >= 0 && _y < grid.size() && b) {
                if (_x >= 0 && _x < grid[_y].size()) {
                    for (int j = 0; j < nums.size(); j++) {
                        if (nums[j] != 0 && nums[j] == grid[_y][_x]){
                            return false;
                        }
                        if (nums[j] == 0) {
                            contains0 = true;
                        }
                    }
                    nums.push_back(grid[_y][_x]);
                    sum += grid[_y][_x];
                }
            }
        }
        if (sum > grid[y][x]) {
            return false;
        }
        if (!contains0) {
            if (sum != grid[y][x]) {
                return false;
            }
        }
    }
    return true;
}
void print(const vector<vector<int>> &grid) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            string s = to_string(grid[i][j]);
            if (s.size() == 1) {
                s += " ";
            }
            cout << s << " ";
        }
        cout << endl;
    }
    cout << endl;
}

vector<vector<int>> copyboard(const vector<vector<int>> &grid) {
    vector<vector<int>> v;
    for (int i = 0; i < grid.size(); i++) {
        v.push_back(vector<int>());
        for (int j = 0; j < grid[i].size(); j++) {
            v[i].push_back(grid[i][j]);
        }
    }
    return v;
}


ret solve(vector<vector<int>> grid, int x, int y) {
    if (y > 2) {
        cout << "hello" << endl;
    }
    
    if (x >= grid[y].size()) {
        y++;
        x = 0;
        if (y >= grid.size()) {
            return ret(grid, isLegalBoard(grid));
        }
    }
    if (grid[y][x] != 0) {
        ret r = solve(grid, x + 1, y);
        if (r.b) {
            return r;
        }
    } else {
        vector<vector<int>> temp = copyboard(grid);
        for (int i = 1; i <= 9; i++) {
            temp[y][x] = i;
            if (temp[3][0]>0) {
                print(temp);
                cout << "\n\n\n" << endl;
            }
            
//            n = (n + 1) % 10000;
            if (isLegalBoard(temp)) {
                ret r = solve(temp, x + 1, y);
                if (r.b) {
                    return r;
                }
            }
        }
    }
    
    
    
    return ret(grid, false);
    
}

int main()
{
    vector<vector<int>> possibles = {
        {28, 35, 36, 38, 40, 42, 44},
        {28, 35, 36, 38, 40, 42, 44},
        {35, 36, 38, 40, 42, 44},
        {35, 36, 38, 40, 42, 44},
        {35, 36, 38, 40, 42, 44},
        {35, 36, 38, 40, 42, 44},
        {35, 36, 38, 40, 42, 44},
    };
    vector<vector<int>> grid = {
        { 0,  5,  0, 15,  0,  8,  0},
        { 4,  0,  0,  0,  0,  0,  0},
        { 0,  3,  0,  0,  0,  0,  1},
        { 0,  0,  0,  0,  0,  7,  0},
        { 0,  8,  0,  0,  1,  0,  4},
        { 0, 23,  0,  0,  0,  2,  0},
    };
    int o = 0;
    for (int a = 0; a < possibles[0].size(); a++) {
        for (int b = 0; b < possibles[1].size(); b++) {
            if (possibles[1][b] != possibles[0][a]) {
                for (int c = 0; c < possibles[2].size(); c++) {
                    if (possibles[2][c] != possibles[1][b] && possibles[2][c] != possibles[0][a]) {
                        for (int d = 0; d < possibles[3].size(); d++) {
                            if (possibles[3][d] != possibles[2][c] && possibles[3][d] != possibles[1][b] && possibles[3][d] != possibles[0][a]) {
                                for (int e = 0; e < possibles[4].size(); e++) {
                                    if (possibles[4][e] != possibles[3][d] && possibles[4][e] != possibles[2][c] && possibles[4][e] != possibles[1][b] && possibles[4][e] != possibles[0][a]) {
                                        for (int f = 0; f < possibles[5].size(); f++) {
                                            if (possibles[5][f] != possibles[4][e] && possibles[5][f] != possibles[3][d] && possibles[5][f] != possibles[2][c] && possibles[5][f] != possibles[1][b] && possibles[5][f] != possibles[0][a]) {
                                                for (int g = 0; g < possibles[6].size(); g++) {
                                                    if (possibles[6][g] != possibles[5][f] && possibles[6][g] != possibles[4][e] && possibles[6][g] != possibles[3][d] && possibles[6][g] != possibles[2][c] && possibles[6][g] != possibles[1][b] && possibles[6][g] != possibles[0][a]) {
                                                        o++;
                                                        vector<vector<int>> temp = copyboard(grid);
                                                        temp[1][5] = possibles[0][a];
                                                        temp[2][5] = possibles[1][b];
                                                        temp[1][1] = possibles[2][c];
                                                        temp[2][3] = possibles[3][d];
                                                        temp[3][1] = possibles[4][e];
                                                        temp[4][3] = possibles[5][f];
                                                        temp[4][5] = possibles[6][g];
                                                        ret r = solve(temp, 0, 0);
                                                        if (r.b) {
                                                            print(r.arr);
                                                        }
                                                        cout << o << endl;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

