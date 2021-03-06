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

	Sprite getAttackedSprite();

	bool isAttacked();

	//Will return health
	int getHealth();

	void ChangeTerrain(Tile::terrainType terrain);
	Tile::terrainType getTerrain();

	//Will check if polar bear is alive
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

	//goal position
	float goal_PositionX;
	float goal_PositionY;

	//Polar bear sprite
	Sprite m_Sprite;

	//Polar bear texture

	Texture m_TextureUp;
	Texture m_TextureDown;
	Texture m_TextureLeft;
	Texture m_TextureRight;

	IntRect rectSourceSprite;

	//The level which determines how strong the polar bear is
	int level;
	//The amount of damage the player can deal
	int m_damage;
	Tile::terrainType m_currentTerrain;

	// control animation speed
	float m_animateTimer;

	// Control attacked animation

	Texture m_AttackedTexture;
	Sprite m_AttackedSprite;
	IntRect rectSourceAttack;

	bool m_attacked;
	float m_attackAnimTimer;
};
#endif