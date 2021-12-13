#include "Enemy.h"
#include "Fish.h"
#include "Player.h"
#include "Tilemap.h"

using namespace sf;

int main() {

	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(VideoMode(resolution.x, resolution.y), "Can You Survive?", Style::Fullscreen);

	View mainView(FloatRect(0, 0, resolution.x, resolution.y));

	Clock clock;

	

	Time gameTimeTotal;
	float gameTimeTotalFloat;
	//Texture textureBackground = Texture

	Tile tile;
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

		polar.Movement(dtAsSeconds, gameTimeTotalFloat);
		enemy.Movement(dtAsSeconds, gameTimeTotalFloat);
		cout << polar.getStaminaTimer() << endl;
		if (polar.getStaminaTimer() >= 1) {
			polar.StaminaDecrease(1);
			polar.setStaminaTimer();
		}
		
		mainView.setCenter(polar.getCenter());

		window.clear(); // clear the window
		window.setView(mainView);

		window.draw(tile.getSprite());
		window.draw(polar.getSprite());
		window.draw(enemy.getSprite());
		window.draw(staminaBar);
		window.display();
	}
	return 0;
}