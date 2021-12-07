#pragma once
#include "Goodies.h"
#include "Entity.h"

class Explosion : public Entity
{
public:

	Explosion(int rad, int size, float x, float y)
	{
		radius = rad;
		xCoord = x;
		yCoord = y;
		explosionSize = size;
		explosion.setRadius(radius);
		explosion.setOrigin(explosionSize, explosionSize);
		explosion.setPosition(sf::Vector2f(xCoord, yCoord));
		explosion.setFillColor(sf::Color::Red);
	}

	~Explosion() {}
	;

	int exploded(int rad)
	{
		int radRet = rad + 3;
		return radRet;
	}

	void explode() {
		radius = exploded(radius);
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(explosion);
	}

	void refresh()
	{
		this->explode();
		explosion.setRadius(radius);
		explosion.setOrigin(radius, radius);
	}

	//variables
	int explosionSize;

private:
	sf::CircleShape explosion;
};