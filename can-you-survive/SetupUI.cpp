#include "Engine.h"

void Engine::setupUI()
{
	// Setup blackout screen properties
	blackoutCDarken.a = 100;
	blackoutCLighten.a = 0;

	blackoutT.loadFromFile("graphics/black.png");
	blackoutS.setTexture(blackoutT);
	blackoutS.scale(4.0, 4.0);

	//All the text used for the game
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	playText.setFont(font);

	// Multiple string streams used to quickly switch text
	playStream <<
		"1. Play Game" <<
		"\n2. About" <<
		"\n3. Instructions" <<
		"\n4. Credits" <<
		"\n5. Quit";
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
	instructionsStream <<
		"WASD - Movement" <<
		"\nQ - Hibernate(When screen dark, on solid land)" <<
		"\nR - Attack" <<
		"\nE - Eat Fish in stock" <<
		"\nSpace - Pause" <<
		"\nEscape - Closes game (if still in main menu, will only return to play menu)";
	referenceStream <<
		"Programmers:" <<
		"\nDesmond Delaney"<<
		"\nJorge Baptista" <<
		"\n" <<
		"\n Artist:" <<
		"\n Isabelle Rellinghaus";
	playText.setString(playStream.str());
	playText.setCharacterSize(75);
	playText.setFillColor(Color::White);
	playText.setPosition(550, 400);

	//introText font
	introText.setFont(font);

	introStream <<
		"You play as a polar bear in the melting ice caps affected by global warming. In the game," <<
		"\nyou must survive by eating fish you can find by either defeating other polar bears or " <<
		"\nby swimming out into the water where fish can be found. As you hunt, your health and " <<
		"\nstamina will start to drop, and if you are swimming, you will lose even more. This is" <<
		"\nregained by consuming fish, fish found in water are held, while those gained from" <<
		"\ndefeated enemies are immediately consumed. By consuming fish and defeating enemies," <<
		"\nyou will gain xp, and when dark arrives, you can hibernate and regain your health" <<
		"\nand stamina, and if you have enough xp you will level up. Reach level 10 by the" <<
		"\nend of the 10th year and you will survive" <<
		"\n" <<
		"\nPress enter to continue";
	introText.setString(introStream.str());
	introText.setFillColor(Color::White);
	introText.setPosition(100, 100);

	pauseStream <<
		"Paused";
	loadedStream <<
		"Loading Complete!" <<
		"\nPress Space to continue";

	pauseText1.setFont(font);
	pauseText1.setString(pauseStream.str());
	pauseText1.setCharacterSize(75);
	pauseText1.setFillColor(Color::Black);
	pauseText1.setPosition(800, 400);

	pauseText2.setFont(font);
	pauseText2.setString(pauseStream.str());
	pauseText2.setCharacterSize(75);
	pauseText2.setFillColor(Color::White);
	pauseText2.setPosition(805, 405);

	// Setup text variables
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

	loseText.setFont(font);
	loseText.setString("You Lose...");
	loseText.setCharacterSize(100);
	loseText.setFillColor(Color::White);
	loseText.setPosition(955, 535);

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

	// Stamina
	// Set color and position
	staminaBar.setFillColor(Color::Red);
	staminaBar.setPosition(50, 1000);

	// Health
	// Set color and position
	healthBar.setFillColor(Color::Green);
	healthBar.setPosition(50, 950);
}