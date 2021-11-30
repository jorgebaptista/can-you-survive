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
	//Texture textureBackground = Texture

	Tile tile;
	Player polar;

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

		float dtAsSeconds = dt.asSeconds();

		polar.Movement(dtAsSeconds);

		mainView.setCenter(tile.getCenter());

		window.clear(); // clear the window
		window.setView(mainView);

		window.draw(tile.getSprite());
		window.draw(polar.getSprite());
		
		window.display();
	}
	return 0;
}