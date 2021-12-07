#include "Player.h"
#include <iostream>

Player::Player(int setHP, int x, int y, int xs, int ys)
{
	hp = setHP;
	xSize = xs;
	ySize = ys;
	xCoord = x;
	yCoord = y;
	radius = xSize/2;
	previousx = x;
	previousy = y;
	sf::Vector2f position = sf::Vector2f(x, y);

	if (playerTexture.loadFromFile("swinia.png"))
	{
		hitbox.setPosition(position);
		hitbox.setRadius(radius);
		hitbox.setOrigin(radius, radius);
	}
	else
		std::cout << "error";
}

void Player::draw(sf::RenderWindow& window)
{
	playerSprite.setTexture(playerTexture);
	window.draw(Player::hitbox);
}

Player::~Player()
{

}

void Player::ChangeHP(int value)
{
	this->hp = this->hp + value;
}

void Player::refresh()
{
	hitbox.setPosition(xCoord, yCoord);
	refreshPreviousPosition();
	movePlayerVel();
	refeshVelocity();
}

void Player::setDirection(int dir)
{
	horizontalMovement = dir;
}

void Player::refeshMovementVelocity()
{
	if (horizontalMovement == Stay)
	{
		if (xVelocity > 0 && onTopOfPlatform)
			xVelocity = xVelocity - 1;
		if (xVelocity < 0&& onTopOfPlatform)
			xVelocity = xVelocity + 1;

	}
	if (horizontalMovement == 1 && xVelocity<8)
	{
		xVelocity = xVelocity + 2;
	}
	if (horizontalMovement == 2 && xVelocity > -8)
	{
		xVelocity = xVelocity - 2;
	}
	if (xVelocity > 8)
		if(onTopOfPlatform)
			xVelocity = xVelocity - 3;
	if (xVelocity < -8)
		if (onTopOfPlatform)
			xVelocity = xVelocity + 3;
}

void Player::refreshPreviousPosition()
{
	previousx = xCoord;
	previousy = yCoord;
}

void Player::movePlayerVel()
{
	xCoord = xCoord + xVelocity;
	yCoord = yCoord + yVelocity;
}

void Player::refeshGravityVerticalVelocity()
{
 
	yVelocity = yVelocity+0.5;

	if (yVelocity > 10)
		yVelocity = 10;
}
void Player::refeshVelocity()
{
	refeshGravityVerticalVelocity();
	refeshMovementVelocity();
}

void Player::ToggleTopCollision(bool value)
{
	onTopOfPlatform = value;
}

void Player::ToggleBotCollision(bool value)
{
	onBottomOfPlatform = value;
}

void Player::ToggleSideCollision(bool value)
{
	onSideOfPlatform = value;
}

void Player::Jump(bool dir)
{   
	if (dir)
		yVelocity = yVelocity - 10;
	else
		yVelocity = yVelocity + 10;
	onTopOfPlatform = 0;
}