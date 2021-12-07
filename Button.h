#ifndef BUTTON_H
#define BUTTON_H
#include <iostream>
#include "SFML/Graphics.hpp"

class Button
{
public:
	Button(std::string fontStr, std::string textStr, sf::Color color, int size, sf::Vector2f position);
	void SetGlobalBoundsToMiddle();
	//konstruktor przycisku
	~Button(); //destruktor przycisku
	void drawButton(sf::RenderWindow& window); //"wyrysuj" przycisk
	void setButtonTextColor(sf::Color color); //nadaje kolor tekstu
	void setButtonTextSize(int size); //nadaje rozmiar tekstu
	void CapitalizeQuick(); //gowno
	bool detectCollision(sf::Vector2f target); //wykrywa kolizje hitboxu z kursorem
	void deCapitalizeQuick(); //pizda
	void setText(std::string text)
	{
		this->text.setString(text);
	}

private:
	std::string name;
	sf::RectangleShape hitbox;
	sf::Text text;
	sf::Font font;
	sf::Color color;
	int size=50;
};

#endif
