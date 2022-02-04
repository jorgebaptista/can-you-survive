#pragma once
#include "Enemy.h"
#include "Fish.h"
#include "Player.h"
#include "Tilemap.h"
#include "FileSystem.h"
#include <list>
#include <stdexcept>

using namespace sf;

class Engine
{
public:
	Engine();

	// Run the game
	void run();

private:
};

