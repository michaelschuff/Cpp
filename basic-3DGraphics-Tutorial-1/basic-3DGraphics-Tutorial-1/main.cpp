#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <time.h>

using namespace std;
using namespace sf;


struct vector3;
struct quaternion;

vector3 operator+(vector3 v1, vector3 v2);
vector3 operator-(vector3 v1, vector3 v2);
vector3 operator/(vector3 v, double k);
vector3 operator*(vector3 v, quaternion q);
vector3 cross(vector3, vector3);
double dot(vector3 v1, vector3 v2);
quaternion get_quaternion(vector3 v1, vector3 v2);
quaternion get_quaternion(vector3 v1, double k);
quaternion operator*(quaternion q1, quaternion q2);

struct vector3 {
    double x, y, z;
    vector3() : x(0), y(0), z(0) {}
    vector3(double tx, double ty, double tz) : x(tx), y(ty), z(tz) {}
    vector3 operator*(double k) { return vector3(k*x, k*y, k*z); }
    double mag() { return sqrt(x*x + y*y + z*z); }
    vector3 normalized() { return *this/mag(); }
    void normalize() { *this = *this/mag(); }
};
struct quaternion {
    double w, x, y, z;
    quaternion() : w(1), x(0), y(0), z(0) {}
    
    quaternion(double tw, double tx, double ty, double tz) : w(tw), x(tx), y(ty), z(tz) {}
    
    quaternion normalized() {
        double m = sqrt(w*w + x*x + y*y + z*z);
        if (m!=0) {
            return quaternion(w/m, x/m, y/m, z/m);
        }
        return *this;
    }
};

class cam {
public:
    vector3 position = vector3(0, 0, 0);
    vector3 forward = vector3(0, 0, 1);
    vector3 up = vector3(0, 1, 0);
    vector3 right = vector3(1, 0, 0);
    
    float fov = 60 *3.14159 / 180;
    
    cam& operator*=(quaternion q) {
        forward = forward * q;
        up = up * q;
        right = right * q;
        return *this;
    }
    
    vector<quaternion> get_reverse_orientation() {
        quaternion forward_to_z = get_quaternion(forward, vector3(0, 0, 1));
        quaternion up_to_y = get_quaternion(up*forward_to_z, vector3(0, 1, 0));
        return {forward_to_z, up_to_y};
    }
};

