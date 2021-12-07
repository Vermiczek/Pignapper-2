#pragma once
#include "Goodies.h"
enum HorizontalMovement { Stay, Left, Right };

class Entity {

public:
	int xSize;
	int ySize;
	int radius;
	float xVelocity = 0;
	float yVelocity = 0;
	int previousx = 0;
	int previousy = 0;
	int xCoord = 0;
	int yCoord = 0;
	sf::Sprite entitySprite;
	std::shared_ptr<sf::Sprite> entitySpritePtr;
	bool taggedForRemoval;
	bool hasCollisionOccured()
	{
	}
	int hp = 1000000000;
	void dealDamage(int value)
	{
		hp -= value;
	}
	void entityOutOfBounds()
	{
		if (xCoord < (0 - 40 - radius * 2))
			xCoord = 1024 + radius * 2 + 40;
		if (xCoord > (1024 + 40 + radius * 2))
			xCoord = -40 - radius * 2;
		if (yCoord < (0 - 40 - radius * 2))
			yCoord = 768 + 40 + radius * 2;
		if (yCoord > (768 + 40 + radius * 2))
			yCoord = 0 - 40 - radius * 2;
	}
	void showHP() {
		std::cout << "HP " << this->hp << std::endl;
	}
};