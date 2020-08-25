#include<iostream>
#include<SFML/Graphics.hpp>
#include<ResourcePath.hpp>

using namespace std;
using namespace sf;

class Button{
public:
	bool activated;
	Texture on;
	Texture off;
	Sprite button;
	Font buttonFont;
	Text buttonText;
	Button(string onpath, string offpath, string fontpath, string textInput, int textSize);
	void setTextPos(int textxpos, int textypos);
	void setButtonText(string newtext);
	void setButtonFont(string newfontpath);
	void updateSprite();
	void resizeButton(int width, int height);
	void moveButton(int buttonxpos,int buttonypos);
};

Button::Button(string onpath, string offpath, string fontpath, string textInput, int textSize){
	activated = false;
	if(!on.loadFromFile(onpath)){
		cout<<"On not working"<<endl;
	}
	if(!off.loadFromFile(offpath)){
		cout<<"Off not working"<<endl;
	}
	button.setTexture(off);
	if(!buttonFont.loadFromFile(fontpath)){
		cout<<"Font path not working"<<endl;
	}
	buttonText.setString(textInput);
	buttonText.setFont(buttonFont);
	buttonText.setCharacterSize(textSize);
}

void Button::setTextPos(int textxpos, int textypos){
	buttonText.setPosition(textxpos,textypos);
}

void Button::setButtonText(string newtext){
	buttonText.setString(newtext);
}

void Button::setButtonFont(string newfontpath){
	if(!buttonFont.loadFromFile(newfontpath)){
		cout<<"New font path not working"<<endl;
	}
}

void Button::updateSprite(){
	if(activated == true){
		button.setTexture(on);
	}
	if(activated == false){
		button.setTexture(off);
	}
}

void Button::resizeButton(int width, int height){
	button.setScale(width/button.getLocalBounds().width,height/button.getLocalBounds().height);
}

void Button::moveButton(int buttonxpos,int buttonypos){
	button.setPosition(buttonxpos,buttonypos);
	buttonText.setPosition(buttonxpos,buttonypos);
}

int main(){
	Button button1(resourcePath()+"On.png",resourcePath()+"Off.png",resourcePath()+"arial.ttf","ExampleText",50);
	RenderWindow window(VideoMode(800,800), "Button");
	while(window.isOpen()){
		Event event;
		while(window.pollEvent(event)){
			if(event.type == Event::Closed){
				window.close();
			}
			if(Mouse::isButtonPressed(Mouse::Left)){
				button1.activated=true;
				button1.updateSprite();
			}
			else{
				button1.activated=false;
				button1.updateSprite();
			}
		}
		window.clear();
		window.draw(button1.button);
		window.draw(button1.buttonText);
		window.display();
	}
}