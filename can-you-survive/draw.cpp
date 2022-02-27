#include "Engine.h"

void Engine::draw()
{
	//Draw for MENU

	if (m_State == GameState::MENU)
	{
		m_Window.clear(Color(0, 0, 0)); // clear the m_Window
		m_Window.setView(m_HudView);
		m_Window.draw(playText);

	}

	if (m_State == GameState::INTRO)
	{
		m_Window.clear(Color(0, 0, 0)); // clear the m_Window
		m_Window.setView(m_HudView);
		m_Window.draw(introText);
	}
	if (m_State == GameState::END) {
		m_Window.clear(Color(0, 0, 0)); // clear the m_Window
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
		// Iterate through the polar bear list and draw each polar bear
		for (iter = lpPolarBears.begin(); iter != lpPolarBears.end(); ++iter)
		{
			m_Window.draw((*iter)->getSprite());
		}

		// Iterate through the fish list and draw each fish
		for (iterF = lpFish.begin(); iterF != lpFish.end(); ++iterF) {
			m_Window.draw((*iterF)->getSprite());
		}

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

		//change view to m_HudView to set HUD graphics
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

		if (pause == true) {
			m_Window.draw(pauseText1);
			m_Window.draw(pauseText2);
		}
	}
}