//
//  CustomMath.hpp
//  HamiltonianCycle
//
//  Created by Michael Schuff on 4/10/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#ifndef CustomMath_hpp
#define CustomMath_hpp

#include <stdio.h>
#include <vector>
#include "Vector2D.hpp"

using namespace std;

namespace CustomMath {
    vector<vector<double>> ReducedRowEchelonForm(vector<vector<double>>);
    vector<double> RREFOutput(vector<vector<double>>);
};

#endif /* CustomMath_hpp */
