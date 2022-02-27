#include "Fish.h"
//Constructor
Fish::Fish()
{
	type = "null";

	m_Position.x = -1000;
	m_Position.y = -1000;
}

Vector2f Fish::getCenter()
{
	return m_Position;
}

//Spawn fish with type
void Fish::Spawn(string t)
{
	type = t;
	if (type == "sea")
	{
		m_Texture.loadFromFile("graphics/fishsea.png");
	}
	else if (type == "land")
	{
		m_Texture.loadFromFile("graphics/fishland.png");
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

//return sprite
Sprite Fish::getSprite() {
	return m_Sprite;
}

//return position
FloatRect Fish::getPosition() {
	return m_Sprite.getGlobalBounds();
}

bool Fish::getActive()
{
	return m_Active;
}

void Fish::setActive(bool value)
{
	m_Active = value;

	if (!value)
	{
		// set its position far away from the level
		m_Position.x = -1000;
		m_Position.y = -1000;
	}
}

//set position
void Fish::setPosition(float x, float y) {
	m_Position.x = x;
	m_Position.y = y;
	m_Sprite.setPosition(m_Position);
}