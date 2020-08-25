#include <SFML/Graphics.hpp>
//create three shapes, i literally put random values into this
using namespace std;
using namespace sf;

int main(){
	RenderWindow window(VideoMode(800,800), "Spicy Shapes");
	CircleShape circle1(50);
	circle1.setOrigin(50,50);
	circle1.setPosition(400,400);
	circle1.setFillColor(Color(255,0,0));
	
	RectangleShape rectangle1(Vector2f(98,100));
	rectangle1.setOrigin(Vector2f(49,50));
	rectangle1.setPosition(700,200);
	rectangle1.setFillColor(Color(0,255,0));

	ConvexShape convex1;
	convex1.setPointCount(5);
	convex1.setPoint(0,Vector2f(0,0));
	convex1.setPoint(1,Vector2f(300,80));
	convex1.setPoint(2,Vector2f(5,120));
	convex1.setPoint(3,Vector2f(40,200));
	convex1.setPoint(4,Vector2f(0,50));
	convex1.setPosition(300,500);
	convex1.setFillColor(Color(0,0,255));
	
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		
		window.clear();
		window.draw(circle1);
		window.draw(rectangle1);
		window.draw(convex1);
		window.display();
	}
}