int main() {
    srand(time(NULL));
    int W = 800,
        H = 600;
    float d2r = 3.14159 / 180;
    
    vector3 tris[36] = {
        vector3(0,0,1), vector3(1,0,1), vector3(1,1,1),
        vector3(0,0,1), vector3(1,1,1), vector3(0,1,1),
        vector3(1,0,1), vector3(1,0,0), vector3(1,1,0),
        vector3(1,0,1), vector3(1,1,0), vector3(1,1,1),
        vector3(1,0,0), vector3(0,0,0), vector3(0,1,0),
        vector3(1,0,0), vector3(0,1,0), vector3(1,1,0),
        vector3(0,0,0), vector3(0,0,1), vector3(0,1,1),
        vector3(0,0,0), vector3(0,1,1), vector3(0,1,0),
        vector3(0,1,1), vector3(1,1,1), vector3(1,1,0),
        vector3(0,1,1), vector3(1,1,0), vector3(0,1,0),
        vector3(1,0,1), vector3(0,0,0), vector3(1,0,0),
        vector3(1,0,1), vector3(0,0,1), vector3(0,0,0)
    };
    Color cols[12] = {
        Color(rand()%255,rand()%255,rand()%255),
        Color(rand()%255,rand()%255,rand()%255),
        Color(rand()%255,rand()%255,rand()%255),
        Color(rand()%255,rand()%255,rand()%255),
        Color(rand()%255,rand()%255,rand()%255),
        Color(rand()%255,rand()%255,rand()%255),
        Color(rand()%255,rand()%255,rand()%255),
        Color(rand()%255,rand()%255,rand()%255),
        Color(rand()%255,rand()%255,rand()%255),
        Color(rand()%255,rand()%255,rand()%255),
        Color(rand()%255,rand()%255,rand()%255),
        Color(rand()%255,rand()%255,rand()%255)
    };
    
    cam c;
    
    
    RenderWindow window(VideoMode(W, H), "3D Graphics");
    window.setFramerateLimit(60);
    
    
    bool w = false,
         a = false,
         s = false,
         d = false,
         shift = false,
         space = false,
         active = false;
    
    
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            } else if (event.type == Event::KeyPressed) {
                switch (event.key.code) {
                    case Keyboard::W:
                        w = true;
                        break;
                    case Keyboard::A:
                        a = true;
                        break;
                    case Keyboard::S:
                        s = true;
                        break;
                    case Keyboard::D:
                        d = true;
                        break;
                    case Keyboard::LShift:
                        shift = true;
                        break;
                    case Keyboard::Space:
                        space = true;
                        break;
                    case Keyboard::Escape:
                        active = !active;
                        break;
                }
            } else if (event.type == Event::KeyReleased) {
                switch (event.key.code) {
                    case Keyboard::W:
                        w = false;
                        break;
                    case Keyboard::A:
                        a = false;
                        break;
                    case Keyboard::S:
                        s = false;
                        break;
                    case Keyboard::D:
                        d = false;
                        break;
                    case Keyboard::LShift:
                        shift = false;
                        break;
                    case Keyboard::Space:
                        space = false;
                        break;
                }
            }
        }
        
        
        if (active) {
            if (w) {
                c.position = c.position + c.forward / 60.0;
            } if (s) {
                c.position = c.position - c.forward / 60.0;
            } if (a) {
                c.position = c.position - c.right / 60.0;
            } if (d) {
                c.position = c.position + c.right / 60.0;
            } if (shift) {
                c.position = c.position + c.up / 60.0;
            } if (space) {
                c.position = c.position - c.up / 60.0;
            }
            
            Vector2i mp = Mouse::getPosition(window);
            
            if (mp.x != W/2) {
                c *= get_quaternion(vector3(0, 1, 0), 0.1 * (mp.x - W/2) * d2r);
            }
            
            if (mp.y != H/2) {
                c *= get_quaternion(c.right, 0.1 * -(mp.y - H/2) * d2r);
            }
            
            Mouse::setPosition(Vector2i(W/2, H/2), window);
        }
        
        
        window.clear();
        vector<quaternion> reverse_cam = c.get_reverse_orientation();
        
        for (int i = 0; i < 12; i++) {
            vector3 P = (tris[3*i + 0] - c.position) * reverse_cam[0] * reverse_cam[1];
            vector3 Q = (tris[3*i + 1] - c.position) * reverse_cam[0] * reverse_cam[1];
            vector3 R = (tris[3*i + 2] - c.position) * reverse_cam[0] * reverse_cam[1];
            
            P.x = W/2 * P.x/(P.z * tan(c.fov/2));
            P.y = H/2 * P.y/(P.z * tan(c.fov/2 * (float) H/W));
            
            Q.x = W/2 * Q.x/(Q.z * tan(c.fov/2));
            Q.y = H/2 * Q.y/(Q.z * tan(c.fov/2 * (float) H/W));
            
            R.x = W/2 * R.x/(R.z * tan(c.fov/2));
            R.y = H/2 * R.y/(R.z * tan(c.fov/2 * (float) H/W));
            
            vector3 normal = cross(Q-P, R-P);
            
            if (normal.z<0) {
                ConvexShape shape(3);
                shape.setPoint(0, Vector2f(W/2 + P.x, H/2 + P.y));
                shape.setPoint(1, Vector2f(W/2 + Q.x, H/2 + Q.y));
                shape.setPoint(2, Vector2f(W/2 + R.x, H/2 + R.y));
                
                shape.setFillColor(cols[i]);
                
                window.draw(shape);
            }
            
        }
        
        window.display();
    }

    return EXIT_SUCCESS;
}

vector3 operator+(vector3 v1, vector3 v2) {
    return vector3(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z);
}
vector3 operator-(vector3 v1, vector3 v2) {
    return vector3(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z);
}
vector3 operator/(vector3 v, double k) {
    return v * (1/k);
}
double dot(vector3 v1, vector3 v2) {
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}
vector3 cross(vector3 v1, vector3 v2) {
    return vector3(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
}
vector3 operator*(vector3 v, quaternion q) {
    quaternion q1((q * quaternion(0, v.x, v.y, v.z)) * quaternion(q.w, -q.x, -q.y, -q.z));
    /*q_1 v_1 q_1^\prime= 0+x_3(-w_1w_1 + x_1x_1 - y_1y_1 - z_1z_1)i + \\
                             y_3(-w_1w_1 - x_1x_1 + y_1y_1 - z_1z_1)j + \\
                             z_3(-w_1w_1 - x_1x_1 - y_1y_1 + z_1z_1)k\\
     */
    return vector3(q1.x, q1.y, q1.z);
}
quaternion get_quaternion(vector3 v1, vector3 v2) {
    vector3 v(cross(v1, v2));
    quaternion q = quaternion(v1.mag()*v2.mag() + dot(v1, v2), v.x, v.y, v.z);
    return q;
}
quaternion get_quaternion(vector3 axis, double theta) {
    vector3 v = axis.normalized() * sin(theta/2);
    return quaternion(cos(theta/2), v.x, v.y, v.z);
}
quaternion operator*(quaternion q1, quaternion q2) {
    return quaternion(q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z,
                      q1.w*q2.x + q1.x*q2.w + q1.y*q2.z - q1.z*q2.y,
                      q1.w*q2.y - q1.x*q2.z + q1.y*q2.w + q1.z*q2.x,
                      q1.w*q2.z + q1.x*q2.y - q1.y*q2.x + q1.z*q2.w);
}
