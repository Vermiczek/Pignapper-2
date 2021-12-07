#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Button.h"
#include <vector>
#include "Goodies.h"
#include "GameState.h"

class GameScreen
{
public:
	GameScreen(float width, float height, int& Action);
	~GameScreen();
	void draw(sf::RenderWindow& window, GameState gameState);
	void MoveUp(); //zmniejsza indeks wyroznionej opcji w menu oraz przeskakuje po wykroczeniu poza zakres
	void MoveDown(); //zwieksza indeks wyroznionej opcji w menu oraz przeskakuje po wykroczeniu poza zakres
	void checkIndex(); //zmienia podswietlenie przyciskow w zaleznosci od indexow
	int Select(sf::RenderWindow& window); //zatwierdza wybór
	void CapitalizeButton(); //gowno
	void deCapitalizeButton(); //pizda
	void Events(sf::RenderWindow& window);
	void MouseDetect(sf::RenderWindow& window); //pobiera koordynaty myszki i wykrywa kolizje
	virtual void Run(sf::RenderWindow& App);
	int* Action;
	void playerMovementInput(int value);
	int PlayerHP() {
		return game.returnPlayerHp();
	}
	int returnCalculatedScore()
	{
		return game.timer / 10;
	}
	GameState game;
	sf::Sprite platformSprite;
	sf::Texture platformTexture;

private:
	bool isCoursorOnButton = 0;
	int selectedItemIndex;
	int selectedItemIndexFlag = 0;
	sf::Font font; //czcionka
	Button* buttons[100];
	sf::Texture BackgroundTexture;
	sf::Sprite BackgroundSprite;
	sf::SoundBuffer BackgroundMusic;
	sf::Vector2i coursorPos;
	sf::Event gameEvent;
};
