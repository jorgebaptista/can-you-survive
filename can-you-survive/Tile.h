#pragma once
#ifndef TILE_H
#define TILE_H
#include <iostream>
using namespace std;
class Tile {
public:
	//Constructor
	Tile();
	//Function to change the type of the tile.
	void ChangeType();
protected:
	//Will be enum, specifies the tile type
	string type;
};
#endif