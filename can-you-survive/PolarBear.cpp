#include "PolarBear.h"
//Constructor
PolarBear::PolarBear()
{
	srand(static_cast<unsigned int>(time(0)));
	health = 100;
	maxHealth = 100;
	level = 1;
	
	speed = 128;

	m_Position.x = 100;
	m_Position.y = 100;

	m_Resolution.x = 100;
	m_Resolution.y = 100;

	moveTime = 0;

	m_damage = 5;

	m_Texture.loadFromFile("graphics/polartemp.png");
	m_Sprite.setTexture(m_Texture);
	m_Sprite.scale(0.1, 0.1);
	m_Sprite.setOrigin(256, 256);
	m_Sprite.setPosition(m_Position);
}

void PolarBear::Spawn(int h, int mh, int l, int d, float x, float y) {
	health = h;
	maxHealth = mh;
	level = l;
	m_damage = d;

	m_Position.x = x;
	m_Position.y = y;
	goal_PositionX = m_Position.x;
	goal_PositionY = m_Position.y;
	m_Sprite.setPosition(m_Position);
}
void PolarBear::RemoveFromPlay() 
{
	//m_Position.x = 2000;
	//m_Position.y = 2000;
	//m_Sprite.setPosition(m_Position);
}
int PolarBear::Attack()
{
	int attackCalc = 0;
	attackCalc = rand() % 5 + m_damage;
	return attackCalc;

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

bool PolarBear::isAlive()
{
	if (health<=0) {
		m_Sprite.setRotation(180);
		//m_Position.x = 2000;
		//m_Position.y = 2000;
		//m_Sprite.setPosition(m_Position);
		return false;
	}
	else {
		return true;
	}
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
