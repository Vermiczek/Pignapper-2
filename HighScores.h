#ifndef HIGHSCORES_H
#define HIGHSCORES_H
#include "Goodies.h"
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Button.h"
#include <fstream>
#include <string>
#include "Goodies.h"
#define MAX_NUMBER_OF_ITEMS 3


class HighScores
{
public:
	HighScores(float width, float height, int& ActionX); //konstruktor menu
	~HighScores(); //destruktor menu
	sf::Sprite SetSpriteScaled(sf::RenderWindow window, sf::Texture texture);
	void draw(sf::RenderWindow& window); //rysuje menu we wskazanym oknie
	void getTexts();
	void MoveUp(); //zmniejsza indeks wyroznionej opcji w menu oraz przeskakuje po wykroczeniu poza zakres
	void MoveDown(); //zwieksza indeks wyroznionej opcji w menu oraz przeskakuje po wykroczeniu poza zakres
	void checkIndex(); //zmienia podswietlenie przyciskow w zaleznosci od indexow
	int Select(sf::RenderWindow& window); //zatwierdza wybór
	void scrollList(int value, int& scrollValue, int size);
	void CapitalizeButton(); //gowno
	void deCapitalizeButton(); //pizda
	void Events(sf::RenderWindow& window);
	void readHiscores();
	void MouseDetect(sf::RenderWindow& window); //pobiera koordynaty myszki i wykrywa kolizje
	virtual void Run(sf::RenderWindow& App);
	int* Action;

private:
	bool isCoursorOnButton = 0;
	int selectedItemIndex;
	int selectedItemIndexFlag = 0;
	sf::Font font; //czcionka
	Button* buttons[MAX_NUMBER_OF_ITEMS];
	sf::Texture hiscoresBackgroundTexture;
	sf::Sprite hiscoresBackgroundSprite;
	sf::SoundBuffer hiscoresBackgroundMusic;
	sf::Vector2i coursorPos;
	sf::Event hiscoresEvent;
	std::vector<highScore> highScores;
	std::ofstream highScoresFile;
	sf::Text texts[10];
	int scroll;
};

#endif