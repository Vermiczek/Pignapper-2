#include "Enemy.h"



void Enemy::draw(sf::RenderWindow& window)
{
	//playerSprite.setTexture(playerTexture);
	window.draw(Enemy::enemyHitbox);
}


void Enemy::refresh()
{
	enemyHitbox.setPosition(xCoord, yCoord);
	refreshPreviousPosition();
	moveEnemyVel();
	limitSpeed();
	//refeshVelocity();
}

void Enemy::limitSpeed()
{
	if (xVelocity > maxSpeed)
		xVelocity = maxSpeed;
	if (xVelocity < -maxSpeed)
		xVelocity = -maxSpeed;
	if (yVelocity > maxSpeed)
		yVelocity = maxSpeed;
	if (yVelocity < -maxSpeed)
		yVelocity = -maxSpeed;
}


void Enemy::refreshPreviousPosition()
{
	previousx = xCoord;
	previousy = yCoord;
}

void Enemy::goTowardsTarget(int targetXcoord, int targetYcoord)
{
	sf::Vector2f aimDir;
	sf::Vector2f aimDirNorm;
   
	sf::Vector2f targetCenter = sf::Vector2f(targetXcoord,targetYcoord);
	sf::Vector2f enemyCenter = sf::Vector2f(this->xCoord, this->yCoord);
	aimDir = targetCenter - enemyCenter;
	float xLen = sqrt(pow(aimDir.x, 2));
	float yLen = sqrt(pow(aimDir.y, 2));
	float tempDenominator = xLen + yLen;
	if (tempDenominator != 0) {
		/*std::cout << "aimdirx " << targetCenter.x << std::endl;
		std::cout << "aimdiry " << targetCenter.y << std::endl;
		std::cout << "denominator" << tempDenominator << std::endl;*/
		float xDir = 1;
		float yDir = 1;
		if (targetCenter.x < enemyCenter.x)
		{
			xDir = -1;
		}
		if (targetCenter.y < enemyCenter.y)
		{
			yDir = -1;
		}
		float xVelRatio = xLen / tempDenominator;
		float yVelRatio = yLen / tempDenominator;
		if(sqrt(xLen * xLen + yLen * yLen) <=300&&this->enemyType==Wkurwiacz){
			this->xVelocity = this->xVelocity - acceleration * xVelRatio * xDir;
			this->yVelocity = this->yVelocity - acceleration * yVelRatio * yDir;
		}
		else {
			this->xVelocity = this->xVelocity + acceleration * xVelRatio * xDir;
			this->yVelocity = this->yVelocity + acceleration * yVelRatio * yDir;
		}
	}

}

void Enemy::moveEnemyVel()
{
	xCoord = xCoord + xVelocity;
	yCoord = yCoord + yVelocity;
}