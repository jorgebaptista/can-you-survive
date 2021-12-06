#include "Enemy.h"
//Constructor
Enemy::Enemy() {
	srand(static_cast<unsigned int>(time(0)));
	health = 100;
	maxHealth = 100;
	level = 1;
	damage = 5;
}

void Enemy::Movement(float elapsedTime, float totalTime) {
	//Decide where to move randomly, unless player is within sight,
	//in which case, attempt to move to player.
	if(moveTime<=totalTime){
		randnum = rand() % 4 + 1;
		moveTime = totalTime + 1;
		std::cout << "Help" << std::endl;
		std::cout << totalTime << std::endl;
		std::cout << elapsedTime << std::endl;
	}
	
	if (randnum == 1) {
		m_Position.y -= 100 * elapsedTime;
		m_Sprite.setRotation(270);
		std::cout << totalTime << std::endl;
		std::cout << elapsedTime << std::endl;
		
	}
	if (randnum == 2) {
		m_Position.y += 100 * elapsedTime;
		m_Sprite.setRotation(90);
		std::cout << totalTime << std::endl;
		std::cout << elapsedTime << std::endl;
		
	}
	if (randnum == 3) {
		m_Position.x -= 100 * elapsedTime;
		m_Sprite.setRotation(180);
		std::cout << totalTime << std::endl;
		std::cout << elapsedTime << std::endl;
		
	}
	if (randnum == 4) {
		m_Position.x += 100 * elapsedTime;
		m_Sprite.setRotation(0);
		
	}

	m_Sprite.setPosition(m_Position);
}
