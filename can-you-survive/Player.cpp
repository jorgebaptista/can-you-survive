#include "Player.h"
//Constructor
Player::Player() {
	health = 100;
	maxHealth = 100;
	stamina = 100;
	maxStamina = 100;
	x = 10;
	y = 10;
	level = 1;
	multiplier = 1.05;
	xp = 0;
	xpNeed = 100;
	damage = 5;
	fishNum = 0;
}

void Player::Movement() {
	//Allow the player to move using the arrow keys
}

void Player::Attack() {
	//Allow the player to attack the opponent with a damage calculation
}

void StaminaDecrease() {
	//Reduce stamina a certain amount
}

void CheckIfLevelUp() {
	//See if the parameters to level up have been met, if so, increment
	//the level and increase stats by the multiplier
}

void CheckGroundType() {
	//See what type of ground the player is walking on, and make a decision
	//based on the ground.
}