#include<iostream>
#include<SFML/Graphics.hpp>
#include<cmath>
using namespace std;
using namespace sf;
//circle of stars
void drawstar(int,int,int,RenderWindow &thatWindow,float,float);

int main(){
	int xpos,ypos,radius=100,stars;
	float pi = 3.14159265;
	cout<<"X coordinate";
	cin>>xpos;
	cout<<"Y coordinate";
	cin>>ypos;
	cout<<"Number of Stars";
	cin>>stars;
	RenderWindow window(VideoMode(800,800),"this problem was annoying");
	
	while (window.isOpen()){
		Event event;
		while(window.pollEvent(event)){
			if(event.type == Event::Closed){
				window.close();
			}
		}
		window.clear();
		for(int i=0;i<stars;i++){//draw each star, and give it an x and y coordinate that is spaced evenyl around the circle
			drawstar(xpos+cos(((2*pi*i)/stars)-pi/2)*radius, ypos+sin(((2*pi*i)/stars)-pi/2)*radius,175/stars, window, pi, (2*pi*i)/(float)stars);
		}
		window.display();
	}
}
void drawstar(int xpos,int ypos,int radius,RenderWindow &thatWindow,float pi, float i){//"i" is the degrees it is around the origonal circle
	ConvexShape convex1;//create star with 5 points, ordered in a way so it isnt a pentagon, and set each point
	convex1.setPosition(xpos,ypos);
	convex1.setPointCount(5);
	convex1.setPoint(0,Vector2f(cos(18*(pi/180)+pi+i)*radius,sin(18*(pi/180)+pi+i)*radius));
	convex1.setPoint(1,Vector2f(cos(162*(pi/180)+pi+i)*radius,sin(162*(pi/180)+pi+i)*radius));
	convex1.setPoint(2,Vector2f(cos(306*(pi/180)+pi+i)*radius,sin(306*(pi/180)+pi+i)*radius));
	convex1.setPoint(3,Vector2f(cos(90*(pi/180)+pi+i)*radius,sin(90*(pi/180)+pi+i)*radius));
	convex1.setPoint(4,Vector2f(cos(234*(pi/180)+pi+i)*radius,sin(234*(pi/180)+pi+i)*radius));
	convex1.setFillColor(Color(0,0,255));
	thatWindow.draw(convex1);
}