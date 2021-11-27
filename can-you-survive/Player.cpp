#include "Player.h"
//Constructor
Player::Player() {
	health = 100;
	maxHealth = 100;
	stamina = 100;
	maxStamina = 100;
	level = 1;
	multiplier = 1.05;
	xp = 0;
	xpNeed = 100;
	damage = 5;
	fishNum = 0;
}

//void Player::Movement(x, y IN, x,y OUT ) {
//	//Allow the player to move using the arrow keys
//	//use a listener, and respond with new x,y co-ord
// Get input
//}

void Player::Movement() {

}


void StaminaDecrease(int reduce) {
	//Reduce stamina a certain amount
}

void CheckIfLevelUp() {
	//See if the parameters to level up have been met, if so, increment
	//the level and increase stats by the multiplier
}

void CheckGroundType(string type) {
	//See what type of ground the player is walking on, and make a decision
	//based on the ground.
}