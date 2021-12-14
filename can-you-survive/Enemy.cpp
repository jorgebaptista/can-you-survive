#include "Enemy.h"
//Constructor
Enemy::Enemy()
{
	srand(static_cast<unsigned int>(time(0)));
	health = 100;
	maxHealth = 100;
	level = 1;
	m_damage = 2;
	speed = 128;
	m_Position.x = 256;
	m_Position.y = 128;
	goal_PositionX = m_Position.x;
	goal_PositionY = m_Position.y;
	m_Sprite.setPosition(m_Position);
}

void Enemy::Movement(float elapsedTime, float totalTime)
{
	//Decide where to move randomly, unless player is within sight,
	//in which case, attempt to move to player.

	//Check if enough time has passed to allow movement
	if (moveTime <= totalTime)
	{
		m_Position.x = goal_PositionX;
		m_Position.y = goal_PositionY;
		m_Sprite.setPosition(m_Position);

		//Calculate a random number, number isn't changed until total run time reaches certain value;
		randnum = rand() % 4 + 1;
		//moveTime will be totalTime plus a certain amount to keep movement going the same way for a while.
		moveTime = totalTime + 1;

		if (randnum == 1)
		{
			//go up
			goal_PositionY = m_Position.y - 128;
		}
		if (randnum == 2)
		{
			//go down
			goal_PositionY = m_Position.y + 128;
		}
		if (randnum == 3)
		{
			//go left
			goal_PositionX = m_Position.x - 128;
		}
		if (randnum == 4)
		{
			//go right
			goal_PositionX = m_Position.x + 128;
		}

	}

	if (randnum == 1)
	{
		//go up
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
	if (randnum == 2)
	{
		//go down
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
	if (randnum == 3)
	{
		//go left
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
	if (randnum == 4)
	{
		//go right
		if (m_Position.x < goal_PositionX) 
		{
			m_Position.x += speed * elapsedTime;
			m_Sprite.setRotation(0);
		}
		else 
		{
			m_Position.x = goal_PositionX;
		}
	}

	//Depending on number, change position
	

	m_Sprite.setPosition(m_Position);
}
