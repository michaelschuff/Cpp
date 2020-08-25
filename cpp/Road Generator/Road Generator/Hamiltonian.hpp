//
//  Hamiltonian.hpp
//  Road Generator
//
//  Created by Michael Schuff on 6/3/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#ifndef Hamiltonian_hpp
#define Hamiltonian_hpp

#include <stdio.h>
#include "Vector2D.hpp"
#include <vector>
#include <algorithm>

using namespace std;

namespace Hamiltonian {
    vector<vector<Vector2D>> ManhattanCycle(int, int);
    vector<vector<Vector2D>> ManhattanCycleDiagonal(int, int);
};

#endif /* Hamiltonian_hpp */

