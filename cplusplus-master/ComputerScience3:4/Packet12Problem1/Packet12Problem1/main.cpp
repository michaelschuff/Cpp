#include<iostream>
#include<SFML/Graphics.hpp>
#include<ResourcePath.hpp>
using namespace std;
using namespace sf;
//lost source file
int main(){
	int frame = 0;
	int row = 0;
	RenderWindow window(VideoMode(86,112.5), "Thriller");
	window.setFramerateLimit(60);
	Texture spriteSheet;
	Sprite playerSprite;
	int frameCounter = 0;
	if(!spriteSheet.loadFromFile(resourcePath()+"Thriller.jpg")){
		cout<<"Image Not Found"<<endl;
	}
	playerSprite.setTexture(spriteSheet);
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		playerSprite.setTextureRect(IntRect(86*frame,112.5*row,86,112.5));
		if(frameCounter == 10){//same code as packet 12 problem 4
			frame = (frame+1)%4;
			frameCounter = 0;
			if(frame == 3){
				row = (row+1)%4;
			}
		}
		frameCounter++;
		window.clear(Color(0,0,0));
		window.draw(playerSprite);
		window.display();
	}
}