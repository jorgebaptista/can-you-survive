#include "Player.h"
//Constructor
Player::Player() {
	health = 100;
	maxHealth = 100;
	stamina = 100;
	maxStamina = 100;
	level = 1;
	multiplier = 1.05;
	xp = 0;
	xpNeed = 100;
	damage = 5;
	fishNum = 0;


}

//void Player::Movement(x, y IN, x,y OUT ) {
//	//Allow the player to move using the arrow keys
//	//use a listener, and respond with new x,y co-ord
// Get input
//}

void Player::Movement(float elapsedTime) {
	if (UpPressed) {
		m_Position.y -= 10 * elapsedTime;
		m_Sprite.setRotation(270);
	}
	if (DownPressed) {
		m_Position.y += 10 * elapsedTime;
		m_Sprite.setRotation(90);
	}
	if (LeftPressed) {
		m_Position.x -= 10 * elapsedTime;
		m_Sprite.setRotation(180);
	}
	if (RightPressed) {
		m_Position.x += 10 * elapsedTime;
		m_Sprite.setRotation(0);
	}

	m_Sprite.setPosition(m_Position);
}


void StaminaDecrease(int reduce) {
	//Reduce stamina a certain amount
}

void CheckIfLevelUp() {
	//See if the parameters to level up have been met, if so, increment
	//the level and increase stats by the multiplier
}

void CheckGroundType(std::string type) {
	//See what type of ground the player is walking on, and make a decision
	//based on the ground.
}

//Movement section
void Player::moveLeft()
{
	LeftPressed = true;
}

void Player::moveRight()
{
	RightPressed = true;
}

void Player::moveUp()
{
	UpPressed = true;
}

void Player::moveDown()
{
	DownPressed = true;
}

void Player::stopLeft()
{
	LeftPressed = false;
}

void Player::stopRight()
{
	RightPressed = false;
}

void Player::stopUp()
{
	UpPressed = false;
}

void Player::stopDown()
{
	DownPressed = false;
}