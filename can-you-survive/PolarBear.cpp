#include "PolarBear.h"
//Constructor
PolarBear::PolarBear(Vector2f position)
{
	health = 100;
	maxHealth = 100;
	level = 1;
	
	speed = 128;

	m_Position = position;

	goal_PositionX = m_Position.x;
	goal_PositionY = m_Position.y;

	m_Resolution.x = 100;
	m_Resolution.y = 100;

	moveTime = 0;
	m_damage = 5;

	m_Texture.loadFromFile("graphics/polar.png");
	m_Sprite.setTexture(m_Texture);
	m_Sprite.scale(1, 1);
	m_Sprite.setOrigin(19, 19);
	m_Sprite.setPosition(m_Position);
}

//Used to spawn new polarbears when they die
void PolarBear::Spawn(int h, int mh, int l, int d, float x, float y) {
	float multi = pow(1.05, l);
	health = h * multi;
	maxHealth = mh * multi;
	level = l;
	m_damage = d * multi;

	m_Position.x = x;
	m_Position.y = y;
	goal_PositionX = m_Position.x;
	goal_PositionY = m_Position.y;
	m_Sprite.setPosition(m_Position);
}

//Perform attack calculation
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

//Check if alive and if not
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

//return health
int PolarBear::getHealth()
{
	return health;
}

//return terrain and assign it to polarbear
void PolarBear::ChangeTerrain(Tile::terrainType terrain)
{
	m_currentTerrain = terrain;
}

//get terrain type
Tile::terrainType PolarBear::getTerrain()
{
	return m_currentTerrain;
}
