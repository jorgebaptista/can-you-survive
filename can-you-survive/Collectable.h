#pragma once
#ifndef COLLECTABLE_H
#define COLLECTABLE_H
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;

using namespace std;

class Collectable {
public:
	//Default Constructor
	Collectable();
	//Check if the player is currently in position to pickup item
	void CheckPickup(sf::Vector2f position);

protected:
	// current position
	sf::Vector2f m_Position;
};
#endif