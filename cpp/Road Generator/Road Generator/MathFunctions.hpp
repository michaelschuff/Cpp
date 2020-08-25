//
//  MathFunctions.hpp
//  Road Generator
//
//  Created by Michael Schuff on 6/3/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#ifndef MathFunctions_hpp
#define MathFunctions_hpp

#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <cmath>
#include "Vector2D.hpp"

using namespace std;

namespace MathFunctions {
enum Directions {up, down, right, left};
vector<vector<double>> ReducedRowEchelonForm(vector<vector<double>>);
vector<double> RREFOutput(vector<vector<double>>);
double RandomRange(double, double);
int RandomRange(int, int);
};

#endif /* MathFunctions_hpp */
