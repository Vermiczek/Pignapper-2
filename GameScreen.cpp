#include "GameScreen.h"

GameScreen::GameScreen(float width, float height, int& ActionX)
{
	Action = &ActionX;
	std::string buforFont; //bufor przechowuj¹cy czcionkê
	std::string buforTex; //bufor przechowuj¹cy tekst przycisku
	sf::Vector2f buforPos; //bufor przechowuj¹cy pozycjê przycisku
	game = GameState();

	if (!BackgroundTexture.loadFromFile("gameBackgroundTexture.png"))
	{
		*Action = 5;
	}
	else
	{
		sf::Vector2u TextureSize = BackgroundTexture.getSize();
		float ScaleX = (float)width / TextureSize.x;
		float ScaleY = (float)height / TextureSize.y;
		BackgroundSprite.setTexture(BackgroundTexture);
		BackgroundSprite.setScale(ScaleX, ScaleY);
	}
	

}

void GameScreen::Events(sf::RenderWindow& window)
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::A:
				game.setKeyDowns(0);
				break;

			case sf::Keyboard::Space:
				game.setSpaceDown();
				break;


			case sf::Keyboard::D:
				game.setKeyDowns(1);
				break;

			case sf::Keyboard::W:
				game.playerJump(1);
				break;

			case sf::Keyboard::S:
				game.playerJump(0);
				break;

			case sf::Keyboard::Num1:
				game.chosenWeapon = 0;
				break;

			case sf::Keyboard::Num2:
				game.chosenWeapon = 1;
				break;
			}
		}
		switch (event.type)
			{
			case sf::Event::MouseButtonPressed:
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Left:
					game.drawingArrow = 1;
					break;
				case sf::Mouse::Right:
					game.markForDetonation();
					break;

				}
			}
		switch (event.type)
		{
		case sf::Event::MouseButtonReleased:
			switch (event.mouseButton.button)
			{
			case sf::Mouse::Left:
				coursorPos = sf::Mouse::getPosition(window);
				game.ShootArrow(coursorPos.x, coursorPos.y);
				break;
			}
		}
		switch (event.type)
		{
		case sf::Event::KeyReleased:
			switch (event.key.code)
			{
			case sf::Keyboard::A:
				game.ResetKeyDowns(0);
				break;

			case sf::Keyboard::Space:
				game.setSpaceUp();
				break;


			case sf::Keyboard::D:
				game.ResetKeyDowns(1);
				break;

			}
		}
	}
}

GameScreen::~GameScreen()
{
}

void GameScreen::draw(sf::RenderWindow& window, GameState gamestate)
{
	window.clear();
	window.draw(BackgroundSprite);
	window.draw(platformSprite);
	gamestate.draw(window);
}

void GameScreen::Run(sf::RenderWindow& window)
{   
	Events(window);
	game.refresh();
	draw(window, game);
	MouseDetect(window);
}

void GameScreen::MouseDetect(sf::RenderWindow& window)
{

	coursorPos = sf::Mouse::getPosition(window);
	sf::Vector2f tempPos = sf::Vector2f(coursorPos);

}