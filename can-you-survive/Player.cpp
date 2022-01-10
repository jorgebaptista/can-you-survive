#include "Player.h"
//Constructor
Player::Player(Vector2f position)
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
	speed = 256;
	fishNum = 100;
	move = 'c';
	staminaTimer = 0;

	m_Position = position;
	goal_PositionX = m_Position.x;
	goal_PositionY = m_Position.y;

	UpPressed = false;
	DownPressed = false;
	LeftPressed = false;
	RightPressed = false;
}


//Movement function
void Player::Movement(float elapsedTime, float totalTime, Vector2f mapBounds)
{
	//If enough total time has passed, the player can move again
	if (moveTime <= totalTime)
	{
		//Set position to current goal position
		m_Position.x = goal_PositionX;
		m_Position.y = goal_PositionY;
		m_Sprite.setPosition(m_Position);
		//move set to c to stop movement until button is pressed.
		move = 'c';
		//Checks direction pressed to see where to move character
		if (UpPressed && !(m_Position.y - 128 < 0))
		{
			goal_PositionY = m_Position.y - 128;
			//set to U to allow continuous movement up
			move = 'U';
		}
		else if (DownPressed && m_Position.y + 128 < mapBounds.y)
		{
			goal_PositionY = m_Position.y + 128;
			//set to D to allow continuous movement down
			move = 'D';
		}
		else if (LeftPressed && !(m_Position.x - 128 < 0))
		{
			goal_PositionX = m_Position.x - 128;
			//set to L to allow continuous movement left
			move = 'L';
		}
		else if (RightPressed && m_Position.x + 128 < mapBounds.x)
		{
			goal_PositionX = m_Position.x + 128;
			//set to R to allow continuous movement right
			move = 'R';
		}
		//move not being c means that a movement has been registered
		if (move != 'c')
		{
			//moveTime will be totalTime plus a certain amount to keep movement going the same way for a while.
			moveTime = totalTime + 0.5;
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

//Add health to the player
void Player::addHealth(float h) 
{
	health = health + h;
	//if health exceeds the max, set it to maxHealth
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

//Restore health and stamina when player hibernates, fish consumed and used 
void Player::Hibernate() 
{
	stamina = maxStamina;
	health = maxHealth;
	xp = fishNum * 10;
	fishNum = 0;
}
//Check if the player has gained enough xp to level up.
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
		//Check level up again incase another level up condition is already met
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

//Return fishNum variable
int Player::getFish() {
	return fishNum;
}

//Return player level
int Player::getLevel() {
	return level;
}

//Return maximum stamina
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

//Check if player has picked up a fish, and what kind
void Player::Pickup(std::string name)
{
	//Land fish effects apply instantly
	if (name == "land")
	{
		//Stamina restoration is based on maximum stamina, the higher the max, the more stamina restored
		stamina = stamina + maxStamina / 10;
		//If stamina restoration increases it to more than the max, set stamina to max
		if (stamina >= maxStamina)
		{
			stamina = maxStamina;
		}
		xp = xp + 10;
	}
	//Sea fish are stored for later use
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