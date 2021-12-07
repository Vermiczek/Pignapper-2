#ifndef MAINMENU_H
#define MAINMENU_H
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Button.h"
#include <vector>
#include "Goodies.h"
#define MENU_NUMBER_OF_ITEMS 5

class MainMenu
{
public:
	MainMenu(float width, float height, int &Action); //konstruktor menu
	~MainMenu(); //destruktor menu
	void draw(sf::RenderWindow& window); //rysuje menu we wskazanym oknie
	void MoveUp(); //zmniejsza indeks wyroznionej opcji w menu oraz przeskakuje po wykroczeniu poza zakres
	void MoveDown(); //zwieksza indeks wyroznionej opcji w menu oraz przeskakuje po wykroczeniu poza zakres
	void checkIndex(); //zmienia podswietlenie przyciskow w zaleznosci od indexow
	int Select(sf::RenderWindow& window); //zatwierdza wybór
	void CapitalizeButton(); //gowno
	void deCapitalizeButton(); //pizda
	void Events(sf::RenderWindow& window);
	void MouseDetect(sf::RenderWindow& window); //pobiera koordynaty myszki i wykrywa kolizje
	void refreshResize(float width, float height);
	virtual void Run(sf::RenderWindow& App);
	int *Action;
	


private:
	bool isCoursorOnButton = 0;
	int selectedItemIndex;
	int selectedItemIndexFlag=0;
	sf::Font font; //czcionka
	Button *buttons[MENU_NUMBER_OF_ITEMS];
	sf::Texture menuBackgroundTexture;
	sf::Sprite menuBackgroundSprite;
	sf::SoundBuffer menuBackgroundMusic;
	sf::Vector2i coursorPos; 
	sf::Event menuEvent;
};
#endif