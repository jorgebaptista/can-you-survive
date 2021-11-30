#include "Tile.h"
//Constructor
Tile::Tile(){
	type="null";
	
	m_Position.x = 100;
	m_Position.y = 100;

	m_Resolution.x = 1920;
	m_Resolution.y = 1080;

	

	m_Texture.loadFromFile("graphics/tile.jpg");
	m_Sprite.setTexture(m_Texture);
	m_Sprite.setOrigin(256,256);
}

void Tile::ChangeType()
{
	//This will result in the type of the tile changing
}

FloatRect Tile::getPosition(){
	return m_Sprite.getGlobalBounds();
}

Vector2f Tile::getCenter(){
	return m_Position;
}

Sprite Tile::getSprite(){
	return m_Sprite;
}