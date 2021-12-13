#include "Fish.h"
//Constructor
Fish::Fish() {
	type = "null";

	m_Position.x = 100;
	m_Position.y = 100;


}

void Fish::Spawn(string t) {
	type = t;
	if (type == "sea") {
		m_Texture.loadFromFile("graphics/fishseatemp.png");
	}
	else if (type == "land") {
		m_Texture.loadFromFile("graphics/fishlandtemp.png");
	}

	m_Sprite.setTexture(m_Texture);
	m_Sprite.scale(0.1, 0.1);
	m_Sprite.setOrigin(256, 256);
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