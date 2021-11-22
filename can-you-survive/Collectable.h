#pragma once
#ifndef COLLECTABLE_H
#define COLLECTABLE_H
#include <iostream>
using namespace std;
class Collectable {
public:
	//Default Constructor
	Collectable();
	//Check if the player is currently in position to pickup item
	void CheckPickup();

protected:

	//x position variable
	int x;
	//y position variable
	int y;
};
#endif