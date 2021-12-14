#include "Tile.h"
//Constructor
Tile::Tile(Vector2f position, terrainType terrain)
{
	m_terrainType = terrain; // assign the type of terrain from the parameter

	m_Sprite.setPosition(position); // position from parameter

	// check correct terrain type and set it's texture accordingly
	switch (m_terrainType)
	{
	case Tile::terrainType::SNOW:
		m_Texture.loadFromFile("graphics/snow.png");
		break;
	case Tile::terrainType::ICE:
		m_Texture.loadFromFile("graphics/ice.png");
		break;
	case Tile::terrainType::WATER:
		m_Texture.loadFromFile("graphics/water.png");
		break;
	default:
		break;
	}

	m_Sprite.setTexture(m_Texture); // assign the texture to the sprite
	m_Sprite.setOrigin(128,128); // set origin to center

	// ???????????????? TODO: TILE Scale or different file size
	m_Sprite.setScale(.5,.5);
}

//void Tile::ChangeType()
//{
//	//This will result in the type of the tile changing
//}

//FloatRect Tile::getPosition(){
//	return m_Sprite.getGlobalBounds();
//}
//
//Vector2f Tile::getCenter(){
//	return m_Position;
//}
//
Sprite Tile::getSprite()
{
	return m_Sprite;
}