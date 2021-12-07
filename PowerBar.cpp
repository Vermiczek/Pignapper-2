#include "PowerBar.h"

PowerBar::PowerBar(double x, double y, double xs, double ys)
{
	xCoord = x;
	xSize = xs;
	yCoord = y;
	ySize = ys;
	powerBar.setSize(sf::Vector2f(xSize, ySize));
	powerBar.setPosition(sf::Vector2f(xCoord, yCoord));
	powerBar.setOrigin(0, 0);
	powerBar.setFillColor(sf::Color::Red);
}

PowerBar::~PowerBar()
{

}

void PowerBar::refresh(double x, double y, int powerLevel)
{
	xCoord = x - 25;
	yCoord = y + 50;
	xSize = powerLevel;
	powerBar.setPosition(sf::Vector2f(xCoord, yCoord));
	powerBar.setSize(sf::Vector2f(xSize, ySize));
}

void PowerBar::draw(sf::RenderWindow& window)
{
	window.draw(powerBar);
}