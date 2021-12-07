#pragma once
#include "Entity.h"

class Platform : public Entity
{
public:
	void draw(sf::RenderWindow& window);
	Platform(int x, int y, int xs, int ys, int id, sf::Texture &spr);
	Platform(int x, int y, int xs, int ys, int id, sf::Texture* spr);
	//Platform(int x, int y, int xs, int ys, int id, sf::Texture spr);
	Platform(int x, int y, int xs, int ys, int id, sf::Sprite spr);
	//Platform(int x, int y, int xs, int ys, int id, sf::Sprite spr);
	//Platform(int x, int y, int xs, int ys, int id, sf::Sprite spr);
	~Platform();
	void platformSetPosition(int xCentre, int yCentre, int distanceFromCenter, sf::Texture& tx);
	void platformSetPosition(int xCentre, int yCentre, int distanceFromCenter, sf::Sprite tex);
	void platformSetPosition(int xCentre, int yCentre, int distanceFromCenter);
	sf::Sprite platformSprite;
	sf::Texture* platformTexturePtr;
	sf::Texture platformTexture;
	sf::RectangleShape platformHitbox;
	int xSize;
	int ySize;
	int id;
	double spin = 0;

};