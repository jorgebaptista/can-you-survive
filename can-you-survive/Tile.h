#pragma once
#ifndef TILE_H
#define TILE_H
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

class Tile 
{
public:
	//Constructor
	Tile();
	//Function to change the type of the tile.
	void ChangeType();

	FloatRect getPosition();

	Vector2f getCenter();

	Sprite getSprite();
	
protected:
	//Will be enum, specifies the tile type
	std::string type;

	Vector2f m_Position;

	Vector2f m_Resolution;

	Sprite m_Sprite;

	Texture m_Texture;

	
};
#endif