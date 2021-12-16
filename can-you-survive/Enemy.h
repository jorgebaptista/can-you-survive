#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include "PolarBear.h"
class Enemy :public PolarBear 
{
public:
	//Constructor
	Enemy(Vector2f position);
	//Virtual functions to be given details
	void Movement(float elapsedTime, float totalTime, Vector2f mapBounds) override;
	void MoveTowards();

protected:
	//Random number used to determine which direction to go
	int randnum;
};
#endif