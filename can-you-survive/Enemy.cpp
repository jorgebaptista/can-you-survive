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

	// load all correct textures
	m_TextureUp.loadFromFile("graphics/enemy/up.png");
	m_TextureDown.loadFromFile("graphics/enemy/down.png");
	m_TextureLeft.loadFromFile("graphics/enemy/left.png");
	m_TextureRight.loadFromFile("graphics/enemy/right.png");

	// create rect to navigate through the spriresheet
	rectSourceSprite = sf::IntRect(0, 0, 64, 64);

	m_Sprite.setTexture(m_TextureRight);
	m_Sprite = Sprite(m_TextureRight, rectSourceSprite);

	m_Sprite.setOrigin(32, 32);
	m_Sprite.setPosition(m_Position);

	m_animateTimer = 0;
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

	// add the delta time to animate timer 
	m_animateTimer += elapsedTime;

	//move based on randnum
	if (randnum == 1)
	{
		//go up
		if (m_Position.y > goal_PositionY)
		{
			m_Position.y -= speed * elapsedTime;

			// every 0.2 seconds
			if (m_animateTimer > 0.2f)
			{
				// if rect is at the right most of the sprite sheet reset it 
				if (rectSourceSprite.left == 320) rectSourceSprite.left = 0;
				// else just jump to the right one
				else rectSourceSprite.left += 64;

				// set the sprite to the correct texture and rect properties
				m_Sprite = Sprite(m_TextureUp, rectSourceSprite);

				// set the animate timer back to 0
				m_animateTimer = 0;
			}
		}
		//Used to ensure character doesn't move past boundary
		else
		{
			m_Position.y = goal_PositionY;

			// reset the sprite and rect back to first one not animated
			rectSourceSprite = sf::IntRect(0, 0, 64, 64);
			m_Sprite = Sprite(m_TextureUp, rectSourceSprite);
		}
	}
	if (randnum == 2)
	{
		//go down
		if (m_Position.y < goal_PositionY)
		{
			m_Position.y += speed * elapsedTime;

			// every 0.2 seconds
			if (m_animateTimer > 0.2f)
			{
				// if rect is at the right most of the sprite sheet reset it 
				if (rectSourceSprite.left == 320) rectSourceSprite.left = 0;
				// else just jump to the right one
				else rectSourceSprite.left += 64;

				// set the sprite to the correct texture and rect properties
				m_Sprite = Sprite(m_TextureDown, rectSourceSprite);

				// set the animate timer back to 0
				m_animateTimer = 0;
			}
		}
		//Used to ensure character doesn't move past boundary
		else
		{
			m_Position.y = goal_PositionY;

			// reset the sprite and rect back to first one not animated
			rectSourceSprite = sf::IntRect(0, 0, 64, 64);
			m_Sprite = Sprite(m_TextureDown, rectSourceSprite);
		}
	}
	if (randnum == 3)
	{
		//go left
		if (m_Position.x > goal_PositionX)
		{
			m_Position.x -= speed * elapsedTime;

			// every 0.2 seconds
			if (m_animateTimer > 0.2f)
			{
				// if rect is at the right most of the sprite sheet reset it 
				if (rectSourceSprite.left == 320) rectSourceSprite.left = 0;
				// else just jump to the right one
				else rectSourceSprite.left += 64;

				// set the sprite to the correct texture and rect properties
				m_Sprite = Sprite(m_TextureLeft, rectSourceSprite);

				// set the animate timer back to 0
				m_animateTimer = 0;
			}
		}
		//Used to ensure character doesn't move past boundary
		else
		{
			m_Position.x = goal_PositionX;

			// reset the sprite and rect back to first one not animated
			rectSourceSprite = sf::IntRect(0, 0, 64, 64);
			m_Sprite = Sprite(m_TextureLeft, rectSourceSprite);
		}
	}
	if (randnum == 4)
	{
		//go right
		if (m_Position.x < goal_PositionX)
		{
			m_Position.x += speed * elapsedTime;

			// every 0.2 seconds
			if (m_animateTimer > 0.2f)
			{
				// if rect is at the right most of the sprite sheet reset it 
				if (rectSourceSprite.left == 320) rectSourceSprite.left = 0;
				// else just jump to the right one
				else rectSourceSprite.left += 64;

				// set the sprite to the correct texture and rect properties
				m_Sprite = Sprite(m_TextureRight, rectSourceSprite);

				// set the animate timer back to 0
				m_animateTimer = 0;
			}
		}
		//Used to ensure character doesn't move past boundary
		else
		{
			m_Position.x = goal_PositionX;

			// reset the sprite and rect back to first one not animated
			rectSourceSprite = sf::IntRect(0, 0, 64, 64);
			m_Sprite = Sprite(m_TextureRight, rectSourceSprite);
		}
	}

	//Depending on number, change position


	m_Sprite.setOrigin(32, 32);
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