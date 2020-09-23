//
//  Camera.hpp
//  2D Visual Hull
//
//  Created by Michael Schuff on 9/23/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>
#include "Vector2D.hpp"
#include "Spline2D.hpp"

class Camera : public Vector2D {
public:
    vector<Vector2D> rays;
    
    Camera(int, int);
    void GetRays(Spline2D&, double);
    bool intersection(double, double, double, double, double, double, double, double);
    
};

#endif /* Camera_hpp */
