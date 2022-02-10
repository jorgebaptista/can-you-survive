#include "Collectable.h"
//Constructor
Collectable::Collectable()
{
	m_Position.x = -1000;
	m_Position.y = -1000;
	collected = false;
}

//Set collected to true
void Collectable::PickedUp() {
	collected = true;
}

//Return collected variable
bool Collectable::isCollected() {
	return collected;
}

Vector2f Collectable::getCenter()
{
	return m_Position;
}