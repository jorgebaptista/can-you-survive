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

	//Texture textureBackground = Texture

	Tile tile;

	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}
		}

		mainView.setCenter(tile.getCenter());

		window.clear(); // clear the window
		window.setView(mainView);

		window.draw(tile.getSprite());
		window.display();
	}
	return 0;
}