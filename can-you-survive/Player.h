#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "PolarBear.h"
class Player : public PolarBear {
public:
	//Default Constructor
	Player();
	//Reduce stamina function
	void StaminaDecrease();
	//See if player has reached level up conditions
	void CheckIfLevelUp();
	//See what kind of ground the polar bear is on
	void CheckGroundType();

	//Virtual functions to be given details
	void Movement();
	void Attack();
protected:
	// Stamina of Player
	int stamina;
	// Max stamina the player can have
	int maxStamina;
	// Gained experience points
	int xp;
	// Experience points needed to level up
	int xpNeed;
	// Number of fish consumables
	int fishNum;
	// How much the stats are increased by per level
	double multiplier;
};
#endif