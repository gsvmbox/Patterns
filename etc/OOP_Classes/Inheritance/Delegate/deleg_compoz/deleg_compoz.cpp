
#include <iostream>
using namespace std;

class Rectangle
{
private:
	int x = 100;
	int y = 300;
public:
	void Area()
	{
		cout << "Window area is: " << x * y<<endl;
	}
};

class Message {
private: int posX, posY;
public: void Area() { cout << "WARNING Message!"<<endl; }
};

class Window
{
private:
	//Rectangle* start_W = new Rectangle;
	Message* start_W = new Message;
public:
	void Area()
	{
		start_W->Area();
	}
};

	
	int main()
{
		Window obj1;
		obj1.Area();

		return 0;
}

