#include "Arrow.h"
#include <Windows.h>

Arrow::Arrow(float x, float y, float agl, int xVel, int yVel, int type)
{ 
	xCoord = x;
	yCoord = y;
	previousx = x;
	previousy = y;
	angle = agl;
	arrowType = type;
	xVelocity = xVel;
	yVelocity = yVel;
	arrowHitbox.setPosition(x, y);
	if (arrowType == PlayerArrow)
	{
		arrowDamage = 100;
		radius = 5;
		arrowHitbox.setRadius(radius);
		gravityVal = 1;
	}
	else if (arrowType == PlayerGrenade)
	{
		arrowDamage = 50;
		arrowTimeLimit = -1;
		radius = 10;
		arrowHitbox.setRadius(radius);
		gravityVal = 1;
	}
	else if (arrowType == EnemyBullet)
	{
		arrowDamage = 10;
		radius = 5;
		arrowHitbox.setRadius(radius);
		gravityVal = 0;
	}
	else if (arrowType == EnemyBigBullet)
	{
		arrowDamage = 15;
		radius = 15;
		arrowHitbox.setRadius(radius);
		gravityVal = 0;
	}
	else if (arrowType == EnemyRocket)
	{
		arrowDamage = 10;
		radius = 15;
		arrowHitbox.setRadius(radius);
		gravityVal = 0;
		arrowTimeLimit = 9999;
	}
	arrowHitbox.setOrigin(radius, radius);
	arrowHitbox.setFillColor(sf::Color::Blue);
	sf::Vector2f position = sf::Vector2f(xCoord, yCoord);
}

void Arrow::draw(sf::RenderWindow& window)
{
	//arrowSprite.setTexture(arrowTexture);
	//window.draw(Arrow::arrowSprite);
	window.draw(arrowHitbox);
}

void Arrow::refresh()
{
	RefreshPosition();
	calcVelocity();
	CalcAngle();
}

void Arrow::CalcAngle()
{
	angle = (atan(yVelocity / xVelocity)*180/3.14);
	arrowSprite.setRotation(angle);
}

void Arrow::calcVelocity()
{
	if (landed){
		xVelocity = 0;
	yVelocity = 0;
}
	yVelocity = yVelocity + (0.25*gravityVal);
}
