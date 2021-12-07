#include "MainMenu.h"


MainMenu::MainMenu(float width, float height, int &ActionX)
{
	Action = &ActionX;
	std::string buforFont; //bufor przechowuj¹cy czcionkê
	std::string buforTex; //bufor przechowuj¹cy tekst przycisku
	sf::Vector2f buforPos; //bufor przechowuj¹cy pozycjê przycisku
	
	buforFont = "smileandwave.ttf";
	buforTex = "Play";
	buforPos = sf::Vector2f(width / 2, height / (MENU_NUMBER_OF_ITEMS + 3) * 3);
	buttons[0] = new Button(buforFont, buforTex, sf::Color::White, 50, buforPos);

	buforTex = "Load Game";
	buforPos = sf::Vector2f(width / 2, height / (MENU_NUMBER_OF_ITEMS + 3) * 4);
	buttons[1] = new Button(buforFont, buforTex, sf::Color::White, 50, buforPos);

	buforTex = "Options";
	buforPos = sf::Vector2f(width / 2, height / (MENU_NUMBER_OF_ITEMS + 3) * 5);
	buttons[2] = new Button(buforFont, buforTex, sf::Color::White, 50, buforPos);

	buforTex = "High Scores";
	buforPos = sf::Vector2f(width / 2, height / (MENU_NUMBER_OF_ITEMS + 3) * 6);
	buttons[3] = new Button(buforFont, buforTex, sf::Color::White, 50, buforPos);

	buforTex = "Exit";
	buforPos = sf::Vector2f(width / 2, height / (MENU_NUMBER_OF_ITEMS + 3) * 7);
	buttons[4] = new Button(buforFont, buforTex, sf::Color::White, 50, buforPos);

	if (!menuBackgroundTexture.loadFromFile("menuBackgroundTexture.jpg"))
	{
		*Action = 5;
	}
	else
	{
		sf::Vector2u TextureSize = menuBackgroundTexture.getSize();
		float ScaleX = (float)width / TextureSize.x;
		float ScaleY = (float)height / TextureSize.y;
		menuBackgroundSprite.setTexture(menuBackgroundTexture);
		menuBackgroundSprite.setScale(ScaleX, ScaleY);
	}

	selectedItemIndex = 0;
	buttons[selectedItemIndex]->setButtonTextColor(sf::Color::Red);
}


MainMenu::~MainMenu()
{
}

void MainMenu::draw(sf::RenderWindow& window)
{
	window.draw(menuBackgroundSprite);
	for (int i = 0; i < MENU_NUMBER_OF_ITEMS; i++)
	{
		buttons[i]->drawButton(window);
	}
}

void MainMenu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		selectedItemIndex--;
		}
	else
	{
		selectedItemIndex = MENU_NUMBER_OF_ITEMS -1;
		}
}

void MainMenu::MoveDown()
{
	if (selectedItemIndex + 1 < MENU_NUMBER_OF_ITEMS)
	{
		selectedItemIndex++;
	}
	else
	{
		selectedItemIndex = 0;
	}
}

void MainMenu::MouseDetect(sf::RenderWindow& window)
{
	
	coursorPos = sf::Mouse::getPosition(window);
	sf::Vector2f tempPos = sf::Vector2f(coursorPos);
	for (int i = 0; i < MENU_NUMBER_OF_ITEMS; i++)
	{
		if (buttons[i]->detectCollision(tempPos))
		{
			selectedItemIndex = i;

		}

	}
}

void MainMenu::refreshResize(float width, float height)
{

	std::string buforFont; //bufor przechowuj¹cy czcionkê
	std::string buforTex; //bufor przechowuj¹cy tekst przycisku
	sf::Vector2f buforPos; //bufor przechowuj¹cy pozycjê przycisku
	buforFont = "smileandwave.ttf";
	buforTex = "Play";
	buforPos = sf::Vector2f(width / 2, height / (MENU_NUMBER_OF_ITEMS + 3) * 3);
	buttons[0] = new Button(buforFont, buforTex, sf::Color::White, 50, buforPos);

	buforTex = "Load Game";
	buforPos = sf::Vector2f(width / 2, height / (MENU_NUMBER_OF_ITEMS + 3) * 4);
	buttons[1] = new Button(buforFont, buforTex, sf::Color::White, 50, buforPos);

	buforTex = "Options";
	buforPos = sf::Vector2f(width / 2, height / (MENU_NUMBER_OF_ITEMS + 3) * 5);
	buttons[2] = new Button(buforFont, buforTex, sf::Color::White, 50, buforPos);

	buforTex = "High Scores";
	buforPos = sf::Vector2f(width / 2, height / (MENU_NUMBER_OF_ITEMS + 3) * 6);
	buttons[3] = new Button(buforFont, buforTex, sf::Color::White, 50, buforPos);

	buforTex = "Exit";
	buforPos = sf::Vector2f(width / 2, height / (MENU_NUMBER_OF_ITEMS + 3) * 7);
	buttons[4] = new Button(buforFont, buforTex, sf::Color::White, 50, buforPos);
}


void MainMenu::checkIndex()
{
	
	if (selectedItemIndex != selectedItemIndexFlag)
	{
		buttons[selectedItemIndexFlag]->setButtonTextColor(sf::Color::White);
		buttons[selectedItemIndex]->setButtonTextColor(sf::Color::Red);
		selectedItemIndexFlag = selectedItemIndex;
	}
	
}

int MainMenu::Select(sf::RenderWindow& window)
{
	if (selectedItemIndex == 0)
		return GameScr;
	if (selectedItemIndex == 1)
		return loadGameScr;
	if (selectedItemIndex == 2)
		return OptionsScr;
	if (selectedItemIndex == 3)
		return HighScoresScr;
	if (selectedItemIndex == 4)
		return ExitApp;
	else
		return MenuScr;
}

void MainMenu::CapitalizeButton()
{
	buttons[selectedItemIndex]->CapitalizeQuick();
}

void MainMenu::deCapitalizeButton()
{
	buttons[selectedItemIndex]->deCapitalizeQuick();
}

void MainMenu::Events(sf::RenderWindow& window)
{
	sf::Event event;

	while (window.pollEvent(event))
	{


		switch (event.type)
		{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				MoveUp();
				break;

			case sf::Keyboard::Down:
				MoveDown();
				break;

			case sf::Keyboard::Return:
				Select(window);
				break;

			
					break;


				break;
			}
		case sf::Event::MouseButtonPressed:
			switch (event.mouseButton.button)
			{
			case sf::Mouse::Left:
				for (int i = 0; i < MENU_NUMBER_OF_ITEMS; i++)
				{
					if (buttons[i]->detectCollision(sf::Vector2f(sf::Mouse::getPosition(window))))
					{
						*Action=Select(window);
						break;
					}

				}
				break;

			}
			break;

		case sf::Event::Closed:
			window.close();

			break;

		case sf::Event::Resized:
				std::cout << "new width: " << event.size.width << std::endl;
				std::cout << "new height: " << event.size.height << std::endl;
				refreshResize(event.size.width, event.size.height);
				break;

		}


	}
}

void MainMenu::Run(sf::RenderWindow& window)
{
	Events(window);
	checkIndex();
	draw(window);
	MouseDetect(window);
}
