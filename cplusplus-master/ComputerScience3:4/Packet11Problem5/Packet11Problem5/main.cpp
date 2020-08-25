#include<iostream>
#include<SFML/Graphics.hpp>
#include<cmath>

using namespace std;
using namespace sf;

void drawstar(int,int,int,RenderWindow &thatWindow);

int main(){
	int xpos,ypos,radius;
	cout<<"X coordinate";
	cin>>xpos;
	cout<<"Y coordinate";
	cin>>ypos;
	cout<<"Radius";
	cin>>radius;
	RenderWindow window(VideoMode(800,800), "Pointy Pentagon");
	
	while (window.isOpen()){
		Event event;
		while(window.pollEvent(event)){
			if(event.type == Event::Closed){
				window.close();
			}
		}
		window.clear();
		drawstar(xpos,ypos,radius,window);
		window.display();
	}
}
void drawstar(int xpos,int ypos,int radius,RenderWindow &thatWindow){
	float pi = 3.14159265;
	ConvexShape convex1;
	convex1.setPosition(xpos,ypos);
	convex1.setPointCount(5);
	convex1.setPoint(0,Vector2f(cos(18*(pi/180)+pi)*radius,sin(18*(pi/180)+pi)*radius));
	convex1.setPoint(1,Vector2f(cos(162*(pi/180)+pi)*radius,sin(162*(pi/180)+pi)*radius));
	convex1.setPoint(2,Vector2f(cos(306*(pi/180)+pi)*radius,sin(306*(pi/180)+pi)*radius));
	convex1.setPoint(3,Vector2f(cos(90*(pi/180)+pi)*radius,sin(90*(pi/180)+pi)*radius));
	convex1.setPoint(4,Vector2f(cos(234*(pi/180)+pi)*radius,sin(234*(pi/180)+pi)*radius));
	convex1.setFillColor(Color(0,0,255));
	thatWindow.draw(convex1);
}