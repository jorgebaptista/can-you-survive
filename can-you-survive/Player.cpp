#include "Player.h"
//Constructor
Player::Player()
{
	health = 100;
	maxHealth = 100;
	stamina = 100;
	maxStamina = 100;
	level = 1;
	multiplier = 1.05;
	xp = 0;
	xpNeed = 100;
	m_damage = 5;
	speed = 640;
	fishNum = 100;
	move = 'c';
	staminaTimer = 0;
	m_Position.x = 128;
	m_Position.y = 128;
	goal_PositionX=m_Position.x;
	goal_PositionY=m_Position.y;
	m_Sprite.setPosition(m_Position);

	UpPressed = false;
	DownPressed = false;
	LeftPressed = false;
	RightPressed = false;
}

//void Player::Movement(x, y IN, x,y OUT ) 
// {
//	//Allow the player to move using the arrow keys
//	//use a listener, and respond with new x,y coordinates
// Get input
//}

void Player::Movement(float elapsedTime, float totalTime)
{
	//If enough total time has passed, the player can move again
	if (moveTime <= totalTime)
	{
		m_Position.x = goal_PositionX;
		m_Position.y = goal_PositionY;
		m_Sprite.setPosition(m_Position);
		//move set to c to stop movement until button is pressed.
		move = 'c';
		//Checks direction pressed to see where to move character
		if (UpPressed)
		{
			goal_PositionY = m_Position.y - 128;
			//m_Position.y -= 128;
			//set to U to allow continous movement up
			move = 'U';
		}
		else if (DownPressed)
		{
			goal_PositionY = m_Position.y + 128;
			//m_Position.y += 128;
			//set to D to allow continous movement down
			move = 'D';
		}
		else if (LeftPressed)
		{
			goal_PositionX = m_Position.x - 128;
			//m_Position.x -= 128;
			//set to L to allow continous movement left
			move = 'L';
		}
		else if (RightPressed)
		{
			goal_PositionX = m_Position.x + 128;
			//m_Position.x += 128;
			//set to R to allow continous movement right
			move = 'R';
		}
		//move not being c means that a movement has been registered
		if (move != 'c')
		{
			//moveTime will be totalTime plus a certain amount to keep movement going the same way for a while.
			moveTime = totalTime + 0.2;
		}
	}
	//If moveTime is still larger than totalTime, then the character will continue moving in the same direction as what was inputted

	//Depending on what move is, the player will continue moving in the previously inputted direction
	if (move == 'U')
	{
		if (m_Position.y > goal_PositionY) 
		{
			m_Position.y -= speed * elapsedTime;
			m_Sprite.setRotation(270);
		}
		else 
		{
			m_Position.y = goal_PositionY;
		}
		
	}
	if (move == 'D')
	{
		if (m_Position.y < goal_PositionY) 
		{
			m_Position.y += speed * elapsedTime;
			m_Sprite.setRotation(90);
		}
		else 
		{
			m_Position.y = goal_PositionY;
		}
	}
	if (move == 'L')
	{
		if (m_Position.x > goal_PositionX) 
		{
			m_Position.x -= speed * elapsedTime;
			m_Sprite.setRotation(180);
		}
		else 
		{
			m_Position.x = goal_PositionX;
		}
	}
	if (move == 'R')
	{
		if (m_Position.x < goal_PositionX) {
			m_Position.x += speed * elapsedTime;
			m_Sprite.setRotation(0);
		}
		else 
		{
			m_Position.x = goal_PositionX;
		}
	}


	m_Sprite.setPosition(m_Position);
}

//Function used to eat fish in inventory
void Player::EatFish()
{
	//Check if there is fish in the inventory
	if (fishNum > 0)
	{
		//Increase stamina by maxStamina amount divided by 10
		stamina = stamina + maxStamina / 10;
		//If stamina addition is more than maxStamina, set stamina to maxStamina
		if (stamina >= maxStamina)
		{
			stamina = maxStamina;
		}
		//Reduce fish in inventory by 1
		xp = xp + 10;
		fishNum = fishNum - 1;
	}
}

void Player::addHealth(float h) 
{
	health = health + h;
	if (health > maxHealth) {
		health = maxHealth;
	}
}
//Add xp to players total experience
void Player::addXP(int exp) 
{
	xp = xp + exp;
}

void Player::StaminaDecrease(float reduce)
{
	//Reduce stamina a certain amount
	stamina = stamina - reduce;
}

void Player::Hibernate() 
{
	stamina = maxStamina;
	health = maxHealth;

}

void Player::CheckIfLevelUp()
{
	if (xp > xpNeed) {
		level++;
		maxHealth = maxHealth * 1.05;
		maxStamina = maxStamina * 1.05;
		health = maxHealth;
		stamina = maxStamina;
		m_damage++;
		xpNeed = xpNeed * 2;
		CheckIfLevelUp();
	}
	//See if the parameters to level up have been met, if so, increment
	//the level and increase stats by the multiplier
}

void Player::CheckGroundType(std::string type)
{
	//See what type of ground the player is walking on, and make a decision
	//based on the ground.
}

int Player::getFish() {
	return fishNum;
}

int Player::getLevel() {
	return level;
}

float Player::getStaminaMax() {
	return maxStamina;
}
//Return stamina
float Player::getStamina()
{
	return stamina;
}

//Return staminaTimer
float Player::getStaminaTimer()
{
	return staminaTimer;
}

//Add to the staminaTimer
void Player::addStaminaTimer(float staminaTimerAdd)
{
	staminaTimer = staminaTimer + staminaTimerAdd;
}

//Set stamina to zero
void Player::setStaminaTimer()
{
	staminaTimer = 0;
}

void Player::Pickup(std::string name)
{
	if (name == "land")
	{
		stamina = stamina + maxStamina / 10;
		if (stamina >= maxStamina)
		{
			stamina = maxStamina;
		}
		xp = xp + 10;
	}
	else if (name == "sea")
	{
		fishNum = fishNum + 1;
	}
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