#pragma once
#ifndef POLARBEAR_H
#define POLARBEAR_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Tile.h"

using namespace sf;

class PolarBear
{
public:
	//Default Constructor
	PolarBear(Vector2f position = Vector2f(128,128));
	//Function to move
	//TODO: Implement bound check here because both enemy and player uses it?
	virtual void Movement(float elapsedTime, float totalTime, Vector2f mapBounds) = 0;
	//virtual sf::Vector2f Movement()=0;
	//Function to attack
	int Attack();
	//Function to receive damage
	void ReduceHealth(int reduce);

	//Function to get variables
	FloatRect getPosition();

	//Function to get center of object 
	Vector2f getCenter();

	//Returns the sprite
	Sprite getSprite();

	//Will return health
	int getHealth();

	void ChangeTerrain(Tile::terrainType terrain);
	Tile::terrainType getTerrain();

	//Will check if polar bear is alive
	//TODO: isalive?
	bool isAlive();

	void Spawn(int h, int mh, int l, int d, float x, float y);
protected:
	// The polar bears health
	int health;
	// The max health value the polar bear can have
	int maxHealth;
	// How fast the polar bear moves
	int speed;
	// Variable used to store when the object can move again
	float moveTime;

	// The current position of this polar bear
	Vector2f m_Position;

	Vector2f m_Resolution;

	//TODO: Move to enemy class?
	//goal position
	float goal_PositionX;
	float goal_PositionY;

	//Polar bear sprite
	Sprite m_Sprite;

	//Polar bear texture
	Texture m_Texture;


	//The level which determines how strong the polar bear is
	int level;
	//The amount of damage the player can deal
	int m_damage;
	Tile::terrainType m_currentTerrain;
};
#endif