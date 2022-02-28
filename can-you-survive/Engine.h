#pragma once
#ifndef ENGINE_H
#define ENGINE_H
#include "Enemy.h"
#include "Fish.h"
#include "Player.h"
#include "Tilemap.h"
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

	void setupUI(); // Setup all UI
	void input(); // Input implementation
	void draw();

private:
	// Set up window variables
	Vector2f m_Resolution; // To store the resolution of the screen

	RenderWindow m_Window; // main window
	// views
	View m_MainView; // main view
	View m_BlackoutView; // view for the dark screen
	View m_HudView; // HUD view

	/****** Game Properties *******/

	// enum to define state of the game
	enum class GameState { MENU, INTRO, PLAYING, END };

	// Store the current state of the game
	GameState m_State;

	// Store current year
	int year;

	// Time variables
	Time m_Time; // store total time of the game
	float m_TimeAsSeconds; // store total time as seconds
	float m_PauseTime; // time since pause

	float m_TileChangeTimer; // time to change ice to water

	float m_SeasonTimer;
	float m_WaitTimer;

	float m_FishTimer;

	//pause bool to pause the game
	bool pause;
	bool select;

	// random num variable helper
	int randnum;

	/****** Player Properties *******/

	float staminaDecrease;
	float m_AttackTimer;
	float m_EatTimer;

	/****** Enemy Properties *******/

	/*********** Set up game objects **********/

	// Create a pointer to a Tilemap object
	Tilemap* tileMap;
	// Store map bounds
	Vector2f mapBounds;

	// Create a pointer of type Player
	Player* pPlayer;

	// create a list of pointers to Polar bears
	std::list<PolarBear*> lpPolarBears;
	//create a list of pointers to fish
	std::list<Fish*> lpFish;
	// pointers to fish that will spawn in water
	std::list<Fish*> lpSeaFish;
	// ? merge conflict
	std::list<Enemy*> lpEnemy;

	// Iterators for the lists
	std::list<PolarBear*>::const_iterator iter;
	std::list<Enemy*>::const_iterator iterE;
	std::list<Fish*>::const_iterator iterF;

	std::list<Fish*>::const_iterator iterSF;

	/********** HUD *********/

	// Blackout texture and sprite
	Texture blackoutT;
	Sprite blackoutS;
	//colors used to change blackout image
	Color blackoutCDarken;
	Color blackoutCLighten;

	Font font;

	// Text for MENU m_State 
	Text playText;
	// Text for Intro m_State
	Text introText;
	//Text for end m_State
	Text loseText;

	std::stringstream playStream;
	std::stringstream aboutStream;
	std::stringstream instructionsStream;
	std::stringstream referenceStream;
	std::stringstream introStream;

	std::stringstream pauseStream;
	std::stringstream loadedStream;

	//Text for Playing m_State
	Text fishText1;
	Text fishText2;
	Text levelText1;
	Text levelText2;
	Text healthText1;
	Text healthText2;
	Text staminaText1;
	Text staminaText2;
	Text winText1;
	Text winText2;
	Text yearText1;
	Text yearText2;
	Text pauseText1;
	Text pauseText2;

	RectangleShape staminaBar; // Display player stamina
	float staminaBarStartWidth = 200; // Set initial width and height
	float staminaBarHeight = 40;

	RectangleShape healthBar;// Display player health
	float healthBarStartWidth = 200; // Set initial width and height
	float healthBarHeight = 40;
};
#endif