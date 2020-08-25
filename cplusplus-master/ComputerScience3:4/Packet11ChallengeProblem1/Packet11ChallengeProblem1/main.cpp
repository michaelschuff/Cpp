#include<iostream>
#include<SFML/Graphics.hpp>
#include<cmath>
#include"ResourcePath.hpp"

using namespace std;
using namespace sf;

float area(int,int,int,int,int,int);

int main(){
	float pi=3.14159,a,b,c,A,B,C;
	int x1=100,y1=100,x2=400,y2=400,x3=700,y3=100;
	cout<<"x1?";
	 cin>>x1;
	 cout<<"y1?";
	 cin>>y1;
	 cout<<"x2?";
	 cin>>x2;
	 cout<<"y2?";
	 cin>>y2;
	 cout<<"x3?";
	 cin>>x3;
	 cout<<"y3?";
	 cin>>y3;
	int triarea = area(x1,y1,x2,y2,x3,y3);
	a=sqrt(float(y2-y1)*(y2-y1)+(x2-x1)*(x2-x1));
	b=sqrt(float(y3-y2)*(y3-y2)+(x3-x2)*(x3-x2));
	c=sqrt(float(y1-y3)*(y1-y3)+(x1-x3)*(x1-x3));
	A=acos((a*a+b*b-c*c)/(2*a*b));
	B=acos((b*b+c*c-a*a)/(2*c*a));
	C=acos((c*c+a*a-b*b)/(2*b*c));
	if(int(180*A/pi)==90||int(180*B/pi)==90||int(180*C/pi)==90){
		cout<<"Nice right triangle"<<endl;
	}
	cout<<"Area: "<<triarea<<endl;
	RenderWindow window(VideoMode(800,800), "Twiangle");
	Font font;
	if(!font.loadFromFile(resourcePath()+"sansation.ttf")){
		cout<<"Font not working"<<endl;
	}
	Text AA;
	AA.setFont(font);
	AA.setString(to_string((int)sqrt((y3-y2)*(y3-y2)+(x3-x2)*(x3-x2))));
	AA.setCharacterSize(40);
	AA.setOrigin(20,20);
	AA.setPosition(x2+(x3-x2)/2, y2+(y3-y2)/2);
	AA.setFillColor(Color(255,0,0));
	Text BB;
	BB.setFont(font);
	BB.setString(to_string((int)sqrt((y2-y1)*(y2-y1)+(x2-x1)*(x2-x1))));
	BB.setCharacterSize(40);
	BB.setOrigin(20,20);
	BB.setPosition(x1+(x2-x1)/2, y1+(y2-y1)/2);
	BB.setFillColor(Color(255,0,0));
	Text CC;
	CC.setFont(font);
	CC.setString(to_string((int)sqrt((y1-y3)*(y1-y3)+(x1-x3)*(x1-x3))));
	CC.setCharacterSize(40);
	CC.setOrigin(20,20);
	CC.setPosition(x1+(x3-x1)/2, y1+(y3-y1)/2);
	CC.setFillColor(Color(255,0,0));
	
	ConvexShape convex1;
	convex1.setPointCount(3);
	convex1.setPoint(0,Vector2f(x1,y1));
	convex1.setPoint(1,Vector2f(x2,y2));
	convex1.setPoint(2,Vector2f(x3,y3));
	convex1.setFillColor(Color(0,255,0));
	
	RectangleShape rectangle1(Vector2f(sqrt(triarea),sqrt(triarea)));
	rectangle1.setPosition(400,500);
	while(window.isOpen()){
		Event event;
		while(window.pollEvent(event)){
			if(event.type == Event::Closed){
				window.close();
			}
		}
		window.clear();
		window.draw(convex1);
		window.draw(rectangle1);
		window.draw(AA);
		window.draw(BB);
		window.draw(CC);
		window.display();
	}
}

float area(int x1,int y1,int x2,int y2,int x3,int y3){
	float A = sqrt(float(y2-y1)*(y2-y1)+(x2-x1)*(x2-x1));
	float B = sqrt(float(y3-y2)*(y3-y2)+(x3-x2)*(x3-x2));
	float C = sqrt(float(y1-y3)*(y1-y3)+(x1-x3)*(x1-x3));
	float S = (A+B+C)/2;
	return(sqrt(S*(S-A)*(S-B)*(S-C)));
}