#include "Enemy.h"
#include "Fish.h"
#include "Player.h"
#include "Tilemap.h"
#include "FileSystem.h"
#include <list>
#include <stdexcept>

using namespace sf;

int main()
{
	srand(static_cast<unsigned int>(time(0)));

	std::ifstream objectFile("objects.txt");

	// create a pointer to a new Tilemap
	Tilemap* tileMap = new Tilemap();

	Vector2f mapBounds = tileMap->getMapBounds();

	// create a list of pointers to Polar bears
	std::list<PolarBear*> lpPolarBears;
	std::list<Fish*> lpFish;
	for (int i = 0; i < 5; i++) {
		Fish* fishLand = new Fish();
		fishLand->Spawn("land");
		lpFish.push_back(fishLand);

	}

	Player* pPlayer = nullptr;

	// ? merge conflict
	std::list<Enemy*> lpEnemy;
	

	//TODO: Move this repeated stuff to another class? singleton for files? tilemap has this kind of loop too
	if (objectFile.is_open())
	{
		Vector2f objectPosition(0, 0); // first tile position at 0, 0
		std::string line;

		int row = 0;

		for (line; getline(objectFile, line);)
		{
			if (objectPosition.y > mapBounds.y)
			{
				std::cout << "Row size of objects.txt file cannot be greater than bounds of map.\n";
				return 0;
			}
			for (char& t : line)
			{
				if (objectPosition.x > mapBounds.x)
				{
					std::cout << "Column size of objects.txt file cannot be greater than bounds of map.\n";
					return 0;
				}
				
				switch (t)
				{
				case '1':
					// create a pointer to a new player
					if (pPlayer == nullptr)
					{
						pPlayer = new Player(objectPosition);
						// push player to list of polar bears
						lpPolarBears.push_back(pPlayer);
					}
					else
					{
						std::cout << "There can only be one player. Please check objects.txt file, there shouldn't be more than one 1 char.\n";
						return 0;
					}
					break;
				case '2':
					Enemy * enemy = new Enemy(objectPosition);
					lpPolarBears.push_back(enemy);
					lpEnemy.push_back(enemy);

					break;
				}

				objectPosition.x += 128;
			}
			
			objectPosition = Vector2f(0, objectPosition.y + 128);
		}
	}

	else
	{
		std::cout << "Cannot find objects.txt file. Please create a file with objects (player, enemies, collectibles, etc)"; //debug can't find file
		return 0;
	}

	objectFile.close();

	float staminaDecrease = 1.f;

	//TODO: Warning, use static cast unsigned??
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(VideoMode(resolution.x, resolution.y), "Can You Survive?", Style::Fullscreen);

	//blackout
	Texture blackoutT;
	Sprite blackoutS;
	Color blackoutCDarken;
	Color blackoutCLighten;
	blackoutCDarken.a = 100;
	blackoutCLighten.a = 0;
	
	blackoutT.loadFromFile("graphics/black.png");
	blackoutS.setTexture(blackoutT);
	
	
	blackoutS.scale(4.0,4.0);

	//Views created
	View mainView(FloatRect(0, 0, resolution.x, resolution.y));
	View blackoutView(FloatRect(0, 0, resolution.x, resolution.y));
	View hudView(FloatRect(0, 0, resolution.x, resolution.y));

	Clock clock;

	Time gameTimeTotal;
	float gameTimeTotalFloat;
	float tileChangeTimer;
	float attackTimer;
	float eatTimer;
	float seasonTimer;
	tileChangeTimer = 0;
	attackTimer = 0;
	eatTimer = 0;
	seasonTimer = 0;
	Fish fishLand;
	Fish fishSea;

	fishLand.Spawn("land");
	fishSea.Spawn("sea");

	int randnum = 0; rand() % 4 + 1;
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

	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");
	fishText1.setFont(font);
	fishText1.setString("Fish : 100");
	fishText1.setCharacterSize(75);
	fishText1.setFillColor(Color::Black);
	fishText1.setPosition(1300, 900);

	fishText2.setFont(font);
	fishText2.setString("Fish : 100");
	fishText2.setCharacterSize(75);
	fishText2.setFillColor(Color::White);
	fishText2.setPosition(1295, 895);

	levelText1.setFont(font);
	levelText1.setString("Level : 1");
	levelText1.setCharacterSize(25);
	levelText1.setFillColor(Color::Black);
	levelText1.setPosition(50, 900);

	levelText2.setFont(font);
	levelText2.setString("Level : 1");
	levelText2.setCharacterSize(25);
	levelText2.setFillColor(Color::White);
	levelText2.setPosition(48, 898);

	healthText1.setFont(font);
	healthText1.setString("Health");
	healthText1.setCharacterSize(25);
	healthText1.setFillColor(Color::Black);
	healthText1.setPosition(55, 950);

	healthText2.setFont(font);
	healthText2.setString("Health");
	healthText2.setCharacterSize(25);
	healthText2.setFillColor(Color::White);
	healthText2.setPosition(53, 948);

	staminaText1.setFont(font);
	staminaText1.setString("Stamina");
	staminaText1.setCharacterSize(25);
	staminaText1.setFillColor(Color::Black);
	staminaText1.setPosition(55, 1000);

	staminaText2.setFont(font);
	staminaText2.setString("Stamina");
	staminaText2.setCharacterSize(25);
	staminaText2.setFillColor(Color::White);
	staminaText2.setPosition(53, 998);

	winText1.setFont(font);
	winText1.setString("You win!");
	winText1.setCharacterSize(100);
	winText1.setFillColor(Color::Black);
	winText1.setPosition(960, 540);

	winText2.setFont(font);
	winText2.setString("You win!");
	winText2.setCharacterSize(100);
	winText2.setFillColor(Color::White);
	winText2.setPosition(955, 535);

	yearText1.setFont(font);
	yearText1.setString("Year: 1");
	yearText1.setCharacterSize(50);
	yearText1.setFillColor(Color::Black);
	yearText1.setPosition(55, 55);

	yearText2.setFont(font);
	yearText2.setString("Year: 1");
	yearText2.setCharacterSize(50);
	yearText2.setFillColor(Color::White);
	yearText2.setPosition(53, 53);

	int maxFps = 0;
	int minFps = 50000;
	int year = 1;

	while (window.isOpen())
	{
		Event event;

		Time dt = clock.restart();

		gameTimeTotal += dt;

		gameTimeTotalFloat = gameTimeTotal.asSeconds();

		float dtAsSeconds = dt.asSeconds();

		seasonTimer = seasonTimer + dtAsSeconds;


		// debug fps

		int fps = floor(1.0f / dtAsSeconds);

		if (maxFps < fps) maxFps = fps;
		if (minFps > fps) minFps = fps;
		// CHECK FPS
		std::cout << "Fps: " << fps << " Min fps: " << minFps << " Max fps: " << maxFps << std::endl;

		while (window.pollEvent(event))
		{
			// reset fps count
			if (Keyboard::isKeyPressed(Keyboard::K))
			{
				minFps = 5000;
				maxFps = 0;
			}

			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}
			//Allow player to move using WASD
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
				if (eatTimer + 0.5 < gameTimeTotalFloat) 
				{
					pPlayer->EatFish();
					eatTimer = gameTimeTotalFloat;
				}
			}
			//Attack with R
			if (Keyboard::isKeyPressed(Keyboard::R))
			{
				if (attackTimer + 0.5 < gameTimeTotalFloat)
				{
					list<PolarBear*>::const_iterator iter;
					for (iter = lpPolarBears.begin(); iter != lpPolarBears.end(); ++iter) 
					{
						Vector2f eCenter = (*iter)->getCenter();
						std::cout << eCenter.x << " " << eCenter.y << endl;
						if (pPlayer->getCenter() != (*iter)->getCenter()) 
						{
							Vector2f pCenter = pPlayer->getCenter();
							std::cout << endl;
							for (int i = pCenter.x - 128; i < pCenter.x + 129; i = i + 128)
							{
								for (int j = pCenter.y - 128; j < pCenter.y + 129; j = j + 128)
								{
									std::cout << i << " " << j << endl;
									if (i - 1 <= eCenter.x && i + 1 >= eCenter.x && j - 1 <= eCenter.y && j + 1 >= eCenter.y)
									{
										int damage = 0;
										damage = pPlayer->Attack();
										(*iter)->ReduceHealth(damage);
										if ((*iter)->getHealth() > 0)
										{
											damage = (*iter)->Attack();
											pPlayer->ReduceHealth(damage);
										}
										else
										{
											pPlayer->addXP(90);
										}
									}
								}
							}
						}
					}
					//cout << eCenter.x << " " << eCenter.y << endl;
					attackTimer = gameTimeTotalFloat;
				}

			}
			if (Keyboard::isKeyPressed(Keyboard::Q))
			{
				if (pPlayer->getTerrain() == Tile::terrainType::SNOW && seasonTimer > 5)
				{
					pPlayer->Hibernate();
					pPlayer->CheckIfLevelUp();
					seasonTimer = 0;
					year++;

					//Attempting to reload tilemap with restored ice blocks, currently doesn't work

					/*tileMap = new Tilemap();
					float wait = 0;
					Clock clockWait;

					Time waitTotal;
					
					while (wait < 15) {

						waitTotal = clockWait.restart();
						wait += waitTotal.asSeconds();
					}
					*/
					
				}
			}
		}

		if (seasonTimer > 5) {
			blackoutS.setColor(blackoutCDarken);
		}
		else {
			blackoutS.setColor(blackoutCLighten);
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

			float staminaPercent = 0;
			staminaPercent = (pPlayer->getStamina() / pPlayer->getStaminaMax()) * 100;

			if (staminaPercent > 80) {
				pPlayer->addHealth(2);
			}
			std::cout << staminaPercent << endl;

			// if player stamina is not 0 it decreases stamina, else it decreases health
			pPlayer->getStamina() > 0 ? pPlayer->StaminaDecrease(decreaseAmount) : pPlayer->ReduceHealth(decreaseAmount);

			pPlayer->setStaminaTimer();
		}

		// fish collision
		std::list<Fish*>::const_iterator iterF;

		for (iterF = lpFish.begin(); iterF != lpFish.end(); iterF++) {
			if (pPlayer->getPosition().intersects((*iterF)->getPosition())) {
				if ((*iterF)->getType() == "land") {
					pPlayer->Pickup("land");
				}
				else if ((*iterF)->getType() == "sea") {
					pPlayer->Pickup("sea");
				}
				(*iterF)->setPosition(-1000, -1000);
				(*iterF)->PickedUp();
			}
		}




		// TODO: optimize
		// creates iterator for polar bear list
		std::list<PolarBear*>::const_iterator iter;
		std::list<Enemy*>::const_iterator iterE;
		// iterate through each element
		for (iter = lpPolarBears.begin(); iter != lpPolarBears.end(); iter++)
		{
			Tile* tile = tileMap->getMap()[(*iter)->getCenter().y / 128][(*iter)->getCenter().x / 128];

			(*iter)->ChangeTerrain(tile->getTerrainType());
		}

		/****************************  CAMERA  *******************************/

		// calculate where camera will be centered
		Vector2f cameraCenter = mainView.getCenter();

		// if player x position is less the center of screen width
		if (pPlayer->getCenter().x < (VideoMode::getDesktopMode().width / 2 - 64))
		{
			// camera center will stay there instead (as in, it will not outside the bounds of the map)
			cameraCenter.x = (VideoMode::getDesktopMode().width / 2) - 64;
		}
		// if player x position is more than the map bound width minus center of screen width 
		else if (pPlayer->getCenter().x > (mapBounds.x - VideoMode::getDesktopMode().width / 2) - 64)
		{
			// camera center will stay there instead (as in, it will not outside the bounds of the map)
			cameraCenter.x = (mapBounds.x - VideoMode::getDesktopMode().width / 2) - 64;
		}
		else
		{
			cameraCenter.x = pPlayer->getCenter().x;
		}
		// if player x position is less the center of screen height
		if (pPlayer->getCenter().y < (VideoMode::getDesktopMode().height / 2) - 64)
		{
			// camera center will stay there instead (as in, it will not outside the bounds of the map)
			cameraCenter.y = (VideoMode::getDesktopMode().height / 2) - 64;
		}
		// if player x position is more than the map bound width minus center of screen height 
		else if (pPlayer->getCenter().y > (mapBounds.y - VideoMode::getDesktopMode().height / 2) - 64)
		{
			// camera center will stay there instead (as in, it will not outside the bounds of the map)
			cameraCenter.y = (mapBounds.y - VideoMode::getDesktopMode().height / 2) - 64;
		}
		else
		{
			// else just center on player instead
			cameraCenter.y = pPlayer->getCenter().y;
		}

		mainView.setCenter(cameraCenter);

		window.clear(Color(135, 206, 235)); // clear the window
		window.setView(mainView);

		// TODO: Optimize camera view, variables ?
		int minCameraViewX = cameraCenter.x - VideoMode::getDesktopMode().width / 2;
		int minCameraViewY = cameraCenter.y - VideoMode::getDesktopMode().height / 2;

		int maxCameraViewX = (cameraCenter.x + VideoMode::getDesktopMode().width / 2) + 256;
		int maxCameraViewY = (cameraCenter.y + VideoMode::getDesktopMode().height / 2) + 256;

		if (minCameraViewX < 0) minCameraViewX = 0;
		if (minCameraViewY < 0) minCameraViewY = 0;

		if (maxCameraViewX > mapBounds.x) maxCameraViewX = mapBounds.x;
		if (maxCameraViewY > mapBounds.y) maxCameraViewY = mapBounds.y;

		// Enemy merge stuff
		for (iterE = lpEnemy.begin(); iterE != lpEnemy.end(); ++iterE)
		{
			
			if ((*iterE)->getCenter().y > minCameraViewY && (*iterE)->getCenter().y < maxCameraViewY
				&& (*iterE)->getCenter().x > minCameraViewX && (*iterE)->getCenter().x < maxCameraViewX)
			{
				
				(*iterE)->MoveTowards(dtAsSeconds, gameTimeTotalFloat, pPlayer->getCenter());
			}
		}

		//Move characters
		for (iter = lpPolarBears.begin(); iter != lpPolarBears.end(); ++iter)
		{
			(*iter)->Movement(dtAsSeconds, gameTimeTotalFloat, mapBounds);
		}

		// TODO: need better way to draw all map, DRAW class?
		std::vector<std::vector<Tile*>> map = (tileMap->getMap());

		//TODO:
		// for each row of tiles
		for (int i = (minCameraViewY / 128); i < maxCameraViewY / 128; i++)
		{
			// for each tile on that row
			for (int j = minCameraViewX / 128; j < maxCameraViewX / 128; j++)
			{
				// draw that tile
				window.draw(map[i][j]->getSprite());
			}
		}


		// TODO: Need better system to melt ice 
		for (int i = 0; i < mapBounds.y / 128; i++)
		{
			// for each tile on that row
			for (int j = 0; j < mapBounds.x / 128; j++)
			{
				// if the terrain type is ice
				if (map[i][j]->getTerrainType() == Tile::terrainType::ICE)
				{
					if (((rand() % 100) + 1.f) >= 99.9)
					{
						if (tileChangeTimer + 0.1 < gameTimeTotalFloat) {
							tileMap->ChangeTileTerrain(i, j, Tile::terrainType::WATER);
							tileChangeTimer = gameTimeTotalFloat;
						}
					}
				}
			}
		}

		int tilenumX = mapBounds.x;
		int tilenumY = mapBounds.y;
		std::cout << tilenumX / 128 << endl;
		std::cout << tilenumY / 128 << endl;

		iterE = lpEnemy.begin();
		while (iterE != lpEnemy.end())
		{
			if (!(*iterE)->isAlive())
			{
				
				for (iterF = lpFish.begin(); iterF != lpFish.end(); iterF++) {
					if (((*iterF)->getCenter().x < -0) && (*iterF)->getType() == "land") {
						
						(*iterF)->setPosition((*iterE)->getCenter().x, (*iterE)->getCenter().y);
						break;
					}
					
				}
				//int tilenumX = mapBounds.x;
				//int tilenumY = mapBounds.y;
				//cout << tilenumX / 128 << endl;
				randnum = rand() % 4 + 1;
				int x = randnum;
				randnum = rand() % 4 + 1;
				int y = randnum;
				(*iterE)->Spawn(100, 100, 1, 3, x * 128, y * 128);
			}
			else
			{
				++iterE;
			}
		}

		for (iter = lpPolarBears.begin(); iter != lpPolarBears.end(); ++iter)
		{
			window.draw((*iter)->getSprite());
		}

		for (iterF = lpFish.begin(); iterF != lpFish.end(); ++iterF) {
			window.draw((*iterF)->getSprite());
		}
		window.draw(fishSea.getSprite());
		window.draw(fishLand.getSprite());

		window.setView(blackoutView);
		window.draw(blackoutS);

		stringstream fishString;
		fishString << "Fish : " << pPlayer->getFish();
		fishText1.setString(fishString.str());
		fishText2.setString(fishString.str());

		stringstream levelString;
		levelString << "Level : " << pPlayer->getLevel();
		levelText1.setString(levelString.str());
		levelText2.setString(levelString.str());
		//HUD view used for elements that don't move

		stringstream yearString;
		yearString << "Year : " << year;
		yearText1.setString(yearString.str());
		yearText2.setString(yearString.str());

		window.setView(hudView);
		window.draw(staminaBar);
		window.draw(healthBar);
		window.draw(fishText1);
		window.draw(fishText2);
		window.draw(levelText1);
		window.draw(levelText2);
		window.draw(healthText1);
		window.draw(healthText2);
		window.draw(staminaText1);
		window.draw(staminaText2);
		window.draw(yearText1);
		window.draw(yearText2);

		//Check if player level meets win condition
		if (pPlayer->getLevel() > 4) {
			window.draw(winText1);
			window.draw(winText2);
		}

		window.display();
	}
	return 0;
}