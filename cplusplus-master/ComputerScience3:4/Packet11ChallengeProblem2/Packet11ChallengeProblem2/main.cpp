#include<iostream>
#include<SFML/Graphics.hpp>
#include<cmath>
#include"ResourcePath.hpp"
using namespace std;
using namespace sf;

void drawstar(int,int,int,RenderWindow &thatWindow,float,float,float,int);

int main(){
	int xpos,ypos,radius,stars;
	float pi = 3.14159265;
	float j = pi/1000;
	int k = 0;
	float height = 800/1.9;
	xpos = 160;
	ypos = 2947/26;
	stars = 9;
	RenderWindow window(VideoMode(800,height), "A-murica!");
	
	RectangleShape stripe1(Vector2f(480,height/13));
	stripe1.setPosition(320,0);
	stripe1.setFillColor(Color(187,19,62));
	
	RectangleShape stripe2(Vector2f(480,height/13));
	stripe2.setPosition(320,height/13);
	stripe2.setFillColor(Color(255,255,255));
	
	RectangleShape stripe3(Vector2f(480,height/13));
	stripe3.setPosition(320,2*height/13);
	stripe3.setFillColor(Color(187,19,62));
	
	RectangleShape stripe4(Vector2f(480,height/13));
	stripe4.setPosition(320,3*height/13);
	stripe4.setFillColor(Color(255,255,255));
	
	RectangleShape stripe5(Vector2f(480,height/13));
	stripe5.setPosition(320,4*height/13);
	stripe5.setFillColor(Color(187,19,62));
	
	RectangleShape stripe6(Vector2f(480,height/13));
	stripe6.setPosition(320,5*height/13);
	stripe6.setFillColor(Color(255,255,255));
	
	RectangleShape stripe7(Vector2f(480,height/13));
	stripe7.setPosition(320,6*height/13);
	stripe7.setFillColor(Color(187,19,62));
	
	RectangleShape stripe8(Vector2f(800,height/13));
	stripe8.setPosition(0,7*height/13);
	stripe8.setFillColor(Color(255,255,255));
	
	RectangleShape stripe9(Vector2f(800,height/13));
	stripe9.setPosition(0,8*height/13);
	stripe9.setFillColor(Color(187,19,62));
	
	RectangleShape stripe10(Vector2f(800,height/13));
	stripe10.setPosition(0,9*height/13);
	stripe10.setFillColor(Color(255,255,255));
	
	RectangleShape stripe11(Vector2f(800,height/13));
	stripe11.setPosition(0,10*height/13);
	stripe11.setFillColor(Color(187,19,62));
	
	RectangleShape stripe12(Vector2f(800,height/13));
	stripe12.setPosition(0,11*height/13);
	stripe12.setFillColor(Color(255,255,255));
	
	RectangleShape stripe13(Vector2f(800,height/13));
	stripe13.setPosition(0,12*height/13);
	stripe13.setFillColor(Color(187,19,62));
	
	while (window.isOpen()){
		k++;
		Event event;
		while(window.pollEvent(event)){
			if(event.type == Event::Closed){
				window.close();
			}
		}
		window.clear(Color(0,33,71));
		for(int i=0;i<stars;i++){
			drawstar(xpos+cos((((2*pi*i)/stars)-pi/2)+(j*k))*85, ypos+sin((((2*pi*i)/stars)-pi/2)+(j*k))*85,175/stars, window, pi, (2*pi*i)/(float)stars,j,k);
		}
		if(k%200==0){
			stripe1.setFillColor(Color(187,19,62));
			stripe2.setFillColor(Color(255,255,255));
			stripe3.setFillColor(Color(187,19,62));
			stripe4.setFillColor(Color(255,255,255));
			stripe5.setFillColor(Color(187,19,62));
			stripe6.setFillColor(Color(255,255,255));
			stripe7.setFillColor(Color(187,19,62));
			stripe8.setFillColor(Color(255,255,255));
			stripe9.setFillColor(Color(187,19,62));
			stripe10.setFillColor(Color(255,255,255));
			stripe11.setFillColor(Color(187,19,62));
			stripe12.setFillColor(Color(255,255,255));
			stripe13.setFillColor(Color(187,19,62));
		}
		if(k%200==99){
			stripe1.setFillColor(Color(255,255,255));
			stripe2.setFillColor(Color(187,19,62));
			stripe3.setFillColor(Color(255,255,255));
			stripe4.setFillColor(Color(187,19,62));
			stripe5.setFillColor(Color(255,255,255));
			stripe6.setFillColor(Color(187,19,62));
			stripe7.setFillColor(Color(255,255,255));
			stripe8.setFillColor(Color(187,19,62));
			stripe9.setFillColor(Color(255,255,255));
			stripe10.setFillColor(Color(187,19,62));
			stripe11.setFillColor(Color(255,255,255));
			stripe12.setFillColor(Color(187,19,62));
			stripe13.setFillColor(Color(255,255,255));
		}
		window.draw(stripe1);
		window.draw(stripe2);
		window.draw(stripe3);
		window.draw(stripe4);
		window.draw(stripe5);
		window.draw(stripe6);
		window.draw(stripe7);
		window.draw(stripe8);
		window.draw(stripe9);
		window.draw(stripe10);
		window.draw(stripe11);
		window.draw(stripe12);
		window.draw(stripe13);
		window.display();
	}
}
void drawstar(int xpos,int ypos,int radius,RenderWindow &thatWindow,float pi, float i,float j,int k){
	ConvexShape convex1;
	convex1.setPosition(xpos,ypos);
	convex1.setPointCount(5);
	convex1.setPoint(0,Vector2f(cos(18*(pi/180)+pi+i+(j*k))*radius,sin(18*(pi/180)+pi+i+(j*k))*radius));
	convex1.setPoint(1,Vector2f(cos(162*(pi/180)+pi+i+(j*k))*radius,sin(162*(pi/180)+pi+i+(j*k))*radius));
	convex1.setPoint(2,Vector2f(cos(306*(pi/180)+pi+i+(j*k))*radius,sin(306*(pi/180)+pi+i+(j*k))*radius));
	convex1.setPoint(3,Vector2f(cos(90*(pi/180)+pi+i+(j*k))*radius,sin(90*(pi/180)+pi+i+(j*k))*radius));
	convex1.setPoint(4,Vector2f(cos(234*(pi/180)+pi+i+(j*k))*radius,sin(234*(pi/180)+pi+i+(j*k))*radius));
	convex1.setFillColor(Color(255,255,255));
	thatWindow.draw(convex1);
}
