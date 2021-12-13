#include "Fish.h"
//Constructor
Fish::Fish() {
	//type = "null";
}

void Fish::Spawn(string t) 
{
	type = t;
	if (type == "sea") 
	{
		m_Texture.loadFromFile("graphics/fishseatemp.png");
	}
	else if (type == "land") 
	{
		m_Texture.loadFromFile("graphics/fishlandtemp.png");
		m_Position.x = -100;
		m_Position.y = -100;
	}

	m_Sprite.setTexture(m_Texture);

	m_Sprite.setPosition(m_Position);
	m_Sprite.scale(2, 2);
	m_Sprite.setOrigin(10, 10);
}
string Fish::getType()
{
	//This will return the type of fish to determine what kind of effect
	//picking it up will have.
	return type;
}

Sprite Fish::getSprite() {
	return m_Sprite;
}

FloatRect Fish::getPosition() {
	return m_Sprite.getGlobalBounds();
}

void Fish::setPosition(float x, float y) {
	m_Position.x = x;
	m_Position.y = y;
	m_Sprite.setPosition(m_Position);
}