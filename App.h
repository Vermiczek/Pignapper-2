#ifndef APP_H
#define APP_H
#include <iostream>
#include "SFML/Graphics.hpp"
#include "HighScores.h"
#include "MainMenu.h"
#include "Goodies.h"
#include "Button.h"
#include "GameScreen.h"
#include "GameOver.h"


#define NUMBER_OF_SCREENS 2


class App
{
public:
	App(float width, float height);
	~App();
	void runApp();
	void resetGamestate(GameScreen& gamescreen);
	void resetGamestate();
	void ActionDo(sf::RenderWindow& window, MainMenu& menu, HighScores& highscores, GameScreen& gameScreen, GameOver& gameover);
	void switchScene(int i);
	int Action = MenuScr;
	void ActionDo(sf::RenderWindow& window, MainMenu& menu, HighScores& highscores, GameScreen& gameScreen);
	int width;
	int height;

private:
	int lastAction = -1;
	int ChoosenScene = 0;
};

#endif