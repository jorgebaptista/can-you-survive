#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "PolarBear.h"

//using namespace sf;

class Player : public PolarBear
{
public:
	//Default Constructor
	Player();
	//Reduce stamina function
	void StaminaDecrease(float reduce);

	//Add to health
	void addHealth(float h);

	//Add to xp
	void addXP(int xp);
	//See if player has reached level up conditions
	void CheckIfLevelUp();
	//See what kind of ground the polar bear is on
	void CheckGroundType(std::string type);

	//Virtual functions to be given details
	void Movement(float elapsedTime, float totalTime);

	void Hibernate();

	void EatFish();

	//Return fish total
	int getFish();

	//Return level
	int getLevel();

	//Return stamina
	float getStamina();

	//Return max stamina
	float getStaminaMax();

	//Return staminaTimer
	float getStaminaTimer();

	//Set staminaTimer to 0
	void setStaminaTimer();

	//Add time to staminaTimer
	void addStaminaTimer(float staminaTimerAdd);

	void Pickup(std::string name);
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
	float stamina;
	// Max stamina the player can have
	float maxStamina;
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