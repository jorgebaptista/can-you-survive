#include "Engine.h"

void Engine::input()
{
	//Event variable
	Event event;

	while (m_Window.pollEvent(event))
	{
		if (m_State == GameState::MENU)
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
				m_WaitTimer = m_PauseTime;

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
				playText.setCharacterSize(35);
			}
			if (Keyboard::isKeyPressed(Keyboard::Num4) && select == false) {
				playText.setString(referenceStream.str());
				select = true;
				playText.setPosition(100, 100);
				playText.setCharacterSize(25);
			}
			if (Keyboard::isKeyPressed(Keyboard::Num5) && select == false) {
				m_Window.close();
			}
		}
		//Intro m_State input
		if (m_State == GameState::INTRO)
		{
			//Pressing lets player enter game
			if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				m_State = GameState::PLAYING;
				pause == false;
			}
		}
		if (m_State != GameState::MENU)
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
				if (m_WaitTimer + 0.1 < m_PauseTime)
				{
					if (pause == false)
					{
						pause = true;
						m_WaitTimer = m_PauseTime;
					}
					else
					{
						pause = false;
						m_WaitTimer = m_PauseTime;
					}
					cout << pause << endl;
				}
				pauseText1.setString(pauseStream.str());
				pauseText1.setPosition(800, 400);
				pauseText2.setString(pauseStream.str());
				pauseText2.setPosition(805, 405);

			}
			//if the game is not paused, allow player movement
			if (pause == false)
			{
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
					if (m_EatTimer + 0.5 < m_TimeAsSeconds)
					{
						pPlayer->EatFish();
						m_EatTimer = m_TimeAsSeconds;
					}
				}
				//Attack with R
				if (Keyboard::isKeyPressed(Keyboard::R))
				{
					//Check if enough time has passed to attack
					if (m_AttackTimer + 0.5 < m_TimeAsSeconds)
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
						m_AttackTimer = m_TimeAsSeconds;
					}

				}
				//Hibernate function, ends the year
				if (Keyboard::isKeyPressed(Keyboard::Q))
				{
					//Check the player's location, see if they can hibernate based on terrain and time passed
					if (pPlayer->getTerrain() == Tile::terrainType::SNOW && m_SeasonTimer > 30)
					{
						//Player hibernate function
						pPlayer->Hibernate();
						//Check if the player has levelled up
						pPlayer->CheckIfLevelUp();
						//Reset seasonTimer
						m_SeasonTimer = 0;
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
							//Attempting to reload tilemap with restored ice blocks
							tileMap = new Tilemap(year);
							pauseText1.setString(loadedStream.str());
							pauseText1.setPosition(700, 300);
							pauseText2.setString(loadedStream.str());
							pauseText2.setPosition(705, 305);
							pause = true;
						}
					}
				}
			}
		}
	}
}