//
//  MathFunctions.cpp
//  SplineGeneration
//
//  Created by Michael Schuff on 3/26/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#include "MathFunctions.hpp"

using namespace std;

namespace MathFunctions {
    double Magnitude(double x, double y) {
        return sqrt(x*x + y*y);
    }

    double Distance(Point2D p1, Point2D p2) {
        return Magnitude(p2.x - p1.x, p2.y - p1.y);
    }

    double Direction(Point2D p1) {
        return atan2(p1.y, p1.x);
    }

    double Magnitude(Point2D p1) {
        return sqrt(p1.x*p1.x + p1.y*p1.y);
    }

    vector<vector<double>> ReducedRowEchelonForm(vector<vector<double>> vect) {
        int columns = vect[0].size();
        int rows = vect.size();
        double leading;
        double head;
        for (int i = 0; i < rows; i++) {
            for (int j = i; j < columns; j++) {
                leading = vect[i][j];
                if (vect[j][i] != 0) {
                    for (int k = 0; k < columns; k++) {
                        vect[j][k] /= leading;
                    }
                    for (int l = 0; l < rows; l++) {
                        head = vect[l][j];
                        if (l != i) {
                            for (int k = 0; k < columns; k++) {
                                vect[l][k] -= head * vect[i][k];
                            }
                        }
                    }
//                    if (i < vect.size()){
//                        swap(vect[j], vect[i]);
//                    }
                    break;
                }
            }
        }
        
        return vect;
    }

    void ReducedRowEchelonForm(double arr[4][5]) {
        int rows = 4;
        int columns = 5;
        double leading;
        double head;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                leading = arr[i][j];
                if (leading != 0) {
                    for (int k = j; k < columns; k++) {
                        arr[i][k] /= leading;
                    }
                    for (int k = 0; k < rows; k++) {
                        if (k != i) {
                            for (int l = 0; l < columns; l++) {
                                arr[k][l] -= arr[k][j]*arr[i][l];
                            }
                        }
                    }
//                    if (j < rows) {
//                        swap(arr[i], arr[j]);
//                    }
                    break;
                }
            }
        }
    }

    template<typename T>
    vector<T> slice(vector<T> &v, int m, int n)
    {
        vector<T> vec(n - m + 1);
        copy(v.begin() + m, v.begin() + n + 1, vec.begin());
        return vec;
    }
}

