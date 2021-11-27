#include "PolarBear.h"
//Constructor
PolarBear::PolarBear() {
	health = 100;
	maxHealth = 100;
	level = 1;
	damage = 5;
}

void PolarBear::Attack()
{
	
}

void PolarBear::TakeDamage(int dam)
{

}

sf::Vector2f PolarBear::getPosition()
{
	return m_Position;
}

bool isAlive(){
	return true;
}