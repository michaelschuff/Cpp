//
//  main.cpp
//  USAMTS_P1_2020
//
//  Created by Michael Schuff on 10/26/20.
//

#include <iostream>

using namespace std;

#define N 8
int pairs[9][2][2] = {{{0, 1},{1, 2}},
                   {{0, 5},{1, 4}},
                   {{2, 0},{3, 1}},
                   {{1, 7},{2, 6}},
                   {{3, 3},{4, 4}},
                   {{4, 6},{5, 7}},
                   {{6, 0},{5, 1}},
                   {{6, 3},{7, 2}},
                   {{6, 5},{7, 6}}
};

void print(int arr[N][N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << arr[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}
bool isSafe(int grid[N][N], int row,
                       int col, int num)
{
    for (int x = 0; x < N; x++){
        if (grid[row][x] == num){
            return false;
            
        }
        if (grid[x][col] == num){
            return false;
            
        }
        
    }
  
    
    for (int i = 0; i < 9; i++) {
        if (row == pairs[i][0][0] && col == pairs[i][0][1]) {
            for (int x = 0; x < N; x++) {
                if (grid[x][pairs[i][1][1]] == num){
                    return false;
                }
                if (grid[pairs[i][1][0]][x] == num){
                    return false;
                }
            }
        }

        if (row == pairs[i][1][0] && col == pairs[i][1][1]) {
            
            for (int x = 0; x < N; x++) {
                if (grid[x][pairs[i][0][1]] == num){
                    return false;
                }
                if (grid[pairs[i][0][0]][x] == num){
                    return false;
                }
            }
        }
    }
    
    
  
    return true;
}
  
bool solveSuduko(int grid[N][N], int row, int col)
{
    if (row == N - 1 && col == N)
        return true;
  
    if (col == N) {
        row++;
        col = 0;
    }
    
    if (grid[row][col] > 0)
        return solveSuduko(grid, row, col + 1);
  
    for (int num = 1; num <= N; num++)
    {
        if (isSafe(grid, row, col, num))
        {
            grid[row][col] = num;
            for (int i = 0; i < 9; i++) {
                if (row == pairs[i][0][0] && col == pairs[i][0][1]) {
                    grid[pairs[i][1][0]][pairs[i][1][1]] = num;
                }
                if (row == pairs[i][1][0] && col == pairs[i][1][1]) {
                    grid[pairs[i][0][0]][pairs[i][0][1]] = num;
                }
            }
            if (solveSuduko(grid, row, col + 1)) {
                return true;
            }
        }
        grid[row][col] = 0;
        for (int i = 0; i < 9; i++) {
            if (row == pairs[i][0][0] && col == pairs[i][0][1]) {
                grid[pairs[i][1][0]][pairs[i][1][1]] = 0;
            }
            if (row == pairs[i][1][0] && col == pairs[i][1][1]) {
                grid[pairs[i][0][0]][pairs[i][0][1]] = 0;
            }
        }
    }
    return false;
}
  
int main()
{
    int grid[N][N] = { { 1, 0, 0, 0, 0, 0, 0, 0},
                       { 2, 3, 0, 0, 0, 0, 0, 0},
                       { 0, 4, 5, 0, 0, 0, 0, 0},
                       { 0, 0, 6, 0, 1, 0, 0, 0},
                       { 0, 0, 0, 7, 0, 1, 0, 0},
                       { 0, 0, 0, 0, 0, 3, 4, 0},
                       { 0, 0, 0, 0, 0, 0, 2, 8},
                       { 0, 0, 0, 0, 0, 0, 0, 5}};
    if (solveSuduko(grid, 0, 0))
        print(grid);
    else
        cout << "no solution  exists " << endl;
  
}
