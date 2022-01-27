#include "Enemy.h"
//Constructor
Enemy::Enemy(Vector2f position)
{
	health = 100;
	maxHealth = 100;
	level = 1;
	m_damage = 2;
	speed = 128;

	m_Position = position;
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
				//Check if going down goes outside the map
				if (m_Position.y + speed > mapBounds.y)
				{
					// generate a new num
					randnum = randnum = rand() % 4 + 1;
				}
				// if it doesn't go outside of map then break while loop with bool
				else canMove = true;
				break;
			case 3:
				//Check if going left goes outside map
				if (m_Position.x - speed < 0)
				{
					// generate a new num
					randnum = randnum = rand() % 4 + 1;
				}
				// if it doesn't go outside of map then break while loop with bool
				else canMove = true;
				break;
			case 4:
				//Check if going right goes outside map
				if (m_Position.x + speed > mapBounds.x)
				{
					// generate a new num
					randnum = randnum = rand() % 4 + 1;
				}
				// if it doesn't go outside of map then break while loop with bool
				else canMove = true;
				break;
			default:
				break;
			}
		}

		//moveTime will be totalTime plus a certain amount to keep movement going the same way for a while.
		moveTime = totalTime + 1;

		//Set goal position based on randnum
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

	//move based on randnum
	if (randnum == 1)
	{
		//go up
		if (m_Position.y > goal_PositionY)
		{
			m_Position.y -= speed * elapsedTime;
			m_Sprite.setRotation(270);
		}
		//Used to ensure character doesn't move past boundry
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
		//Used to ensure character doesn't move past boundry
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
		//Used to ensure character doesn't move past boundry
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
		//Used to ensure character doesn't move past boundry
		else
		{
			m_Position.x = goal_PositionX;
		}
	}

	//Depending on number, change position


	m_Sprite.setPosition(m_Position);
}

//Used by enemy to track player
void Enemy::MoveTowards(float elapsedTime, float totalTime, Vector2f pPosition)
{
	//Used to measure distance from player
	Vector2f distance;
	distance.x = 0;
	distance.y = 0;
	if (moveTime <= totalTime)
	{
		//set position to goal position
		m_Position.x = goal_PositionX;
		m_Position.y = goal_PositionY;
		m_Sprite.setPosition(m_Position);
		//Determine distance to player
		if (m_Position.x < pPosition.x)
		{
			distance.x = pPosition.x - m_Position.x;
		}
		else
		{
			distance.x = m_Position.x - pPosition.x;
		}
		if (m_Position.y < pPosition.y)
		{
			distance.y = pPosition.y - m_Position.y;
		}
		else
		{
			distance.y = m_Position.y - pPosition.y;
		}


		//Check used to make sure the enemy stops moving at the player
		if ((distance.x < 127 && distance.y < 255) || (distance.x < 255 && distance.y < 127))
		{
			randnum = 0;
			moveTime = totalTime + 1;
		}
		//Determine where enemy should move
		else {
			if (distance.x > distance.y)
			{
				if (m_Position.x < pPosition.x)
				{
					randnum = 4;
					goal_PositionX = m_Position.x + speed;
				}
				else
				{
					randnum = 3;
					goal_PositionX = m_Position.x - speed;
				}
				moveTime = totalTime + 1;
			}

			else if (distance.x < distance.y)
			{
				if (m_Position.y < pPosition.y)
				{
					randnum = 2;
					goal_PositionY = m_Position.y + speed;

				}
				else
				{
					randnum = 1;
					goal_PositionY = m_Position.y - speed;
				}
				moveTime = totalTime + 1;
			}
			//Else to move enemy if x distance and y distance are the same
			else {
				if (m_Position.y < pPosition.y)
				{
					randnum = 2;
					goal_PositionY = m_Position.y + speed;

				}
				else
				{
					randnum = 1;
					goal_PositionY = m_Position.y - speed;
				}
				moveTime = totalTime + 1;
			}
			
		}
		//std::cout << randnum << std::endl;

	}
}

void Enemy::LevelUp() {
	level++;
	float multi = pow(1.08, level);
	health = maxHealth * multi;
	maxHealth = maxHealth * multi;
	m_damage = m_damage * multi;
}