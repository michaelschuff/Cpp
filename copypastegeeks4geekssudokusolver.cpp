#include <iostream>

using namespace std; 
  
// N is the size of the 2D matrix   N*N 
#define N 8 
  
/* A utility function to print grid */
void print(int arr[N][N], int row, int col) 
{ 
    for (int i = 0; i < N; i++) { 
        for (int j = 0; j < N; j++) 
            if (i == row && j == col) {
                cout << arr[i][j] << "*"; 
            } else {

                cout << arr[i][j] << " "; 
            }
        cout << endl; 
    } 
    cout << endl;
} 
  
// Checks whether it will be  
// legal to assign num to the 
// given row, col 
bool isSafe(int grid[N][N], int row,  
                       int col, int num) 
{ 
      
    // if we find the same num  
    // in the similar row , we 
    // return false 
    for (int x = 0; x < N; x++) 
        if (grid[row][x] == num) 
            return false; 
  
    // if we find the same num in  
    // the similar column , we 
    // return false 
    for (int x = 0; x < N; x++) 
        if (grid[x][col] == num) 
            return false; 
  
    // if we find the same num in  
    // the particular 3*3 matrix, 
    // we return false 
    // int startRow = row - row % 3,  
    //         startCol = col - col % 3; 
    
    // for (int i = 0; i < 3; i++) 
    //     for (int j = 0; j < 3; j++) 
    //         if (grid[i + startRow][j +  
    //                         startCol] == num) 
    //             return false; 
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
    for (int i = 0; i < 9; i++) {
        if (row == pairs[i][0][0] && col == pairs[i][0][1] && grid[pairs[i][1][1]][pairs[i][1][0]] != num) {
            int tempgrid[N][N];
            for (int y = 0; y < N; y++) {
                for (int x = 0; x < N; x++) {
                    tempgrid[y][x] = grid[y][x];
                }
            }
            tempgrid[row][col] = num;
            if (!isSafe(tempgrid, pairs[i][1][0], pairs[i][1][1], num)) {
                return false;
            }
        }

        if (row == pairs[i][1][0] && col == pairs[i][1][1] && grid[pairs[i][0][1]][pairs[i][0][0]] != num) {
            int tempgrid[N][N];
            for (int y = 0; y < N; y++) {
                for (int x = 0; x < N; x++) {
                    tempgrid[y][x] = grid[y][x];
                }
            }
            tempgrid[row][col] = num;
            if (!isSafe(tempgrid, pairs[i][0][0], pairs[i][0][1], num)) {
                return false;
            }
        }
    }
  
    return true; 
} 
  
/* Takes a partially filled-in grid and attempts 
to assign values to all unassigned locations in 
such a way to meet the requirements for 
Sudoku solution (non-duplication across rows, 
columns, and boxes) */
bool solveSuduko(int grid[N][N], int row, int col) 
{ 
    // Check if we have reached the 8th  
    // row and 9th column (0 
    // indexed matrix) , we are  
    // returning true to avoid 
    // further backtracking 
    if (row == N - 1 && col == N) 
        return true; 
  
    // Check if column value  becomes 9 ,  
    // we move to next row and 
    //  column start from 0 
    if (col == N) { 
        row++; 
        col = 0; 
    } 
    
    // Check if the current position of  
    // the grid already contains 
    // value >0, we iterate for next column 
    if (grid[row][col] > 0) 
        return solveSuduko(grid, row, col + 1); 
  
    for (int num = 1; num <= N; num++)  
    { 
        print(grid, row, col);
        cout << "num: " << num << endl;
        if (isSafe(grid, row, col, num))  
        { 
            grid[row][col] = num;
            if (solveSuduko(grid, row, col + 1)) {
                return true; 
            }
        }
        grid[row][col] = 0; 
    } 
    return false; 
} 
  
// Driver Code 
int main() 
{ 
    // 0 means unassigned cells 
    int grid[N][N] = { { 1, 0, 0, 0, 0, 0, 0, 0}, 
                       { 2, 3, 0, 0, 0, 0, 0, 0}, 
                       { 0, 4, 5, 0, 0, 0, 0, 0}, 
                       { 0, 0, 6, 0, 1, 0, 0, 0}, 
                       { 0, 0, 0, 7, 0, 1, 0, 0}, 
                       { 0, 0, 0, 0, 0, 3, 4, 0}, 
                       { 0, 0, 0, 0, 0, 0, 2, 8}, 
                       { 0, 0, 0, 0, 0, 0, 0, 5}}; 
  
    if (solveSuduko(grid, 0, 0)) 
        print(grid,0, 0); 
    else
        cout << "no solution  exists " << endl; 
  
    return 0; 
    // This is code is contributed by Pradeep Mondal P 
}