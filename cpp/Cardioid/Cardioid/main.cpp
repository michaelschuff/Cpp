#include<SFML/Graphics.hpp>
#include<iostream>
#include<cmath>
#include<vector>

using namespace sf;
using namespace std;

void drawline(int x1,int y1,int x2,int y2,RenderWindow &window){
	RectangleShape line(Vector2f(sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)),1));
	line.setFillColor(Color(255,255,255,50	));
	line.setPosition(x1,y1);
	line.setRotation(atan2(y2-y1,x2-x1)*180/3.1416);
	window.draw(line);
}

int main(){
	int points=10000;
	int times=2;
	
	vector<vector<double>> lines;
	vector<double> l;
	float framecounter=0;
	float pi=3.1416;
	float radians=2*pi/points;
	int radius=200;
	double d,next;
	RenderWindow window(VideoMode(800,800),"Cardioid");
	window.setFramerateLimit(60);
	while(window.isOpen()){
		Event event;
		while(window.pollEvent(event)){
			if(event.type==Event::Closed){
				window.close();
			}
		}
		if(framecounter<120){
			window.clear();
			l={double(radians*framecounter*points/120),double(radians*(int((framecounter*points/120)*times)%points))};
			lines.push_back(l);
			for(int i=0;i<lines.size();i++){
				drawline(400+radius*cos(lines[i][0]),400+radius*sin(lines[i][0]),400+radius*cos(lines[i][1]),400+radius*sin(lines[i][1]),window);
			}
		}
		window.display();
		framecounter++;
		if(framecounter==120){
			times++;
		}
		if(framecounter==240){
			framecounter=0;
		}
		if(lines.size()>120){
			lines.erase(lines.begin());
		}
	}
}