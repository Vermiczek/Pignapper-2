#include "App.h"

App::App(float widthX, float heightY)
{
	width = widthX;
	height = heightY;
}

App::~App()
{

}

void App::runApp()
{
	sf::RenderWindow window(sf::VideoMode(width, height), "Pignapper");
	MainMenu menu(window.getSize().x, window.getSize().y, Action);
	HighScores highscores(window.getSize().x, window.getSize().y, Action);
	GameScreen gameScreen(window.getSize().x, window.getSize().y, Action);
	GameOver gameOver(window.getSize().x, window.getSize().y, Action);
	int previousSizeX = window.getSize().x;
	int previousSizeY = window.getSize().y;
	window.setFramerateLimit(60);

	while (window.isOpen())
	{       
		    window.clear();
		    ActionDo(window, menu, highscores, gameScreen, gameOver);
			window.display();
	}
}

void App::resetGamestate(GameScreen &gamescreen)
{
	gamescreen.game = GameState();
}

void App::ActionDo(sf::RenderWindow& window, MainMenu& menu, HighScores& highscores, GameScreen& gameScreen, GameOver& gameover)
{
	if (Action == 0)
	{   
		menu.Run(window);
    }

	if (Action == 1)
	{
		gameScreen.Run(window);
		if (gameScreen.PlayerHP()<=0)
		{
			gameover.setHighscore(gameScreen.returnCalculatedScore());
			Action = 6;
		}
	}

	if (Action == 4)
	{
		highscores.readHiscores();
		highscores.Run(window);
	}

	if (Action == 5)
	{
		window.close();
	}
	if (Action == 6)
	{
		resetGamestate(gameScreen);
		gameover.Run(window);
	}
}
