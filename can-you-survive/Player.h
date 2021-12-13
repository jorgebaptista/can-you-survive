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
	void StaminaDecrease(float reduce);
	//See if player has reached level up conditions
	void CheckIfLevelUp();
	//See what kind of ground the polar bear is on
	void CheckGroundType(std::string type);

	//Virtual functions to be given details
	void Movement(float elapsedTime, float totalTime);

	float getStamina();

	float getStaminaTimer();

	void setStaminaTimer();
	void setStaminaTimer(float staminaTimerAdd);

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
	float  stamina;
	// Max stamina the player can have
	float  maxStamina;
	// Gained experience points
	int xp;
	// Experience points needed to level up
	int xpNeed;
	// Number of fish consumables
	int fishNum;
	// How much the stats are increased by per level
	double multiplier;
	// Used to determine when to decrease stamina
	float staminaTimer;

	//Used to determine which way to move each movement call
	char move;
	//direction variables
	bool UpPressed;
	bool DownPressed;
	bool LeftPressed;
	bool RightPressed;
};
#endif