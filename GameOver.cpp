#include "GameOver.h"


GameOver::GameOver(float width, float height, int& ActionX)
{
	Action = &ActionX;
	std::string buforFont; //bufor przechowuj¹cy czcionkê
	std::string buforTex; //bufor przechowuj¹cy tekst przycisku
	sf::Vector2f buforPos; //bufor przechowuj¹cy pozycjê przycisku
	buforFont = "smileandwave.ttf";
	buforTex = "Play again!";
	buforPos = sf::Vector2f(width / 2, height / (MENU_NUMBER_OF_ITEMS + 3) * 3);
	buttons[0] = new Button(buforFont, buforTex, sf::Color::White, 50, buforPos);

	buforTex = "Exit";
	buforPos = sf::Vector2f(width / 2, height / (MENU_NUMBER_OF_ITEMS + 3) * 4);
	buttons[1] = new Button(buforFont, buforTex, sf::Color::White, 50, buforPos);

	buforTex = "Score:";
	buforPos = sf::Vector2f(width / 2, height / (MENU_NUMBER_OF_ITEMS + 3) );
	buttons[2] = new Button(buforFont, buforTex, sf::Color::White, 50, buforPos);

	buforTex = " ";
	buforPos = sf::Vector2f(width / 2, height / (MENU_NUMBER_OF_ITEMS + 3) *2);
	buttons[3] = new Button(buforFont, buforTex, sf::Color::White, 50, buforPos);

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


GameOver::~GameOver()
{
}

void GameOver::draw(sf::RenderWindow& window)
{
	window.draw(menuBackgroundSprite);
	for (int i = 0; i < MENU_NUMBER_OF_ITEMS+2; i++)
	{
		buttons[i]->drawButton(window);
	}
}

void GameOver::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		selectedItemIndex--;
	}
	else
	{
		selectedItemIndex = MENU_NUMBER_OF_ITEMS - 1;
	}
}

void GameOver::MoveDown()
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

void GameOver::SaveScore()
{
	std::ofstream file;
	file.open("highScores.txt", std::ios_base::app);
	if (file.is_open())
	{
		file << playername<<std::endl;
		file << highScore<<std::endl;
		file.close();
	}
}

void GameOver::MouseDetect(sf::RenderWindow& window)
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


void GameOver::checkIndex()
{

	if (selectedItemIndex != selectedItemIndexFlag)
	{
		buttons[selectedItemIndexFlag]->setButtonTextColor(sf::Color::White);
		buttons[selectedItemIndex]->setButtonTextColor(sf::Color::Red);
		selectedItemIndexFlag = selectedItemIndex;
	}

}

int GameOver::Select(sf::RenderWindow& window)
{
	if (selectedItemIndex == 0) {
		SaveScore();
		return GameScr;
	}
	if (selectedItemIndex == 1) {
		SaveScore();
		return MenuScr;
	}
	else
		return 5;
}

void GameOver::CapitalizeButton()
{
	buttons[selectedItemIndex]->CapitalizeQuick();
}

void GameOver::deCapitalizeButton()
{
	buttons[selectedItemIndex]->deCapitalizeQuick();
}

void GameOver::Events(sf::RenderWindow& window)
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
	    case sf::Event::TextEntered:
			{
			if (event.text.unicode < 123&&event.text.unicode>64) {
				playername += static_cast<char>(event.text.unicode);
				std::cout << playername<<std::endl;
				
					buttons[3]->setText(playername);
					buttons[3]->SetGlobalBoundsToMiddle();
				}
			}
		case sf::Event::MouseButtonPressed:
			switch (event.mouseButton.button)
			{
			case sf::Mouse::Left:
				for (int i = 0; i < MENU_NUMBER_OF_ITEMS; i++)
				{
					if (buttons[i]->detectCollision(sf::Vector2f(sf::Mouse::getPosition(window))))
					{
						*Action = Select(window);
						break;
					}

				}
				break;

			}
			break;

		case sf::Event::Closed:
			window.close();

			break;

	

		}


	}
}

void GameOver::Run(sf::RenderWindow& window)
{
	Events(window);
	checkIndex();
	draw(window);
	MouseDetect(window);
}
