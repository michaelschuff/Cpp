#include<iostream>
#include<SFML/Graphics.hpp>
#include<vector>
#include<cstdlib>
#include<ctime>
//create a bunch of random circles, self explanatory
using namespace std;
using namespace sf;

class Circle{
public:
	int radius = rand()%50+50;
	int xpos = rand()%800;
	int ypos = rand()%800;
	int red = rand()%255;
	int green = rand()%255;
	int blue = rand()%255;
	CircleShape createcircle();
};

CircleShape Circle::createcircle(){
	CircleShape circle1(radius);
	circle1.setOrigin(radius,radius);
	circle1.setPosition(xpos,ypos);
	circle1.setFillColor(Color(red,green,blue));
	return(circle1);
}

int main(){
	srand(time(NULL));
	int num1;
	cout<<"How many circles do you want?";
	cin>>num1;
	vector<Circle> vector1;
	RenderWindow window(VideoMode(800,800), "Taste the Rainbow. Contract the Rainbow.");
	for(int i=0;i<num1;i++){
		Circle circle1;
		circle1.createcircle();
		vector1.push_back(circle1);
	}
	
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		
		window.clear();
		for(int i=0;i<vector1.size();i++){
			window.draw(vector1[i].createcircle());
		}
		window.display();
	}
}