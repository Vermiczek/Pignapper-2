#include "Goodies.h"
#pragma once

class PowerBar
{
public:
	PowerBar(double x, double y, double xs, double ys);
	~PowerBar();
	void refresh(double x, double y, int powerLevel);
	void draw(sf::RenderWindow& window);

private:
	sf::RectangleShape powerBar;
	double xSize;
	double ySize;
	double xCoord;
	double yCoord;
};