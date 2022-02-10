#pragma once
#ifndef COLLECTABLE_H
#define COLLECTABLE_H
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;

using namespace std;

class Collectable
{
public:
	//Default Constructor
	Collectable();
	void PickedUp();
	bool isCollected();
	Vector2f getCenter();

protected:
	// current position
	bool collected;
	sf::Vector2f m_Position;
};
#endif