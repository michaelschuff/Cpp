#include<iostream>
#include<SFML/Graphics.hpp>
#include<vector>
#include<ctime>
#include<cstdlib>
#include<cmath>
//four buttons that get a random color on a left click, and go back to the last color on a right click
using namespace std;
using namespace sf;

int distanceformula(int x1,int y1,int x2,int y2){
	return(sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)));
}

class Colors{
public:
	int red=rand()%255;
	int green=rand()%255;
	int blue=rand()%255;
};
int main(){
	srand(time(NULL));
	bool leftmousedown=false,rightmousedown=true;
	int pos1=0,pos2=0,pos3=0,pos4=0;
	vector<Colors> vect1;
	CircleShape Circle1(100);//create 4 circles, and 4 arrays, c1,c2,etc, v1,v2,etc
	Circle1.setOrigin(100,100);
	Circle1.setPosition(200,200);
	Circle1.setFillColor(Color(0,0,0));
	Colors color1;
	vect1.push_back(color1);
	Circle1.setFillColor(Color(color1.red,color1.green,color1.blue));
	
	vector<Colors> vect2;
	CircleShape Circle2(100);
	Circle2.setOrigin(100,100);
	Circle2.setPosition(600,200);
	Circle2.setFillColor(Color(0,0,0));
	Colors color2;
	vect2.push_back(color2);
	Circle2.setFillColor(Color(color2.red,color2.green,color2.blue));
	
	vector<Colors> vect3;
	CircleShape Circle3(100);
	Circle3.setOrigin(100,100);
	Circle3.setPosition(200,600);
	Circle3.setFillColor(Color(0,0,0));
	Colors color3;
	vect3.push_back(color3);
	Circle3.setFillColor(Color(color3.red,color3.green,color3.blue));
	
	vector<Colors> vect4;
	CircleShape Circle4(100);
	Circle4.setOrigin(100,100);
	Circle4.setPosition(600,600);
	Circle4.setFillColor(Color(0,0,0));
	Colors color4;
	vect4.push_back(color4);
	Circle4.setFillColor(Color(color4.red,color4.green,color4.blue));
	
	RenderWindow window(VideoMode(800,800), "Clicky Clicky");
	while(window.isOpen()){
		Event event;
		while(window.pollEvent(event)){
			if(event.type==Event::Closed){
				window.close();
			}
		}
		if(Mouse::isButtonPressed(Mouse::Left)){
			leftmousedown=true;
		}
		if(leftmousedown&&!Mouse::isButtonPressed(Mouse::Left)){//this basically says if you click within a 200 pixel radius of the center of the circle (for each circle), then create a new color if you are at the end of the vector, or go to the next color if you arent
			leftmousedown=false;
			if(distanceformula(200,200,Mouse::getPosition(window).x,Mouse::getPosition(window).y)<=100){
				pos1++;
				if(pos1>=vect1.size()){
					Colors newColor;
					vect1.push_back(newColor);
					Circle1.setFillColor(Color(newColor.red,newColor.green,newColor.blue));
				}
				else{
					Circle1.setFillColor(Color(vect1[pos1].red,vect1[pos1].green,vect1[pos1].blue));
				}
			}
			else if(distanceformula(600,200,Mouse::getPosition(window).x,Mouse::getPosition(window).y)<=100){
				pos2++;
				if(pos2>=vect2.size()){
					Colors newColor;
					vect2.push_back(newColor);
					Circle2.setFillColor(Color(newColor.red,newColor.green,newColor.blue));
				}
				else{
					Circle2.setFillColor(Color(vect2[pos2].red,vect2[pos2].green,vect2[pos2].blue));
				}
			}
			else if(distanceformula(200,600,Mouse::getPosition(window).x,Mouse::getPosition(window).y)<=100){
				pos3++;
				if(pos3>=vect3.size()){
					Colors newColor;
					vect3.push_back(newColor);
					Circle3.setFillColor(Color(newColor.red,newColor.green,newColor.blue));
				}
				else{
					Circle3.setFillColor(Color(vect3[pos3].red,vect3[pos3].green,vect3[pos3].blue));
				}
			}
			else if(distanceformula(600,600,Mouse::getPosition(window).x,Mouse::getPosition(window).y)<=100){
				pos4++;
				if(pos4>=vect4.size()){
					Colors newColor;
					vect4.push_back(newColor);
					Circle4.setFillColor(Color(newColor.red,newColor.green,newColor.blue));
				}
				else{
					Circle4.setFillColor(Color(vect4[pos4].red,vect4[pos4].green,vect4[pos4].blue));
				}
			}
		}
		if(Mouse::isButtonPressed(Mouse::Right)){//have like a double if statement thing so if they click and hold down it doesnt cycle rapidly through colors
			rightmousedown=true;
		}
		if(rightmousedown&&!Mouse::isButtonPressed(Mouse::Right)){
			rightmousedown=false;
			if(distanceformula(200,200,Mouse::getPosition(window).x,Mouse::getPosition(window).y)<=100){//if they right click, decrease the position, and set the color
				if(pos1!=0){
					pos1--;
				}
				Circle1.setFillColor(Color(vect1[pos1].red,vect1[pos1].green,vect1[pos1].blue));
			}
			else if(distanceformula(600,200,Mouse::getPosition(window).x,Mouse::getPosition(window).y)<=100){
				if(pos2!=0){
					pos2--;
				}
				Circle2.setFillColor(Color(vect2[pos2].red,vect2[pos2].green,vect2[pos2].blue));
			}
			else if(distanceformula(200,600,Mouse::getPosition(window).x,Mouse::getPosition(window).y)<=100){
				if(pos3!=0){
					pos3--;
				}
				Circle3.setFillColor(Color(vect3[pos3].red,vect3[pos3].green,vect3[pos3].blue));
			}
			else if(distanceformula(600,600,Mouse::getPosition(window).x,Mouse::getPosition(window).y)<=100){
				if(pos4!=0){
					pos4--;
				}
				Circle4.setFillColor(Color(vect4[pos4].red,vect4[pos4].green,vect4[pos4].blue));
			}
		}
		window.clear(Color(0,0,0));
		window.draw(Circle1);
		window.draw(Circle2);
		window.draw(Circle3);
		window.draw(Circle4);
		window.display();
	}
}