#include "Enemy.h"
//Constructor
Enemy::Enemy()
{
	srand(static_cast<unsigned int>(time(0)));
	health = 100;
	maxHealth = 100;
	level = 1;
	damage = 5;
}

void Enemy::Movement(float elapsedTime, float totalTime)
{
	//Decide where to move randomly, unless player is within sight,
	//in which case, attempt to move to player.

	//Check if enough time has passed to allow movement
	if (moveTime <= totalTime)
	{

		//Calculate a random number, number isn't changed until total run time reaches certain value;
		randnum = rand() % 4 + 1;
		//moveTime will be totalTime plus a certain amount to keep movement going the same way for a while.
		moveTime = totalTime + 1;
	}

	//Depending on number, change position
	if (randnum == 1)
	{
		//go up
		m_Position.y -= 100 * elapsedTime;
		m_Sprite.setRotation(270);
	}
	if (randnum == 2)
	{
		//go down
		m_Position.y += 100 * elapsedTime;
		m_Sprite.setRotation(90);
	}
	if (randnum == 3)
	{
		//go left
		m_Position.x -= 100 * elapsedTime;
		m_Sprite.setRotation(180);
	}
	if (randnum == 4)
	{
		//go right
		m_Position.x += 100 * elapsedTime;
		m_Sprite.setRotation(0);
	}

	m_Sprite.setPosition(m_Position);
}
