#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "PolarBear.h"

//using namespace sf;

class Player : public PolarBear {
public:
	//Default Constructor
	Player();
	//Reduce stamina function
	void StaminaDecrease(int reduce);
	//See if player has reached level up conditions
	void CheckIfLevelUp();
	//See what kind of ground the polar bear is on
	void CheckGroundType(std::string type);

	//Virtual functions to be given details
	void Movement(float elapsedTime, float totalTime);

	// Moving functions
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	// Stopping functions
	void stopLeft();
	void stopRight();
	void stopUp();
	void stopDown();

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

	char move;
	//direction variables
	bool UpPressed;
	bool DownPressed;
	bool LeftPressed;
	bool RightPressed;
};
#endif