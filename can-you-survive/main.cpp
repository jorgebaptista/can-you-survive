#include "Enemy.h"
#include "Fish.h"
#include "Player.h"
#include "Tilemap.h"
#include "FileSystem.h"

using namespace sf;

int main() {
	Tilemap *tileMap = new Tilemap();

	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(VideoMode(resolution.x, resolution.y), "Can You Survive?", Style::Fullscreen);

	View mainView(FloatRect(0, 0, resolution.x, resolution.y));

	Clock clock;

	

	Time gameTimeTotal;
	float gameTimeTotalFloat;
	//Texture textureBackground = Texture

	Tile* tile = new Tile(Vector2f(0, 0));
	Player polar;
	Enemy enemy;

	RectangleShape staminaBar;
	float staminaBarStartWidth = 200;
	float staminaBarHeight = 40;
	
	staminaBar.setFillColor(Color::Red);
	staminaBar.setPosition(100, 100);

	while (window.isOpen())
	{
		Event event;

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
		}

		Time dt = clock.restart();

		gameTimeTotal += dt;

		gameTimeTotalFloat = gameTimeTotal.asSeconds();

		float dtAsSeconds = dt.asSeconds();
		polar.setStaminaTimer(dtAsSeconds);
		staminaBar.setSize(Vector2f(2*polar.getStamina(), staminaBarHeight));
		healthBar.setSize(Vector2f(2 *polar.getHealth(), healthBarHeight));
		
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

		polar.Movement(dtAsSeconds, gameTimeTotalFloat);
		enemy.Movement(dtAsSeconds, gameTimeTotalFloat);
		//std::cout << polar.getStaminaTimer() << endl;
		if (polar.getStaminaTimer() >= 1) {
			polar.StaminaDecrease(1);
			polar.setStaminaTimer();
		}
		
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

		//window.draw(tile->getSprite());
		window.draw(polar.getSprite());
		window.draw(enemy.getSprite());
		window.draw(staminaBar);
		window.display();
	}
	return 0;
}