#pragma once
#ifndef FISH_H
#define FISH_H
#include "Collectable.h"

class Fish : public Collectable {
public:
	//Constructor
	Fish();
	//Return the type of fish
	string getType();

private:
	//The type of fish
	string type;
};
#endif