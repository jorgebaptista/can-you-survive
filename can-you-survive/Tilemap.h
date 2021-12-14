#pragma once
#ifndef TILEMAP_H
#define TILEMAP_H
#include "Tile.h"
#include <iostream>
#include <fstream>
#include <list>

using namespace sf;

class Tilemap : public Tile 
{
public:
	Tilemap();

	std::vector<std::vector<Tile*>> getMap();

	//void LoadMap();

	void ChangeTileTerrain(int x, int y, terrainType terrain);

protected:
	std::vector<std::vector<Tile*>> map;
};
#endif