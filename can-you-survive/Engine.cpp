#include "Engine.h"

Engine::Engine()
{
	// Get the width and height of the screen and apply it  to x and y of the resolution variable.
	m_Resolution.x = VideoMode::getDesktopMode().width;
	m_Resolution.y = VideoMode::getDesktopMode().height;

	// Create the window with a title and in full screen and store it in the variable
	m_Window.create(VideoMode(m_Resolution.x, m_Resolution.y), "Can You Survive?", Style::Fullscreen);

	/** Setup the views **/
	// Main v+iew
	m_MainView.reset(FloatRect(0, 0, m_Resolution.x, m_Resolution.y));
	// TODO: Blackout view
	m_BlackoutView.reset(FloatRect(0, 0, m_Resolution.x, m_Resolution.y));
	// HUD view
	m_HudView.reset(FloatRect(0, 0, m_Resolution.x, m_Resolution.y));

	// Initial state of game is Paused
	m_State = GameState::PAUSED;

	/***** TO ORGANIZE ****/
	// TODO: Organize
	year = 1;

	// Point tilemap to a new object
	tileMap = new Tilemap(year);

	// Save map boundaries for future use such as camera and player block
	mapBounds = tileMap->getMapBounds();

	// TODO: FISH? change to foreach?
	//fill pointers with fish
	for (int i = 0; i < 5; i++)
	{
		Fish* fishLand = new Fish();
		fishLand->Spawn("land");
		lpFish.push_back(fishLand);
	}

	// Create a stream object and open objects.txt file
	std::ifstream objectFile("objects.txt");

	//TODO: Move this repeated stuff to another class? singleton for files? tile map has this kind of loop too
	if (objectFile.is_open())
	{
		Vector2f objectPosition(0, 0); // first tile position at 0, 0

		std::string line; // Create a string to access each line of the document

		int row = 0;
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
				// Switch character check if it's
				switch (t)
				{
					//Create player
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
						return;
					}
					break;
					//Create enemy
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
		return;
	}

	objectFile.close();

}

