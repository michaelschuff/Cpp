#include <iostream>


using namespace std;

void ReducedRowEchelonForm(double, int, int);
void print(double, int, int);

int main() {
    double M[3][4] = { {  1, 2, -1,  -4 },
                     {  2, 3, -1, -11 },
                     { -2, 0, -3,  22 } };
    ReducedRowEchelonForm(M, 3, 4);
    print(M, 3, 4);
}


void ReducedRowEchelonForm(double **vect, int rows, int columns) {
    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            if (vect[j][i] != 0) {
                for (int k = i; k < columns; k++) {
                    vect[j][k] /= vect[j][i];
                }
                for (int l = 0; l < rows; l++) {
                    if (l != j) {
                        double pivot = vect[l][i];
                        for (int m = 0; m < columns; m++) {
                            vect[l][m] -= vect[j][m] * pivot;
                        }
                    }
                }
                swap(vect[j], vect[i]);
                break;
            }
        }
    }
    // return vect;
}

void print(double **v, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << v[i][j];
            if (j != rows - 1) {
                cout << "\t";
            } else {
                cout << endl;
            }
        }
    }
}