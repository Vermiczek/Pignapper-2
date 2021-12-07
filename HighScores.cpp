#include "HighScores.h"
#include <fstream>
#include <algorithm>
#include <string>

HighScores::HighScores(float width, float height, int& ActionX)
{
	Action = &ActionX;
	std::string buforFont; //bufor przechowuj¹cy czcionkê
	std::string buforTex; //bufor przechowuj¹cy tekst przycisku
	sf::Vector2f buforPos; //bufor przechowuj¹cy pozycjê przycisku


	HighScores::readHiscores();
	HighScores::getTexts();
	buforFont = "smileandwave.ttf";
	buforTex = "Back";
	buforPos = sf::Vector2f(width / 6, 5 * height / 6);
	buttons[0] = new Button(buforFont, buforTex, sf::Color::White, 50, buforPos);
	buforTex = "Down";
	buforPos = sf::Vector2f(5*width / 6, 5 * height / 6);
	buttons[1] = new Button(buforFont, buforTex, sf::Color::White, 50, buforPos);
	buforTex = "Up";
	buforPos = sf::Vector2f(5*width / 6,  height / 6);
	buttons[2] = new Button(buforFont, buforTex, sf::Color::White, 50, buforPos);

	if (!hiscoresBackgroundTexture.loadFromFile("hiscoresBackgroundTexture.png"))
	{
		*Action = 0;
	}
	else
	{
		sf::Vector2u TextureSize = hiscoresBackgroundTexture.getSize(); 
		float ScaleX = (float)width / TextureSize.x;
		float ScaleY = (float)height / TextureSize.y;     
		hiscoresBackgroundSprite.setTexture(hiscoresBackgroundTexture);
		hiscoresBackgroundSprite.setScale(ScaleX, ScaleY);      
		

	}

	selectedItemIndex = 0;
	buttons[selectedItemIndex]->setButtonTextColor(sf::Color::Red);
}




HighScores::~HighScores()
{
}

void HighScores::readHiscores()
{
	highScore tempHighScore;
	std::ifstream hiscoresFile;
	std::string text;
	bool isEven = 0;

	hiscoresFile.open("highScores.txt");
	while (getline(hiscoresFile, text))
	{
		if (!isEven) 
		{
			tempHighScore.name = text;
			isEven = 1;
			continue;
		} 
		if (isEven)
		{
			tempHighScore.score = stoi(text);
			isEven = 0;
			highScores.push_back(tempHighScore);
		}

	}
	std::sort(HighScores::highScores.begin(), HighScores::highScores.end(), &scoreSort);

}


void HighScores::draw(sf::RenderWindow& window)
{   
	window.draw(hiscoresBackgroundSprite);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		buttons[i]->drawButton(window);
	}
	int hiscoreLimit;

	if (highScores.size() < 10)
		hiscoreLimit = highScores.size();
	else
		hiscoreLimit = 10;

	for (int i = 0; i < hiscoreLimit; i++)
	{
		window.draw(texts[i]);
	}

}

void HighScores::getTexts()
{
	
	if (!font.loadFromFile("smileandwave.ttf"))
	{
		// handle error
	};
	
	int hiscoreLimit;

	if (highScores.size() < 10)
		hiscoreLimit = highScores.size();
	else
		hiscoreLimit = 10;

	for (int i = 0; i < hiscoreLimit; i++)
	{
		texts[i].setFont(font);
		texts[i].setString(highScores[i+scroll].name + "      " + std::to_string(highScores[i+scroll].score));

		// set the character size
		texts[i].setCharacterSize(30); // in pixels, not points!

		// set the color
		texts[i].setFillColor(sf::Color::White);

		texts[i].setOutlineColor(sf::Color::Black);
		texts[i].setOutlineThickness(2);
		// set the text style
		texts[i].setStyle(sf::Text::Bold);

		texts[i].setPosition(300, 100+50*i);
	}
}


void HighScores::MouseDetect(sf::RenderWindow& window)
{

	coursorPos = sf::Mouse::getPosition(window);
	sf::Vector2f tempPos = sf::Vector2f(coursorPos);

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		if (buttons[i]->detectCollision(tempPos))
		{
			selectedItemIndex = i;
		}
	}
}



void HighScores::checkIndex()
{

	if (selectedItemIndex != selectedItemIndexFlag)
	{
		buttons[selectedItemIndexFlag]->setButtonTextColor(sf::Color::White);
		buttons[selectedItemIndex]->setButtonTextColor(sf::Color::Red);
		selectedItemIndexFlag = selectedItemIndex;
	}

}

int HighScores::Select(sf::RenderWindow& window)
{
	if (selectedItemIndex == 0)
		return MenuScr;
	if (highScores.size() > 10) {
		if (selectedItemIndex == 1)
		{
			HighScores::scrollList(1, scroll, highScores.size());
			std::cout << scroll;
			HighScores::getTexts();
		}
		if (selectedItemIndex == 2)
		{
			HighScores::scrollList(-1, scroll, highScores.size());
			std::cout << scroll;
			HighScores::getTexts();
		}
	}
	return HighScoresScr;
}

void HighScores::scrollList(int value, int& scrollValue, int size)
{
	int limit = size - 10;

	scrollValue = scrollValue + value;
	if (scrollValue < 0)
	{
		scrollValue = 0;
		HighScores::getTexts();
	}
	else if (scrollValue == limit)
	{
		scrollValue = scrollValue-1;
		HighScores::getTexts();
	}
}

void HighScores::CapitalizeButton()
{
	buttons[selectedItemIndex]->CapitalizeQuick();
}

void HighScores::deCapitalizeButton()
{
	buttons[selectedItemIndex]->deCapitalizeQuick();
}

void HighScores::Events(sf::RenderWindow& window)
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
				
				break;

			case sf::Keyboard::Down:
				
				break;

			case sf::Keyboard::Return:
				Select(window);
				break;


				break;


				break;
			}

		case sf::Event::Closed:
			window.close();

			break;

		case sf::Event::MouseButtonPressed:
			switch (event.mouseButton.button)
			{
			case sf::Mouse::Left:
				for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
				{
					if (buttons[i]->detectCollision(sf::Vector2f(sf::Mouse::getPosition(window))))
					{
						*Action = Select(window);
					}

				}

				break;

			}

			break;

			}
		}


	
}

/*void readHighScores()
{
	std::ifstream myfile("highScores.txt");
	myfile.open("example.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			cout << line << '\n';
		}
		myfile.close();
	}
}*/

void HighScores::Run(sf::RenderWindow& window)
{
	Events(window);
	checkIndex();
	draw(window);
	MouseDetect(window);
}
