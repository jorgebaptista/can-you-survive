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
	staminaTimer = 0;

}

//void Player::Movement(x, y IN, x,y OUT ) {
//	//Allow the player to move using the arrow keys
//	//use a listener, and respond with new x,y co-ord
// Get input
//}

void Player::Movement(float elapsedTime, float totalTime) {
	//If enough total time has passed, the player can move again
	if (moveTime <= totalTime) {
		//move set to c to stop movement until button is pressed.
		move = 'c';
		//Checks direction pressed to see where to move character
		if (UpPressed) {
			//set to U to allow continous movement up
			move = 'U';
		}
		if (DownPressed) {
			//set to D to allow continous movement down
			move = 'D';
		}
		if (LeftPressed) {
			//set to L to allow continous movement left
			move = 'L';
		}
		if (RightPressed) {		
			//set to R to allow continous movement right
			move = 'R';
		}
		//move not being c means that a movement has been registered
		if (move != 'c') {
			//moveTime will be totalTime plus a certain amount to keep movement going the same way for a while.
			moveTime = totalTime + 1;
		}
	}
	//If moveTime is still larger than totalTime, then the character will continue moving in the same direction as what was inputted
	
	//Depending on what move is, the player will continue moving in the previously inputted direction
	if (move == 'U') {
		m_Position.y -= 100 * elapsedTime;
		m_Sprite.setRotation(270);
	}
	if (move == 'D') {
		m_Position.y += 100 * elapsedTime;
		m_Sprite.setRotation(90);
	}
	if (move == 'L') {
		m_Position.x -= 100 * elapsedTime;
		m_Sprite.setRotation(180);
	}
	if (move == 'R') {
		m_Position.x += 100 * elapsedTime;
		m_Sprite.setRotation(0);
	}


	m_Sprite.setPosition(m_Position);
}


void Player::StaminaDecrease(float reduce) {
	//Reduce stamina a certain amount
	stamina = stamina - reduce;
}

void CheckIfLevelUp() {
	//See if the parameters to level up have been met, if so, increment
	//the level and increase stats by the multiplier
}

void CheckGroundType(std::string type) {
	//See what type of ground the player is walking on, and make a decision
	//based on the ground.
}

float Player::getStamina() {
	return stamina;
}

float Player::getStaminaTimer() {
	return staminaTimer;
}

void Player::setStaminaTimer(float staminaTimerAdd) {
	staminaTimer = staminaTimer + staminaTimerAdd;
}

void Player::setStaminaTimer() {
	staminaTimer = 0;
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