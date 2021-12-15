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

void Enemy::Movement(float elapsedTime, float totalTime, Vector2f mapBounds)
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

		// check if can move
		bool canMove = false;

		// if not keep looping and generating a new number
		while (!canMove)
		{
			// check direction
			switch (randnum)
			{
			// if up
			case 1:
				// if going up goes outside of map
				if (m_Position.y - speed < 0)
				{
					// generate a new num
					randnum = randnum = rand() % 4 + 1;
				}
				// if it doesn't go outside of map then break while loop with bool
				else canMove = true;
				break;
			case 2:
				if (m_Position.y + speed > mapBounds.y)
				{
					randnum = randnum = rand() % 4 + 1;
				}
				else canMove = true;
				break;
			case 3:
				if (m_Position.x - speed < 0)
				{
					randnum = randnum = rand() % 4 + 1;
				}
				else canMove = true;
				break;
			case 4:
				if (m_Position.x + speed > mapBounds.x)
				{
					randnum = randnum = rand() % 4 + 1;
				}
				else canMove = true;
				break;
			default:
				break;
			}
		}

		//moveTime will be totalTime plus a certain amount to keep movement going the same way for a while.
		moveTime = totalTime + 1;

		if (randnum == 1)
		{
			//go up
			goal_PositionY = m_Position.y - speed;
		}
		if (randnum == 2)
		{
			//go down
			goal_PositionY = m_Position.y + speed;
		}
		if (randnum == 3)
		{
			//go left
			goal_PositionX = m_Position.x - speed;
		}
		if (randnum == 4)
		{
			//go right
			goal_PositionX = m_Position.x + speed;
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

void Enemy::MoveTowards(float elapsedTime, float totalTime, Vector2f pPosition) 
{
	Vector2f distance;
	distance.x = 0;
	distance.y = 0;
	
	distance.x = m_Position.x - pPosition.x;
	distance.y = m_Position.y - pPosition.y;

	if (distance.x > distance.y) 
	{

	}

	else if (distance.x < distance.y) 
	{

	}
}