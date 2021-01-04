#include <SFML/Graphics/Image.hpp>
#include "ResourcePath.hpp"
#include <iostream>
#include <chrono>
#include <thread>

using namespace sf;
using namespace std;
using namespace std::chrono;


int main(int, char const**) {
    Image img;
    if (!img.loadFromFile(resourcePath() + "img.png")) {
        img.create(1280, 720, Color(0, 0, 0));
    }
    
//        if (!img.saveToFile(resourcePath() + "img.png")) {
//            return EXIT_FAILURE;
//        }
    
    steady_clock::time_point start, start1;
    steady_clock::time_point end, end1;
    steady_clock::time_point temp;
    int elapsed = 0;
    while (true) {
//        start1 = steady_clock::now();
        start = steady_clock::now();
        
        
        
        
        
        //do stuff
        
        
        
        
        
        end = steady_clock::now();
        this_thread::sleep_for(nanoseconds(1000000000 / 30 - duration_cast<nanoseconds>(end - start).count()));
//        end1 = steady_clock::now();
//        cout << (double) 1000000000 / duration_cast<nanoseconds>(end1 - start1).count() << endl;
    }
    
    return EXIT_SUCCESS;
}
