#include "Enemy.h"
#include "Fish.h"
#include "Player.h"
#include "Tilemap.h"

using namespace sf;

int main() 
{

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
	float eatTimer;
	eatTimer = 0;
	//Texture textureBackground = Texture

	Tile tile;
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
	staminaBar.setPosition(50,1000);

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

		//Timer used for multiple commands
		Time dt = clock.restart();

		gameTimeTotal += dt;

		gameTimeTotalFloat = gameTimeTotal.asSeconds();

		float dtAsSeconds = dt.asSeconds();

		while (window.pollEvent(event))
		{
			//Keyboards commands for closing game and movement
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}
			//Moving Up
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				polar.moveUp();
			}
			else
			{
				polar.stopUp();
			}
			//Moving Down
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				polar.moveDown();
			}
			else
			{
				polar.stopDown();
			}
			//Moving Left
			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				polar.moveLeft();
			}
			else
			{
				polar.stopLeft();
			}
			//Moving Right
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
		}

		
		
		//Will set the stamina timer
		polar.addStaminaTimer(dtAsSeconds);

		//Set stamina and health bar size based on stamina and health
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

		//Move characters
		polar.Movement(dtAsSeconds, gameTimeTotalFloat);
		enemy.Movement(dtAsSeconds, gameTimeTotalFloat);

		mainView.setCenter(polar.getCenter());

		window.clear(); // clear the window
		//Used for non hud elements
		window.setView(mainView);

		window.draw(tile.getSprite());
		window.draw(polar.getSprite());
		window.draw(enemy.getSprite());
		window.draw(fishSea.getSprite());
		window.draw(fishLand.getSprite());

		//Hudview used for elements that don't move
		window.setView(hudView);
		window.draw(staminaBar);
		window.draw(healthBar);
		window.display();
	}
	return 0;
}