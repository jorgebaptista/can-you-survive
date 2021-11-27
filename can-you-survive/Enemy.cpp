#include "Enemy.h"
//Constructor
Enemy::Enemy() {
	health = 100;
	maxHealth = 100;
	level = 1;
	damage = 5;
}

void Enemy::Movement() {
	//Decide where to move randomly, unless player is within sight,
	//in which case, attempt to move to player.
}
