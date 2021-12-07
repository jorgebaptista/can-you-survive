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
	move = 'c';

}

//void Player::Movement(x, y IN, x,y OUT ) {
//	//Allow the player to move using the arrow keys
//	//use a listener, and respond with new x,y co-ord
// Get input
//}

void Player::Movement(float elapsedTime, float totalTime) {
	if (moveTime <= totalTime) {
		move = 'c';
		if (UpPressed) {
			m_Position.y -= 100 * elapsedTime;
			m_Sprite.setRotation(270);
			move = 'U';
		}
		if (DownPressed) {
			m_Position.y += 100 * elapsedTime;
			m_Sprite.setRotation(90);
			move = 'D';
		}
		if (LeftPressed) {
			m_Position.x -= 100 * elapsedTime;
			m_Sprite.setRotation(180);
			move = 'L';
		}
		if (RightPressed) {
			m_Position.x += 100 * elapsedTime;
			m_Sprite.setRotation(0);
			move = 'R';
		}
		//move not being c means that a movement has been registered
		if (move != 'c') {
			//moveTime will be totalTime plus a certain amount to keep movement going the same way for a while.
			moveTime = totalTime + 1;
		}
	}
	else {
		if (move == 'U') {
			m_Position.y -= 100 * elapsedTime;
		}
		if (move == 'D') {
			m_Position.y += 100 * elapsedTime;
		}
		if (move == 'L') {
			m_Position.x -= 100 * elapsedTime;
		}
		if (move == 'R') {
			m_Position.x += 100 * elapsedTime;
		}
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