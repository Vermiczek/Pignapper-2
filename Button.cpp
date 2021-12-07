#include "Button.h"

Button::Button(std::string fontStr, std::string textStr, sf::Color color, int size, sf::Vector2f position)
{
	
	if (!font.loadFromFile(fontStr))
	{
		// handle error
	};

	text.setFont(font);
	text.setFillColor(color);
	text.setString(textStr);
	text.setCharacterSize(size);
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	text.setPosition(position);
	text.setOutlineThickness(2);
	text.setOutlineColor(sf::Color(0, 0, 0));
	float width = text.getLocalBounds().width;
	float height = text.getLocalBounds().height;
	hitbox.setSize(sf::Vector2f(width, height));
	hitbox.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	hitbox.setPosition(position);
	hitbox.setFillColor(sf::Color::Transparent);
}

void Button::SetGlobalBoundsToMiddle()
{
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	hitbox.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
}
Button::~Button()
{

}

void Button::drawButton(sf::RenderWindow& window)
{
	window.draw(text);
}

void Button::setButtonTextColor(sf::Color color)
{
	text.setFillColor(color);
}

void Button::setButtonTextSize(int size)
{
	text.setCharacterSize(size);
}

bool Button::detectCollision(sf::Vector2f target)
{
	sf::FloatRect boundingBox = hitbox.getGlobalBounds();
	if (boundingBox.contains(target))
		return 1;
	else
		return 0;
}

void Button::CapitalizeQuick()
{
	text.setCharacterSize(70);
	text.setFillColor(sf::Color(0, 0, 0));
}

void Button::deCapitalizeQuick()
{
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::White);
}