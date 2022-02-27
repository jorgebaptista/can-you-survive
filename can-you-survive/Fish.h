#pragma once
#ifndef FISH_H
#define FISH_H
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;

using namespace std;

class Fish
{
public:
	//Constructor
	Fish();

	Vector2f getCenter();

	void Spawn(string t);
	//Return the type of fish
	string getType();

	//Return fish sprite
	Sprite getSprite();

	void setPosition(float x, float y);

	FloatRect getPosition();

	bool getActive();
	void setActive(bool value);

private:
	//The type of fish
	string type;

	// The current position of this fish
	Vector2f m_Position;

	Vector2f m_Resolution;



	//fish sprite
	Sprite m_Sprite;

	//fish texture
	Texture m_Texture;

	// Check if inactive
	bool m_Active;
};
#endif