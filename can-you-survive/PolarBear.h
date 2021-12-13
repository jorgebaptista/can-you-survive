#pragma once
#ifndef POLARBEAR_H
#define POLARBEAR_H
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;

class PolarBear
{
public:
	//Default Constructor
	PolarBear();
	//Function to move
	virtual void Movement(float elapsedTime, float totalTime) = 0;
	//virtual sf::Vector2f Movement()=0;
	//Function to attack
	void Attack();
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

	//Will check if polar bear is alive
	//TODO: isalive?
	//bool isAlive();

protected:
	// The polar bears health
	int health;
	// The max health value the polar bear can have
	int maxHealth;

	// Variable used to store when the object can move again
	float moveTime;

	// The current position of this polar bear
	Vector2f m_Position;

	Vector2f m_Resolution;



	//Polar bear sprite
	Sprite m_Sprite;

	//Polar bear texture
	Texture m_Texture;

	//The level which determines how strong the polar bear is
	int level;
	//The amount of damage the player can deal
	int damage;
};
#endif