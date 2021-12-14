#include "PolarBear.h"
//Constructor
PolarBear::PolarBear()
{
	health = 100;
	maxHealth = 100;
	level = 1;
	damage = 5;

	m_Position.x = 100;
	m_Position.y = 100;

	m_Resolution.x = 100;
	m_Resolution.y = 100;

	moveTime = 0;

	m_Texture.loadFromFile("graphics/polartemp.png");
	m_Sprite.setTexture(m_Texture);
	m_Sprite.scale(0.1, 0.1);
	m_Sprite.setOrigin(256, 256);
	m_Sprite.setPosition(m_Position);
}

void PolarBear::Attack()
{

}
//Reduce the polar bear's health
void PolarBear::ReduceHealth(int reduce)
{
	health = health - reduce;
}

//Return the global bounds of the polar bear
FloatRect PolarBear::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

//Return the center of the polar bear
Vector2f PolarBear::getCenter()
{
	return m_Position;
}

//Return the polar bears sprite
Sprite PolarBear::getSprite()
{
	return m_Sprite;
}

bool isAlive()
{
	return true;
}

int PolarBear::getHealth()
{
	return health;
}

void PolarBear::ChangeTerrain(Tile::terrainType terrain)
{
	m_currentTerrain = terrain;
}

Tile::terrainType PolarBear::getTerrain()
{
	return m_currentTerrain;
}
