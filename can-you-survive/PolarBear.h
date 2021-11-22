#pragma once
#ifndef POLARBEAR_H
#define POLARBEAR_H
#include <iostream>
using namespace std;
class PolarBear 
{
public:
	//Default Constructor
	PolarBear();
	//Function to move
	virtual void Movement() = 0;
	//Function to attack
	virtual void Attack() = 0;

protected:
	// The polar bears health
	int health;
	// The max health value the polar bear can have
	int maxHealth;
	//X position variable
	int x;
	//Y position variable
	int y;
	//The level which determines how strong the polar bear is
	int level;
	//The amount of damage the player can deal
	int damage;
};
#endif