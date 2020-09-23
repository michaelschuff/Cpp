#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "vector2.hpp"
#include <iostream>

using namespace sf;
using namespace std;

int main() {
    RenderWindow window(VideoMode(800, 600), "2D Visual Hull");

    
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                window.close();
            }
        }

        window.clear();

        window.display();
    }

    return EXIT_SUCCESS;
}
