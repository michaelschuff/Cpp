#include<iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

int main(){
	RenderWindow window(VideoMode(800,600), "SFML window");
	while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type==Event::Closed){
                window.close();
            }
        }
        window.clear();
		
        window.display();
    }
}
