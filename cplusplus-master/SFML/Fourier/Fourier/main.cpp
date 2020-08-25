#include<SFML/Graphics.hpp>
#include<iostream>
#include<cmath>
#include<vector>

using namespace std;
using namespace sf;

int main(){
	int angle=0,radius,iradius=75,x=200,y=300,prevx,prevy,n,f=0;
	double pi=3.14159265359;
	vector<int> points;
	vector<CircleShape> circles;
	vector<RectangleShape> lines;
	RenderWindow window(VideoMode(800,600),"Fourier");
	window.setFramerateLimit(60);
	RectangleShape Pixel(Vector2f(1,1));
	Pixel.setFillColor(Color(255,255,255));
	vector<vector<int>> paths;
    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type==Event::Closed){
                window.close();
            }
        }
		window.clear(Color(0,0,0));
		for(int i=0;i<=f;i++){//this creates an equation that approximates a square curve
			n=i*2+1;//n is an odd number
			prevx=x;
			prevy=y;
			radius=iradius*4/(n*pi);
			x+=radius*cos(n*angle*pi/180);
			y+=radius*sin(n*angle*pi/180);//the equation used
			if(i==f){
				points.insert(points.begin(),y);
			}
			CircleShape c1(radius);
			c1.setOrigin(radius,radius);
			c1.setFillColor(Color(0,0,0,0));
			c1.setOutlineColor(Color(255,255,255,100));
			c1.setOutlineThickness(1);
			c1.setPosition(prevx,prevy);
			circles.push_back(c1);//draw a circle that rotates at the point of its last circle
			RectangleShape line(Vector2f(1,1));
			line.setFillColor(Color(255,255,255));
			line.setSize(Vector2f(radius,1));
			line.setRotation(n*angle);
			line.setPosition(prevx,prevy);
			lines.push_back(line);//line from the center of the circle to the point rotating on the circle
			if(i==f){
				RectangleShape drawer(Vector2f(1,1));
				drawer.setFillColor(Color(255,255,255,50));
				drawer.setSize(Vector2f(500-x,1));
				drawer.setPosition(x,y);
				lines.push_back(drawer);//horizontal line going from the point on the circle and traces teh path of the curve
			}
			
		}
		for(int i=0;i<circles.size();i++){
			window.draw(circles[i]);
		}
		for(int i=0;i<lines.size();i++){
			window.draw(lines[i]);
		}
		for(int i=0;i<points.size();i++){
			Pixel.setPosition(500+i,points[i]);
			window.draw(Pixel);
		}
		if(points.size()>300){
			points.pop_back();
		}
        window.display();
		angle++;
		if(angle==360){//using degrees because it is easier to increment
			angle=0;
			f++;
		}//once we get to 360, add another circle onto the rotating point
		circles.clear();
		lines.clear();
		
		//when it runs, the points it draws arent always perfect, the majority of them are good, but some are off, and thats probably rounding errors or something like that
		
		x=200;
		y=300;
    }
}
