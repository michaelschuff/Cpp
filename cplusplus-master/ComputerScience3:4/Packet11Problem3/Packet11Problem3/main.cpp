#include<iostream>
#include<SFML/Graphics.hpp>
#include<cmath>

using namespace std;
using namespace sf;

float area(int,int,int,int,int,int);

int main(){
	srand(time(NULL));
	int x1,y1,x2,y2,x3,y3;
	float a,b,c,A,B,C,pi=3.14159;
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
	int triarea = area(x1,y1,x2,y2,x3,y3);//get area, using herins formula
	a=sqrt(float(y2-y1)*(y2-y1)+(x2-x1)*(x2-x1));//each side length, distance formula
	b=sqrt(float(y3-y2)*(y3-y2)+(x3-x2)*(x3-x2));
	c=sqrt(float(y1-y3)*(y1-y3)+(x1-x3)*(x1-x3));
	A=acos((a*a+b*b-c*c)/(2*a*b));//angle of each side, law of cosines
	B=acos((b*b+c*c-a*a)/(2*c*a));
	C=acos((c*c+a*a-b*b)/(2*b*c));
	if(int(180*A/pi)==90||int(180*B/pi)==90||int(180*C/pi)==90){//if an angle is 90 degrees, using degrees so we can convert the angle to an int, because it most likely wont be exact
		cout<<"Nice right triangle"<<endl;
	}
	cout<<"Area: "<<triarea<<endl;
	RenderWindow window(VideoMode(800,800), "Twiangle");
	ConvexShape convex1;
	convex1.setPointCount(3);//create the triangle
	convex1.setPoint(0,Vector2f(x1,y1));
	convex1.setPoint(1,Vector2f(x2,y2));
	convex1.setPoint(2,Vector2f(x3,y3));
	convex1.setFillColor(Color(0,255,0));
	
	RectangleShape rectangle1(Vector2f(sqrt(triarea),sqrt(triarea)));//create a rectangle with equal area
	rectangle1.setOrigin(Vector2f(sqrt(triarea)/2,sqrt(triarea)/2));
	rectangle1.setPosition(400,400);
	
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