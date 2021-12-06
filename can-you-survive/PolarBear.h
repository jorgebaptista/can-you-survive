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
	void TakeDamage(int dam);

	//Function to get variables
	FloatRect getPosition();

	Vector2f getCenter();

	Sprite getSprite();

	bool isAlive();
	




protected:
	// The polar bears health
	int health;
	// The max health value the polar bear can have
	int maxHealth;
	
	float moveTime;

	// The current position of this polar b
	Vector2f m_Position;

	Vector2f m_Resolution;

	Sprite m_Sprite;

	Texture m_Texture;

	//The level which determines how strong the polar bear is
	int level;
	//The amount of damage the player can deal
	int damage;
};
#endif