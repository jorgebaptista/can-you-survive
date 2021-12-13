#pragma once
#ifndef FISH_H
#define FISH_H
#include "Collectable.h"

class Fish : public Collectable
{
public:
	//Constructor
	Fish();

	void Spawn(string t);
	//Return the type of fish
	string getType();

	//Return fish sprite
	Sprite getSprite();

	void setPosition(float x, float y);

	FloatRect getPosition();

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
};
#endif