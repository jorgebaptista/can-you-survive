#include "Tilemap.h"
//Constructor
Tilemap::Tilemap()
{
	std::ifstream mapFile("map.txt"); // open map text file

	Vector2f tilePosition (0, 0); // first tile position at 0, 0

	// if text file exists
	if (mapFile.is_open())
	{
		std::string line; // create a blank line to store each line of the map file

		int row = 0; // starts on row 0

		// for each line in the text file
		for (line; getline(mapFile, line);)
		{
			map.push_back(std::vector<Tile*>()); // push back a new vector of tiles

			m_bounds.y++;

			// for each character in that string
			for (char& t : line)
			{
				Tile::terrainType terrain = Tile::terrainType::SNOW; //default
				
				// each character represents a specific terrain type
				switch (t)
				{
				case '0':
					terrain = Tile::terrainType::SNOW;
					break;
				case '1':
					terrain = Tile::terrainType::ICE;
					break;
				case '2':
					terrain = Tile::terrainType::WATER;
					break;
				default:
					std::cout << "No terrain type for character: " << t << "at position x: " << tilePosition.x << " y: " << tilePosition.y; // debug
					break;
				}

				Tile* tile = new Tile(tilePosition, terrain); // create a new tile

				tilePosition = Vector2f(tilePosition.x + 128, tilePosition.y); // increment next tile position by the size of last tile

				map[row].push_back(tile); // push new tile into vector of tiles
			}
			tilePosition = Vector2f(0, tilePosition.y + 128); // increment next tile position by the size of last tile
			row++; // increment row
		}

		m_bounds.x = line.size();
	}
	else std::cout << "Cannot find file."; //debug can't find file

	m_bounds.x *= 128;
	m_bounds.y *= 128;
}

std::vector<std::vector<Tile*>> Tilemap::getMap()
{
	return map; //TODO: need better map drawing system
}

void Tilemap::ChangeTileTerrain(int y, int x, terrainType terrain)
{
	map[y][x]->ChangeType(terrain);
}

Vector2f Tilemap::getMapBounds()
{
	return m_bounds;
}
