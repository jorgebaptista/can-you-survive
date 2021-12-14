#include "Enemy.h"
#include "Fish.h"
#include "Player.h"
#include "Tilemap.h"
#include "FileSystem.h"

using namespace sf;

int main() 
{
	srand(static_cast<unsigned int>(time(0)));
	Tilemap *tileMap = new Tilemap();

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
	//Texture textureBackground = Texture

	Tile* tile = new Tile(Vector2f(0, 0));
	Player polar;
	Enemy enemy;
	Fish fishLand;
	Fish fishSea;

	fishLand.Spawn("land");
	fishSea.Spawn("sea");

	//Stamina Bar to display player stamina
	RectangleShape staminaBar;
	//Set inital width and height
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
	//Set color and positon
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
				polar.moveUp();
			}
			else
			{
				polar.stopUp();
			}

			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				polar.moveDown();
			}
			else
			{
				polar.stopDown();
			}

			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				polar.moveLeft();
			}
			else
			{
				polar.stopLeft();
			}

			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				polar.moveRight();
			}
			else
			{
				polar.stopRight();
			}
			//Eat fish
			if (Keyboard::isKeyPressed(Keyboard::E))
			{
				if (eatTimer + 0.5 < gameTimeTotalFloat) 
				{
					polar.EatFish();
					eatTimer = gameTimeTotalFloat;
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::R))
			{
				if (attackTimer + 0.5 < gameTimeTotalFloat) {
					Vector2f eCenter = enemy.getCenter();
					Vector2f pCenter = polar.getCenter();
					cout << endl;
					for (int i = pCenter.x - 128; i < pCenter.x + 129; i = i + 128)
					{
						for (int j = pCenter.y - 128; j < pCenter.y + 129; j = j + 128)
						{
							cout << i << " " << j << endl;
							if (i == eCenter.x && j == eCenter.y) {
								int damage = 0;
								damage = polar.Attack();
								enemy.ReduceHealth(damage);
								if (enemy.getHealth()>0) {
									damage = enemy.Attack();
									polar.ReduceHealth(damage);
								}
								else {
									polar.addXP(90);
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
		polar.addStaminaTimer(dtAsSeconds);

		//Set stamina and health bar size based on stamina and health
		staminaBar.setSize(Vector2f(2 * polar.getStamina(), staminaBarHeight));
		healthBar.setSize(Vector2f(2 * polar.getHealth(), healthBarHeight));

		//Check if enough time has passed to decrease stamina or health
		if (polar.getStaminaTimer() >= 1)
		{
			if (!polar.getStamina() <= 0)
			{
				polar.StaminaDecrease(1);
				polar.setStaminaTimer();
			}
			else
			{
				polar.ReduceHealth(1);
				polar.setStaminaTimer();
			}
		}
		if (polar.getPosition().intersects(fishSea.getPosition()))
		{
			if (!fishSea.isCollected())
			{
				polar.Pickup("sea");
				//fishSea.setPosition(-1000, -1000);
				fishSea.PickedUp();
			}

		}
		else if (polar.getPosition().intersects(fishLand.getPosition()))
		{
			if (!fishLand.isCollected())
			{
				polar.Pickup("land");
				//fishLand.setPosition(-1000, -1000);
				fishLand.PickedUp();
			}

		}

		//Move characters
		polar.Movement(dtAsSeconds, gameTimeTotalFloat);
		//enemy.Movement(dtAsSeconds, gameTimeTotalFloat);

		mainView.setCenter(polar.getCenter());

		window.clear(); // clear the window
		window.setView(mainView);

		std::vector<std::vector<Tile*>> map = tileMap->getMap();

		for (int i = 0; i < map.size(); i++)
		{
			for (int j = 0; j < map[i].size(); j++)
			{
				window.draw(map[i][j]->getSprite());
			}
		}

		if (!enemy.isAlive()) {
			enemy.RemoveFromPlay();
		};
		cout << enemy.getHealth() << endl;

		polar.CheckIfLevelUp();
		window.draw(polar.getSprite());
		window.draw(enemy.getSprite());
		window.draw(fishSea.getSprite());
		window.draw(fishLand.getSprite());

		//Hud view used for elements that don't move
		window.setView(hudView);
		window.draw(staminaBar);
		window.draw(healthBar);
		window.display();
	}
	return 0;
}