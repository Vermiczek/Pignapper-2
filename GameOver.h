#ifndef GAMEOVER_H
#define GAMEOVER_H
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Button.h"
#include <vector>
#include "Goodies.h"
#include <fstream>
#define MENU_NUMBER_OF_ITEMS 2

class GameOver
{
public:
	GameOver(float width, float height, int& Action); //konstruktor menu
	~GameOver(); //destruktor menu
	void draw(sf::RenderWindow& window); //rysuje menu we wskazanym oknie
	void MoveUp(); //zmniejsza indeks wyroznionej opcji w menu oraz przeskakuje po wykroczeniu poza zakres
	void MoveDown(); //zwieksza indeks wyroznionej opcji w menu oraz przeskakuje po wykroczeniu poza zakres
	void SaveScore();
	void checkIndex(); //zmienia podswietlenie przyciskow w zaleznosci od indexow
	int Select(sf::RenderWindow& window); //zatwierdza wybór
	void CapitalizeButton(); //gowno
	void deCapitalizeButton(); //pizda
	void Events(sf::RenderWindow& window);
	void MouseDetect(sf::RenderWindow& window); //pobiera koordynaty myszki i wykrywa kolizje
	void refreshResize(float width, float height);
	virtual void Run(sf::RenderWindow& App);
	int* Action;
	void setHighscore(int score)
	{
		highScore = score;
		buttons[2]->setText(std::to_string(score));
		buttons[2]->SetGlobalBoundsToMiddle();
	}
	int highScore = 0;


private:
	std::string playername = " ";
	bool isCoursorOnButton = 0;
	int selectedItemIndex;
	int selectedItemIndexFlag = 0;
	sf::Font font; //czcionka
	Button* buttons[MENU_NUMBER_OF_ITEMS+2];
	sf::Texture menuBackgroundTexture;
	sf::Sprite menuBackgroundSprite;
	sf::SoundBuffer menuBackgroundMusic;
	sf::Vector2i coursorPos;
	sf::Event menuEvent;
};
#endif#pragma once
