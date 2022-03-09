#include "Engine.h"

Engine::Engine()
{
	/***** Game Window and Views *****/

	// Get the width and height of the screen and apply it  to x and y of the resolution variable.
	m_Resolution.x = VideoMode::getDesktopMode().width;
	m_Resolution.y = VideoMode::getDesktopMode().height;

	// Create the m_Window with a title and in full screen and store it in the variable
	m_Window.create(VideoMode(m_Resolution.x, m_Resolution.y), "Can You Survive?", Style::Fullscreen);

	/** Setup the views **/
	// Main view
	m_MainView.reset(FloatRect(0, 0, m_Resolution.x, m_Resolution.y));
	// Blackout view
	m_BlackoutView.reset(FloatRect(0, 0, m_Resolution.x, m_Resolution.y));
	// HUD view
	m_HudView.reset(FloatRect(0, 0, m_Resolution.x, m_Resolution.y));

	// Initial m_State of game is Paused
	m_State = GameState::MENU;

	/***** Game Properties Set up *****/

	// timers
	m_TimeAsSeconds = 0;
	m_PauseTime = 0;
	m_TileChangeTimer = 0;
	m_SeasonTimer = 0;
	m_WaitTimer = 0;

	m_FishTimer = 0;

	// Pause booleans
	pause = false;
	select = false;

	randnum = 0;

	year = 1; // Set initial year to 1

	// Point tilemap to a new object
	tileMap = new Tilemap(year);

	// Save map boundaries for future use such as camera and player block
	mapBounds = tileMap->getMapBounds();

	/***** Characters Properties Set up *****/

	pPlayer = nullptr;

	staminaDecrease = 2.f;
	m_AttackTimer = 0;
	m_EatTimer = 0;

	// Create a stream object and open objects.txt file
	std::ifstream objectFile("objects.txt");

	// Open the text file
	if (objectFile.is_open())
	{
		Vector2f objectPosition(0, 0); // first tile position at 0, 0

		std::string line; // Create a string to access each line of the document

		int row = 0; // first row

		// Iterate through the lines of the text file
		for (line; getline(objectFile, line);)
		{
			// If the object position is outside map bounds on Y
			if (objectPosition.y > mapBounds.y)
			{
				// Display error to console
				std::cout << "Row size of objects.txt file cannot be greater than bounds of map.\n";
				return; // stop program
			}
			// For each letter in this line
			for (char& t : line)
			{
				// If the object position is outside the map bounds on X
				if (objectPosition.x > mapBounds.x)
				{
					// Displayer error to console
					std::cout << "Column size of objects.txt file cannot be greater than bounds of map.\n";
					return; // stop the program
				}
				// Switch character check if it's....
				switch (t)
				{
					// If it's the player
				case '1':
					// If player is pointing to a null pointer, i.e., no player yet
					if (pPlayer == nullptr)
					{
						// Create a new player and point to it
						pPlayer = new Player(objectPosition);
						// push player to list of polar bears
						lpPolarBears.push_back(pPlayer);
					}
					// If there is already a player created
					else
					{
						// Displayer an error and stop the program.
						std::cout << "There can only be one player. Please check objects.txt file, there shouldn't be more than one 1 char.\n";
						return;
					}
					break;
					// If it's an enemy
				case '2':
					// Create a new enemy on the same position as the position in the text file
					Enemy * enemy = new Enemy(objectPosition);
					lpPolarBears.push_back(enemy); // push it to the polar bear list
					lpEnemy.push_back(enemy); // push it to the enemy list

					break;
				}
				// next tile to the right (each tile is 128 pixels)
				objectPosition.x += 128;
			}
			// Return to the left most tile and one row down
			objectPosition = Vector2f(0, objectPosition.y + 128);
		}
	}
	else
	{
		// If it can't find the objects.txt file, print an error and close the program
		std::cout << "Cannot find objects.txt file. Please create a file with objects (player, enemies, collectibles, etc)"; //debug can't find file
		return;
	}

	// Close the object
	objectFile.close();

	//fill pointers with fish
	for (int i = 0; i < 5; i++)
	{
		Fish* fishLand = new Fish();
		fishLand->Spawn("land");
		lpFish.push_back(fishLand);
	}

	// Fill sea fish list with some fish initially
	for (int i = 0; i < 10; i++)
	{
		Fish* fishSea = new Fish(); // create new fish object
		fishSea->Spawn("sea"); // spawn it
		fishSea->setActive(false); // disable it 
		lpSeaFish.push_back(fishSea); // push it into list
	}

	setupUI();

}

