#pragma once
#ifndef POLARBEAR_H
#define POLARBEAR_H
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

class PolarBear 
{
public:
	//Default Constructor
	PolarBear();
	//Function to move
	virtual void Movement() = 0;
	//virtual sf::Vector2f Movement()=0;
	//Function to attack
	void Attack();
	//Function to receive damage
	void TakeDamage(int dam);

	//Function to get variables
	sf::Vector2f getPosition();

	bool isAlive();

protected:
	// The polar bears health
	int health;
	// The max health value the polar bear can have
	int maxHealth;
	// The current position of this polar b
	sf::Vector2f m_Position;
	//The level which determines how strong the polar bear is
	int level;
	//The amount of damage the player can deal
	int damage;
};
#endif