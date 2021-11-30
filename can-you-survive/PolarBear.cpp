#include "PolarBear.h"
//Constructor
PolarBear::PolarBear() {
	health = 100;
	maxHealth = 100;
	level = 1;
	damage = 5;

	m_Position.x = 100;
	m_Position.y = 100;

	m_Resolution.x = 100;
	m_Resolution.y = 100;



	m_Texture.loadFromFile("graphics/polartemp.png");
	m_Sprite.setTexture(m_Texture);
	m_Sprite.scale(0.1,0.1);
	m_Sprite.setOrigin(256, 256);
}

void PolarBear::Attack()
{
	
}

void PolarBear::TakeDamage(int dam)
{

}

FloatRect PolarBear::getPosition() {
	return m_Sprite.getGlobalBounds();
}

Vector2f PolarBear::getCenter() {
	return m_Position;
}

Sprite PolarBear::getSprite() {
	return m_Sprite;
}

bool isAlive(){
	return true;
}