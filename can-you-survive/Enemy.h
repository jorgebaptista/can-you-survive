#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include "PolarBear.h"
class Enemy :public PolarBear {
public:
	//Constructor
	Enemy();
	//Virtual functions to be given details
	void Movement();
};
#endif