void Engine::run()
{
	Clock clock;

	//Start of while loop, runs game while window is open
	while (m_Window.isOpen())
	{
		Time dt = clock.restart();
		float dtAsSeconds = dt.asSeconds();

		//Check if pause variable has been made false, if so, increase gameTimeTotal
		if (pause == false)
		{
			m_Time += dt;

			m_TimeAsSeconds = m_Time.asSeconds();
		}
		if (pause == false && m_State == GameState::PLAYING)
		{
			m_SeasonTimer = m_SeasonTimer + dtAsSeconds;
		}

		//Constantly increment pauseTimeTotal to pause and unpause game
		m_PauseTime += dt.asSeconds();

		input(); // Input implementation

		if (m_State == GameState::PLAYING)
		{
			//Season timer will change blackout sprite to be less opaque, darkening the screen
			if (m_SeasonTimer > 30)
			{
				blackoutS.setColor(blackoutCDarken);
			}
			//blackout sprite will be set to opaque, lightening the screen
			else
			{
				blackoutS.setColor(blackoutCLighten);
			}
			//Will set the stamina timer
			pPlayer->addStaminaTimer(dtAsSeconds);

			//Set stamina and health bar size based on stamina and health
			staminaBar.setSize(Vector2f(2 * pPlayer->getStamina(), staminaBarHeight));
			healthBar.setSize(Vector2f(2 * pPlayer->getHealth(), healthBarHeight));

			//Check if enough time has passed to decrease stamina or health
			if (pPlayer->getStaminaTimer() >= 1 && pause == false)
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

				//Stamina percent used to determine if player regens health
				float staminaPercent = 0;
				staminaPercent = (pPlayer->getStamina() / pPlayer->getStaminaMax()) * 100;

				if (staminaPercent > 80)
				{
					pPlayer->addHealth(10);
				}

				// if player stamina is not 0 it decreases stamina, else it decreases health
				pPlayer->getStamina() > 0 ? pPlayer->StaminaDecrease(decreaseAmount) : pPlayer->ReduceHealth(decreaseAmount);
				pPlayer->setStaminaTimer();
			}

			// fish collision
			//Scanning through fish list to determine which fish was found
			for (iterF = lpFish.begin(); iterF != lpFish.end(); iterF++)
			{
				if (pPlayer->getPosition().intersects((*iterF)->getPosition()))
				{
					pPlayer->Pickup("land");
					(*iterF)->setPosition(-1000, -1000);
				}
			}

			for (iterSF = lpSeaFish.begin(); iterSF != lpSeaFish.end(); iterSF++)
			{
				if (pPlayer->getPosition().intersects((*iterSF)->getPosition()))
				{
					pPlayer->Pickup("sea");
					(*iterSF)->setActive(false);
					(*iterSF)->setPosition(-1000, -1000);
				}
			}

			// iterate through each element
			if (pause == false)
			{
				for (iter = lpPolarBears.begin(); iter != lpPolarBears.end(); iter++)
				{
					Tile* tile = tileMap->getMap()[(*iter)->getCenter().y / 128][(*iter)->getCenter().x / 128];

					(*iter)->ChangeTerrain(tile->getTerrainType());
				}
			}
			/****************************  CAMERA  *******************************/

			// calculate where camera will be centered
			Vector2f cameraCenter = m_MainView.getCenter();

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

			// Set main view center to be same as the above calculation
			m_MainView.setCenter(cameraCenter);

			// Clear the screen and set the current view to Main View
			m_Window.clear(Color(135, 206, 235)); // clear the m_Window
			m_Window.setView(m_MainView);

			// get the minimum camera view by dividing the width and height of the screen 
			int minCameraViewX = cameraCenter.x - VideoMode::getDesktopMode().width / 2;
			int minCameraViewY = cameraCenter.y - VideoMode::getDesktopMode().height / 2;

			int maxCameraViewX = (cameraCenter.x + VideoMode::getDesktopMode().width / 2) + 256;
			int maxCameraViewY = (cameraCenter.y + VideoMode::getDesktopMode().height / 2) + 256;

			// Limit the maximum and minimum values to not be greater 
			// or lesser than the actual boundaries of the map
			if (minCameraViewX < 0) minCameraViewX = 0;
			if (minCameraViewY < 0) minCameraViewY = 0;

			if (maxCameraViewX > mapBounds.x) maxCameraViewX = mapBounds.x;
			if (maxCameraViewY > mapBounds.y) maxCameraViewY = mapBounds.y;


			for (iterE = lpEnemy.begin(); iterE != lpEnemy.end(); ++iterE)
			{

				if ((*iterE)->getCenter().y > minCameraViewY && (*iterE)->getCenter().y < maxCameraViewY
					&& (*iterE)->getCenter().x > minCameraViewX && (*iterE)->getCenter().x < maxCameraViewX)
				{

					(*iterE)->MoveTowards(dtAsSeconds, m_TimeAsSeconds, pPlayer->getCenter());
				}
			}

			//Move characters
			if (pause == false)
			{
				for (iter = lpPolarBears.begin(); iter != lpPolarBears.end(); ++iter)
				{
					(*iter)->Movement(dtAsSeconds, m_TimeAsSeconds, mapBounds);
				}
			}

			std::vector<std::vector<Tile*>> map = (tileMap->getMap());

			if (pause == false)
			{
				for (int i = 0; i < mapBounds.y / 128; i++)
				{
					// for each tile on that row
					for (int j = 0; j < mapBounds.x / 128; j++)
					{
					// if tile is water
						if (map[i][j]->getTerrainType() == Tile::terrainType::WATER)
						{
							// every 2 seconds
							if (m_FishTimer + 4 < m_TimeAsSeconds)
							{
								// chance to spawn on this tile
								if ((rand() % 20) >= 18)
								{
									for (iterSF = lpSeaFish.begin(); iterSF != lpSeaFish.end(); iterSF++)
									{
										if (!((*iterSF)->getActive()))
										{
											(*iterSF)->setPosition(j * 128, i * 128);
											(*iterSF)->setActive(true);

											break;
										}
									}
									m_FishTimer = m_TimeAsSeconds;
								}
							}
						}

						// if the terrain type is ice
						if (map[i][j]->getTerrainType() == Tile::terrainType::ICE)
						{
							// random chance to turn to water
							if (((rand() % 100) + 1.f) >= 99.9)
							{
								// every 0.4 seconds
								if (m_TileChangeTimer + 0.4 < m_TimeAsSeconds)
								{
									// change a ice tile to water
									tileMap->ChangeTileTerrain(i, j, Tile::terrainType::WATER);
									m_TileChangeTimer = m_TimeAsSeconds;
								}
							}
						}
					}
				}
			}

			// for each row of tiles
			for (int i = (minCameraViewY / 128); i < maxCameraViewY / 128; i++)
			{
				// for each tile on that row
				for (int j = minCameraViewX / 128; j < maxCameraViewX / 128; j++)
				{
					// draw that tile
					m_Window.draw(map[i][j]->getSprite());
				}
			}

			iterE = lpEnemy.begin();
			//While loop, will check if enemy has died and will respawn them, will also drop fish on land
			while (iterE != lpEnemy.end())
			{
				if (!(*iterE)->isAlive())
				{

					for (iterF = lpFish.begin(); iterF != lpFish.end(); iterF++)
					{
						//Checks to see if the fish has already been placed, if not, place the fish and break the loop
						if (((*iterF)->getCenter().x < -0) && (*iterF)->getType() == "land")
						{

							(*iterF)->setPosition((*iterE)->getCenter().x, (*iterE)->getCenter().y);
							break;
						}

					}

					//calculate new spawn location for enemy
					randnum = rand() % 4 + 1;
					int x = randnum;
					randnum = rand() % 4 + 1;
					int y = randnum;
					(*iterE)->Spawn(100, 100, year, 3, x * 128, y * 128);
				}
				else
				{
					++iterE;
				}
				//Check if the player has died
				if (!pPlayer->isAlive())
				{
					m_State = GameState::END;
				}
			}
		}

		draw();
		m_Window.display();
	}
}