void Engine::run()
{


	float staminaDecrease = 1.f;

	//blackout
	Texture blackoutT;
	Sprite blackoutS;
	//colors used to change blackout image
	Color blackoutCDarken;
	Color blackoutCLighten;
	blackoutCDarken.a = 100;
	blackoutCLighten.a = 0;

	//load blackout file
	blackoutT.loadFromFile("graphics/black.png");
	blackoutS.setTexture(blackoutT);

	//scale to fill screen
	blackoutS.scale(4.0, 4.0);

	Clock clock;

	//Section where timers are placed for the game
	Time gameTimeTotal;
	float gameTimeTotalFloat;
	float pauseTimeTotal;
	float tileChangeTimer;
	float attackTimer;
	float eatTimer;
	float seasonTimer;
	float waitTimer;
	pauseTimeTotal = 0;
	tileChangeTimer = 0;
	attackTimer = 0;
	eatTimer = 0;
	seasonTimer = 0;
	waitTimer = 0;
	Fish fishLand;
	Fish fishSea;

	fishLand.Spawn("land");
	fishSea.Spawn("sea");

	//pause bool to pause the game
	bool pause;
	bool select;
	pause = false;
	select = false;
	int randnum = 0;
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

	//All the text used for the game
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	//Text for Paused state 
	Text playText;

	playText.setFont(font);

	//multiple stringstreams used to quickly switch text
	std::stringstream playStream;
	playStream <<
		"1. Play Game" <<
		"\n2. About" <<
		"\n3. Instructions" <<
		"\n4. References";
	std::stringstream aboutStream;
	aboutStream <<
		"This game is about the theme of global warming, staring a polar bear attempting" <<
		"\nto survive in the polar ice caps. Global Warming has constantly been affecting " <<
		"\nthe world in a variety of ways, and in the case of this scenario, Animals have been" <<
		"\nlosing their homes thanks to the ice caps melting, and the effects this has on us" <<
		"\nare that we will lose livable land mass due to flooding, as the melting results in" <<
		"\nmore water in the oceans. Global warming is not to be taken lightly and needs to be" <<
		"\nprevented" <<
		"\n" <<
		"\nPolar Bears are animals that reside in the Polar Ice Caps and the feature of the game" <<
		"\nPolar Bears are experiencing long summer fasts as a result of climate change, and the" <<
		"\nfasts they experience will continue to get longer and longer as climate change gets worse." <<
		"\nPolar bears primary food source is ringed seals, however, in cases where food is scarce," <<
		"\ntheir food source is fish.";
	std::stringstream instructionsStream;
	instructionsStream <<
		"WASD - Movement" <<
		"\nQ - Hibernate(When screen dark, on solid land)" <<
		"\nR - Attack" <<
		"\nE - Eat Fish in stock" <<
		"\nSpace - Pause" <<
		"\nEscape - Closes game (if still in main menu, will only return to play menu)";
	std::stringstream referenceStream;
	referenceStream <<
		"ice.png and snow.png - digit1024 on opengameart.com, originally called ice block (snow modified ice)" <<
		"\npolar.png and polarflip - rapidpunches on opengameart.com, part of Galapagos Penguin and Polar Bear" <<
		"\nfishland.png and fishsea.png - skylerb on opengameart.com, part of 02 The Rescue Assets COMP 1501A" <<
		"\n";
	playText.setString(playStream.str());
	playText.setCharacterSize(75);
	playText.setFillColor(Color::White);
	playText.setPosition(550, 400);

	//Text for Intro state
	Text introText;

	//introText font
	introText.setFont(font);

	std::stringstream introStream;
	introStream <<
		"You play as a polar bear in the melting ice caps affected by global warming. In the game," <<
		"\nyou must survive by eating fish you can find by either defeating other polar bears or " <<
		"\nby swimming out into the water where fish can be found. As you hunt, your health and " <<
		"\nstamina will start to drop, and if you are swimming, you will lose even more. This is" <<
		"\nregained byconsuming fish, fish found in water are held, while those gained from" <<
		"\ndefeated enemies areimmediately consumed. By consuming fish and defeating enemies," <<
		"\nyou will gain xp, and when dark arrives, you can hibernate and regain your health" <<
		"\nand stamina, and if you have enough xp you will level up. Reach level 10 by the" <<
		"\nend of the 10th year and you will survive" <<
		"\n" <<
		"\nPress enter to continue";
	introText.setString(introStream.str());
	introText.setFillColor(Color::White);
	introText.setPosition(100, 100);

	//Text for Playing state
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

	//set font
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

	//Text for end state
	Text loseText;

	loseText.setFont(font);
	loseText.setString("You Lose...");
	loseText.setCharacterSize(100);
	loseText.setFillColor(Color::White);
	loseText.setPosition(955, 535);
	//fps stored
	int maxFps = 0;
	int minFps = 50000;

	//Start of while loop, runs game while window is open
	while (m_Window.isOpen())
	{
		//Event variable
		Event event;


		Time dt = clock.restart();
		float dtAsSeconds = dt.asSeconds();

		//Check if pause variable has been made false, if so, increase gameTimeTotal
		if (pause == false)
		{
			gameTimeTotal += dt;

			gameTimeTotalFloat = gameTimeTotal.asSeconds();
		}
		if (pause == false && m_State == GameState::PLAYING)
		{
			seasonTimer = seasonTimer + dtAsSeconds;
		}

		//Constantly increment pauseTimeTotal to pause and unpause game

		pauseTimeTotal += dt.asSeconds();




		//change seasons



		// debug fps

		int fps = floor(1.0f / dtAsSeconds);

		if (maxFps < fps) maxFps = fps;
		if (minFps > fps) minFps = fps;
		// CHECK FPS
		//std::cout << "Fps: " << fps << " Min fps: " << minFps << " Max fps: " << maxFps << std::endl;

		while (m_Window.pollEvent(event))
		{
			if (m_State == GameState::PAUSED)
			{
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					if (select == true) {
						select = false;
						playText.setString(playStream.str());
						playText.setPosition(550, 400);
						playText.setCharacterSize(75);
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Num1) && select == false)
				{
					m_State = GameState::INTRO;
					waitTimer = pauseTimeTotal;

				}
				if (Keyboard::isKeyPressed(Keyboard::Num2) && select == false)
				{
					playText.setString(aboutStream.str());
					select = true;
					playText.setPosition(100, 100);
					playText.setCharacterSize(25);
				}
				if (Keyboard::isKeyPressed(Keyboard::Num3) && select == false)
				{
					playText.setString(instructionsStream.str());
					select = true;
					playText.setPosition(100, 100);
					playText.setCharacterSize(50);
				}
				if (Keyboard::isKeyPressed(Keyboard::Num4) && select == false) {
					playText.setString(referenceStream.str());
					select = true;
					playText.setPosition(100, 100);
					playText.setCharacterSize(25);
				}
			}
			//Intro state input
			if (m_State == GameState::INTRO)
			{
				//Pressing lets player enter game
				if (Keyboard::isKeyPressed(Keyboard::Enter))
				{
					m_State = GameState::PLAYING;
					pause == false;
				}
			}
			if (m_State != GameState::PAUSED)
			{
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					m_Window.close();
				}
			}
			if (m_State == GameState::PLAYING)
			{

				//Used to pause the game
				if (Keyboard::isKeyPressed(Keyboard::Space))
				{
					//Add wait timer to stop input being reread
					if (waitTimer + 0.1 < pauseTimeTotal)
					{
						if (pause == false)
						{
							pause = true;
							waitTimer = pauseTimeTotal;
						}
						else
						{
							pause = false;
							waitTimer = pauseTimeTotal;
						}
						cout << pause << endl;
					}

				}
				//if the game is not paused, allow player movement
				if (pause == false)
				{
					// reset fps count
					if (Keyboard::isKeyPressed(Keyboard::K))
					{
						minFps = 5000;
						maxFps = 0;
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
						//Check if enough time has passed to attack
						if (attackTimer + 0.5 < gameTimeTotalFloat)
						{
							//Run through polar bear list and see which are close enough to attack
							list<PolarBear*>::const_iterator iter;
							for (iter = lpPolarBears.begin(); iter != lpPolarBears.end(); ++iter)
							{
								Vector2f eCenter = (*iter)->getCenter();
								//Get the center of the polar bear and compare it to player
								std::cout << eCenter.x << " " << eCenter.y << endl;
								if (pPlayer->getCenter() != (*iter)->getCenter())
								{
									//Return player center
									Vector2f pCenter = pPlayer->getCenter();
									std::cout << endl;
									//for loops to scan around player for enemy
									for (int i = pCenter.x - 128; i < pCenter.x + 129; i = i + 128)
									{
										for (int j = pCenter.y - 128; j < pCenter.y + 129; j = j + 128)
										{
											std::cout << i << " " << j << endl;
											//If enemy is found, attack that enemy
											if (i - 1 <= eCenter.x && i + 1 >= eCenter.x && j - 1 <= eCenter.y && j + 1 >= eCenter.y)
											{
												//Run the attack function for both player and enemy and reduce health by the returned amount
												int damage = 0;
												damage = pPlayer->Attack();
												(*iter)->ReduceHealth(damage);
												//If the enemy has health, retailiate, if not, die and give player xp
												if ((*iter)->getHealth() > 0)
												{
													damage = (*iter)->Attack();
													pPlayer->ReduceHealth(damage);
												}
												else
												{
													pPlayer->addXP(90 * year);
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
					//Hibernate function, ends the year
					if (Keyboard::isKeyPressed(Keyboard::Q))
					{
						//Check the player's location, see if they can hibernate based on terrain and time passed
						if (pPlayer->getTerrain() == Tile::terrainType::SNOW && seasonTimer > 30)
						{
							//Player hibernate function
							pPlayer->Hibernate();
							//Check if the player has levelled up
							pPlayer->CheckIfLevelUp();
							//Reset seasonTimer
							seasonTimer = 0;
							//Increment year
							year++;
							if (year == 11)
							{
								m_State = GameState::END;
							}
							else
							{
								//When year increases, level up enemies
								std::list<Enemy*>::const_iterator iterE;
								for (iterE = lpEnemy.begin(); iterE != lpEnemy.end(); ++iterE)
								{
									float x = (*iterE)->getCenter().x;
									float y = (*iterE)->getCenter().y;
									(*iterE)->LevelUp();
								}
								//Attempting to reload tilemap with restored ice blocks, currently doesn't work
								tileMap = new Tilemap(year);
								pause = true;
							}
						}
					}
				}
			}
		}

		std::list<PolarBear*>::const_iterator iter;
		std::list<Enemy*>::const_iterator iterE;
		std::list<Fish*>::const_iterator iterF;
		if (m_State == GameState::PLAYING)
		{
			//Season timer will change blackout sprite to be less opaque, darkening the screen
			if (seasonTimer > 30)
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

			//TODO: In player class set stamina and health to 0 if they go below zero (negative)
			//Set stamina and health bar size based on stamina and health
			staminaBar.setSize(Vector2f(2 * pPlayer->getStamina(), staminaBarHeight));
			healthBar.setSize(Vector2f(2 * pPlayer->getHealth(), healthBarHeight));

			//TODO: move this to player class
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
					pPlayer->addHealth(2);
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
					if ((*iterF)->getType() == "land")
					{
						pPlayer->Pickup("land");
					}
					else if ((*iterF)->getType() == "sea")
					{
						pPlayer->Pickup("sea");
					}
					(*iterF)->setPosition(-1000, -1000);
					(*iterF)->PickedUp();
				}
			}

			// TODO: optimize			
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

			m_MainView.setCenter(cameraCenter);

			m_Window.clear(Color(135, 206, 235)); // clear the window
			m_Window.setView(m_MainView);

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
			if (pause == false)
			{
				for (iter = lpPolarBears.begin(); iter != lpPolarBears.end(); ++iter)
				{
					(*iter)->Movement(dtAsSeconds, gameTimeTotalFloat, mapBounds);
				}
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
					m_Window.draw(map[i][j]->getSprite());
				}
			}


			// TODO: Need better system to melt ice 
			if (pause == false)
			{
				for (int i = 0; i < mapBounds.y / 128; i++)
				{
					// for each tile on that row
					for (int j = 0; j < mapBounds.x / 128; j++)
					{
						// if the terrain type is ice
						if (map[i][j]->getTerrainType() == Tile::terrainType::ICE)
						{
							//determine if ice terrain changes to water
							if (((rand() % 100) + 1.f) >= 99.9)
							{
								if (tileChangeTimer + 0.1 < gameTimeTotalFloat)
								{
									tileMap->ChangeTileTerrain(i, j, Tile::terrainType::WATER);
									tileChangeTimer = gameTimeTotalFloat;
								}
							}
						}
					}
				}
			}

			int tilenumX = mapBounds.x;
			int tilenumY = mapBounds.y;
			//std::cout << tilenumX / 128 << endl;
			//std::cout << tilenumY / 128 << endl;


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
					//int tilenumX = mapBounds.x;
					//int tilenumY = mapBounds.y;
					//cout << tilenumX / 128 << endl;
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


		//Perform draws
		//Draw for paused

		if (m_State == GameState::PAUSED)
		{
			m_Window.clear(Color(0, 0, 0)); // clear the window
			m_Window.setView(m_HudView);
			m_Window.draw(playText);

		}

		if (m_State == GameState::INTRO)
		{
			m_Window.clear(Color(0, 0, 0)); // clear the window
			m_Window.setView(m_HudView);
			m_Window.draw(introText);
		}
		if (m_State == GameState::END) {
			m_Window.clear(Color(0, 0, 0)); // clear the window
			m_Window.setView(m_HudView);
			//Check if player level meets win condition
			if (pPlayer->getLevel() > 6 && pPlayer->isAlive()) {
				m_Window.draw(winText2);
			}
			else {
				m_Window.draw(loseText);
			}
		}
		//Draw for playing
		if (m_State == GameState::PLAYING)
		{
			for (iter = lpPolarBears.begin(); iter != lpPolarBears.end(); ++iter)
			{
				m_Window.draw((*iter)->getSprite());
			}

			for (iterF = lpFish.begin(); iterF != lpFish.end(); ++iterF) {
				m_Window.draw((*iterF)->getSprite());
			}
			m_Window.draw(fishSea.getSprite());
			m_Window.draw(fishLand.getSprite());

			m_Window.setView(m_BlackoutView);
			m_Window.draw(blackoutS);

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

			//change view to hudView to set hud graphics
			m_Window.setView(m_HudView);
			m_Window.draw(staminaBar);
			m_Window.draw(healthBar);
			m_Window.draw(fishText1);
			m_Window.draw(fishText2);
			m_Window.draw(levelText1);
			m_Window.draw(levelText2);
			m_Window.draw(healthText1);
			m_Window.draw(healthText2);
			m_Window.draw(staminaText1);
			m_Window.draw(staminaText2);
			m_Window.draw(yearText1);
			m_Window.draw(yearText2);


		}
		m_Window.display();
	}
}
