#include "Collectable.h"
//Constructor
Collectable::Collectable()
{
	m_Position = sf::Vector2f(0, 0);
	collected = false;
}

void Collectable::CheckPickup(sf::Vector2f position)
{
	//Do a check to see if player position is the same as item position
	//if so, the item is considered picked up.
}

//Set collected to true
void Collectable::PickedUp() {
	collected = true;
}

//Return collected variable
bool Collectable::isCollected() {
	return collected;
}