//
//  MathFunctions.hpp
//  SplineGeneration2.0
//
//  Created by Michael Schuff on 4/9/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#ifndef MathFunctions_hpp
#define MathFunctions_hpp

#include <stdio.h>
#include <vector>
#include "Vector2D.hpp"

using namespace std;

namespace MathFunctions {
    enum Directions {up, down, right, left};
    vector<vector<double>> ReducedRowEchelonForm(vector<vector<double>>);
    vector<double> RREFOutput(vector<vector<double>>);
};

#endif /* MathFunctions_hpp */
