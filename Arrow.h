#include "Goodies.h"
#include "Entity.h"
#include <math.h>
#pragma once
enum type {PlayerArrow, PlayerGrenade, EnemyBullet, EnemyBigBullet, EnemyRocket};

class Arrow : public Entity
{
public:
	Arrow(float x, float y, float agl, int xVel, int yVel, int type);
	void draw(sf::RenderWindow& window);
	void refresh();
	void CalcAngle();
	void RefreshPosition()
	{
		previousx = xCoord;
		previousy = yCoord;
		xCoord = xCoord + xVelocity;
		yCoord = yCoord + yVelocity;
		sf::Vector2f position = sf::Vector2f(xCoord, yCoord);
		arrowHitbox.setPosition(position);
		arrowHitbox.setOrigin(radius, radius);
		//arrowSprite.setPosition(position);
	}
	void arrowOutOfBounds()
	{
		if (xCoord < (0 - 40 - radius * 2))
			markForRemoval = 1;
		if (xCoord > (1024 + 40 + radius * 2))
			markForRemoval = 1;
		if (yCoord < (0 - 40 - radius * 2))
			markForRemoval = 1;
		if (yCoord > (768 + 40 + radius * 2))
			markForRemoval = 1;
	}
	void calcVelocity();
	float Velocity = 10;
	float previousxVel;
	float previousyVel;
	bool markForRemoval = 0;
	bool markForDetonation = 0;
	bool landed = 0;
	int arrowType;
	int arrowDamage;
	float gravityVal = 0;
	int arrowTimer = 0;
	int arrowTimeLimit = 100;

private:
	float angle = 0;
	sf::CircleShape arrowHitbox;
	sf::Sprite arrowSprite;
	sf::Texture arrowTexture;
};