// classes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

class robot
{
public :
	// constructors
	robot(string name);
	robot();

	string name;
	int battery;
	int x;
	int y;

	// member
	void move(int degrees, int feet);
	void turn(int degrees);
	void battle(robot& robot);
private :
	bool isSarah;
	void terminate();
};

int main()
{
	robot t2("Terminator");

	robot ed209("Ed");
	robot johny5("Johny5");

	ed209.turn(90);
	johny5.battery = 1;
	johny5.move(0, 600);
	ed209.move(10, 400);
	ed209.move(30, 700);
	ed209.move(90, 600);
	ed209.battle(johny5);
	ed209.move(45, 800);


	system("pause");
    return 0;
}

robot::robot(string n)
{
	isSarah = true;
	name = n;
	battery = 100;
	x = 0;
	y = 0;
}

robot::robot()
{
	name = "no name";
	isSarah = false;
	battery = 100;
	x = 0;
	y = 0;
}

void robot::move(int degrees, int feet)
{
	battery -= 10;
	if (battery <= 5) {
		terminate();
	}
	robot::turn(degrees);
	x += feet;
	cout << name << "Moving " << feet << " feet" << ". Feet to position " << x << endl;
}

void robot::turn(int degrees)
{
	battery -= 10;
	if (battery <= 5) {
		terminate();
	}
	cout << name << "Turning " << degrees << " degrees" << endl;
}

void robot::battle(robot & robot)
{
	cout << name << " vs " << robot.name << endl;
	if (battery >= robot.battery) {
		cout << name << " wins!" << endl;
		robot.battery -= 25;
	}
	else {
		cout << "bzzzzrttttt x." << endl;
		battery -= 25;
	}
}

void robot::terminate()
{
	if (isSarah && name != "Johny5")
	{
		isSarah = false;
		cout << name << " Extermmmminate" << endl;
	}
	else {
		cout << name << " Needs more data. Where is Sarah??" << endl;
	}
}