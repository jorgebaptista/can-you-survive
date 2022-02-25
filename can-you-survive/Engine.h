#pragma once
#ifndef ENGINE_H
#define ENGINE_H
#include "Enemy.h"
#include "Fish.h"
#include "Player.h"
#include "Tilemap.h"
#include "TextureHolder.h"
#include <sstream>
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
	// Set up window variables
	Vector2f m_Resolution; // To store the resolution of the screen

	RenderWindow m_Window; // main window
	// views
	View m_MainView; // main view
	View m_BlackoutView; // view for the dark screen
	View m_HudView; // HUD view

	// enum to define state of the game
	enum class GameState { MENU, INTRO, PLAYING, END };

	// Store the current state of the game
	GameState m_State;

	// Set up game objects

	// create a pointer to a new Tilemap
	Tilemap* tileMap;
	// Store map bounds
	Vector2f mapBounds;

	// Create a pointer of type Player
	Player* pPlayer;

	// create a list of pointers to Polar bears
	std::list<PolarBear*> lpPolarBears;
	//create a list of pointers to fish
	std::list<Fish*> lpFish;
	// ? merge conflict
	std::list<Enemy*> lpEnemy;


	// Store current year
	int year;
};
#endif