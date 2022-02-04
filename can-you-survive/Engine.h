#pragma once
#ifndef ENGINE_H
#define ENGINE_H
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
	Engine(); // Constructor

	// Run the game
	void run();

private:
	Vector2f m_Resolution;

	RenderWindow m_Window;

	View m_MainView;
	View m_BlackoutView;
	View m_HudView;

	// enum to define state of the game
	enum class GameState { PAUSED, INTRO, PLAYING, END };

	// Store the current state of the game
	GameState m_State;

	/***** TO ORGANIZE ****/
	// TODO: Organize

	// Store current year
	int year;

	// create a pointer to a new Tilemap
	Tilemap* tileMap;

	// Store map bounds
	Vector2f mapBounds;

	// create a list of pointers to Polar bears
	std::list<PolarBear*> lpPolarBears;

	//create a list of pointers to fish
	std::list<Fish*> lpFish;
};
#endif

