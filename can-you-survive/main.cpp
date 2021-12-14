#include "Enemy.h"
#include "Fish.h"
#include "Player.h"
#include "Tilemap.h"
#include "FileSystem.h"

using namespace sf;

int main() 
{
	srand(static_cast<unsigned int>(time(0)));

	// create a pointer to a new Tilemap
	Tilemap *tileMap = new Tilemap();

	// create a list of pointers to Polar bears
	std::list<PolarBear*> lpPolarBears;

	// create a pointer to player
	Player* pPlayer = new Player();

	float staminaDecrease = 1.f;

	// push player to list of polar bears

	lpPolarBears.push_back(pPlayer);

	Enemy* enemy = new Enemy();

	//TODO: Warning, use static cast unsigned??
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(VideoMode(resolution.x, resolution.y), "Can You Survive?", Style::Fullscreen);

	//Views created
	View mainView(FloatRect(0, 0, resolution.x, resolution.y));
	View hudView(FloatRect(0, 0, resolution.x, resolution.y));

	Clock clock;	

	Time gameTimeTotal;
	float gameTimeTotalFloat;
	float attackTimer;
	float eatTimer;
	attackTimer = 0;
	eatTimer = 0;
	Fish fishLand;
	Fish fishSea;

	fishLand.Spawn("land");
	fishSea.Spawn("sea");

	//Stamina Bar to display player stamina
	RectangleShape staminaBar;
	//Set initial width and height
	float staminaBarStartWidth = 200;
	float staminaBarHeight = 40;
	//Set color and position
	staminaBar.setFillColor(Color::Red);
	staminaBar.setPosition(50, 1000);

	//Health Bar to display player health
	RectangleShape healthBar;
	//Set initial width and height
	float healthBarStartWidth = 200;
	float healthBarHeight = 40;
	//Set color and position
	healthBar.setFillColor(Color::Green);
	healthBar.setPosition(50, 950);

	while (window.isOpen())
	{
		Event event;

		Time dt = clock.restart();

		gameTimeTotal += dt;

		gameTimeTotalFloat = gameTimeTotal.asSeconds();

		float dtAsSeconds = dt.asSeconds();

		while (window.pollEvent(event))
		{
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				pPlayer->moveUp();
			}
			else
			{
				pPlayer->stopUp();
			}

			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				pPlayer->moveDown();
			}
			else
			{
				pPlayer->stopDown();
			}

			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				pPlayer->moveLeft();
			}
			else
			{
				pPlayer->stopLeft();
			}

			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				pPlayer->moveRight();
			}
			else
			{
				pPlayer->stopRight();
			}
			//Eat fish
			if (Keyboard::isKeyPressed(Keyboard::E))
			{
				if (eatTimer + 0.5 < gameTimeTotalFloat) {
					pPlayer->EatFish();
					eatTimer = gameTimeTotalFloat;
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::R))
			{
				if (attackTimer + 0.5 < gameTimeTotalFloat) {
					Vector2f eCenter = enemy->getCenter();
					Vector2f pCenter = pPlayer->getCenter();
					cout << endl;
					for (int i = pCenter.x - 128; i < pCenter.x + 129; i = i + 128)
					{
						for (int j = pCenter.y - 128; j < pCenter.y + 129; j = j + 128)
						{
							cout << i << " " << j << endl;
							if (i == eCenter.x && j == eCenter.y) {
								int damage = 0;
								damage = pPlayer->Attack();
								enemy->ReduceHealth(damage);
								if (enemy->getHealth()>0) {
									damage = enemy->Attack();
									pPlayer->ReduceHealth(damage);
								}
								else {
									pPlayer->addXP(90);
								}
							}
						}
					}
					cout << eCenter.x << " " << eCenter.y << endl;
					attackTimer = gameTimeTotalFloat;
				}
			
			}
		}
		
		//Will set the stamina timer
		pPlayer->addStaminaTimer(dtAsSeconds);

		//TODO: In player class set stamina and health to 0 if they go below zero (negative)
		//Set stamina and health bar size based on stamina and health
		staminaBar.setSize(Vector2f(2 * pPlayer->getStamina(), staminaBarHeight));
		healthBar.setSize(Vector2f(2 * pPlayer->getHealth(), healthBarHeight));
		
		//TODO: move this to player class
		//Check if enough time has passed to decrease stamina or health
		if (pPlayer->getStaminaTimer() >= 1)
		{
			float decreaseAmount; 
			
			// if player is on water it decreases stamina 8 times faster
			if (pPlayer->getTerrain() == Tile::terrainType::WATER)
			{
				decreaseAmount = staminaDecrease * 8;
			}
			else
			{
				decreaseAmount = staminaDecrease;
			}

			// if player stamina is not 0 it decreases stamina, else it decreases health
			pPlayer->getStamina() > 0 ? pPlayer->StaminaDecrease(decreaseAmount) : pPlayer->ReduceHealth(decreaseAmount);

			pPlayer->setStaminaTimer();
		}

		// fish collision
		if (pPlayer->getPosition().intersects(fishSea.getPosition()))
		{
			if (!fishSea.isCollected())
			{
				pPlayer->Pickup("sea");
				//fishSea.setPosition(-1000, -1000);
				fishSea.PickedUp();
			}

		}
		else if (pPlayer->getPosition().intersects(fishLand.getPosition()))
		{
			if (!fishLand.isCollected())
			{
				pPlayer->Pickup("land");
				//fishLand.setPosition(-1000, -1000);
				fishLand.PickedUp();
			}

		}

		//Move characters
		pPlayer->Movement(dtAsSeconds, gameTimeTotalFloat);
		enemy->Movement(dtAsSeconds, gameTimeTotalFloat);

		// TODO: optimize
		// creates iterator for polar bear list
		std::list<PolarBear*>::const_iterator iter;
		// iterate through each element
		for (iter = lpPolarBears.begin(); iter != lpPolarBears.end(); iter++)
		{
			Tile* tile = tileMap->getMap()[(*iter)->getCenter().y / 128][(*iter)->getCenter().x / 128];

			(*iter)->ChangeTerrain(tile->getTerrainType());
		}


		mainView.setCenter(pPlayer->getCenter());

		window.clear(Color(135, 206, 235)); // clear the window
		window.setView(mainView);

		// TODO: need better way to draw all map, DRAW class?
		std::vector<std::vector<Tile*>> map = (tileMap->getMap());

		//TODO:
		// for each row of tiles
		for (int i = 0; i < map.size(); i++)
		{
			// for each tile on that row
			for (int j = 0; j < map[i].size(); j++)
			{
				// if the terrain type is ice
				if (map[i][j]->getTerrainType() == Tile::terrainType::ICE)
				{
					if (((rand() % 100) + 1.f) >= 99.9)
					{
						tileMap->ChangeTileTerrain(i, j, Tile::terrainType::WATER);
					}
				}

				// draw that tile
				window.draw(map[i][j]->getSprite());
			}
		}

		if (!enemy->isAlive()) {
			enemy->RemoveFromPlay();
		};
		cout << enemy->getHealth() << endl;

		pPlayer->CheckIfLevelUp();
		window.draw(pPlayer->getSprite());
		window.draw(enemy->getSprite());
		window.draw(fishSea.getSprite());
		window.draw(fishLand.getSprite());

		//HUD view used for elements that don't move
		window.setView(hudView);
		window.draw(staminaBar);
		window.draw(healthBar);
		window.display();
	}
	return 0;
}