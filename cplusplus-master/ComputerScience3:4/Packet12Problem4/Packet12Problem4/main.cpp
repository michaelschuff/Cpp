#include<iostream>
#include<SFML/Graphics.hpp>
#include"ResourcePath.hpp"
//***********************************DISCLAIMER*********************
//acccidently deleted the sprite files, and couldnt be bothered to find them again
using namespace std;
using namespace sf;

int main(){
	int frameCounter=0;
	int frame = 0;
	int row = 0;
	int size=6;
	Texture runSheet;
	Texture idleSheet;
	Sprite Trump;
	if(!idleSheet.loadFromFile(resourcePath()+"trumpidle.png")){
		cout<<"Movement image Not Found"<<endl;
	}
	if(!runSheet.loadFromFile(resourcePath()+"trumprun.png")){
		cout<<"Idle image Not Found"<<endl;
	}
	RenderWindow window(VideoMode(800,800), "My Man DT");
	window.setFramerateLimit(60);
	while(window.isOpen()){
		Event event;
		while(window.pollEvent(event)){
			if(event.type == Event::Closed){
				window.close();
			}
			if(Keyboard::isKeyPressed(Keyboard::Down)||Keyboard::isKeyPressed(Keyboard::S)){//works for wasd and up/down/etc
				Trump.setTexture(runSheet);
				row=0;
				size=6;
			}
			else if(Keyboard::isKeyPressed(Keyboard::Right)||Keyboard::isKeyPressed(Keyboard::D)){
				Trump.setTexture(runSheet);
				row=1;
				size=6;
			}
			else if(Keyboard::isKeyPressed(Keyboard::Up)||Keyboard::isKeyPressed(Keyboard::W)){
				Trump.setTexture(runSheet);
				row=2;
				size=6;
			}
			else if(Keyboard::isKeyPressed(Keyboard::Left)||Keyboard::isKeyPressed(Keyboard::A)){
				Trump.setTexture(runSheet);
				row=3;
				size=6;
			}
			else{
				Trump.setTexture(idleSheet);
				size=10;//different sizes because the sprite sheets come with different amounts of sprites
			}
		}
		frameCounter++;
		if(frameCounter==10){
			frame=(frame+1)%size;//each 10 frame, go to the next sprite, and if it is out of sheets, restart it
			frameCounter=0;
		}
		Trump.setTextureRect(IntRect(frame*256,row*256,256,256));
		window.clear(Color(0,0,0));
		window.draw(Trump);
		window.display();
	}
}