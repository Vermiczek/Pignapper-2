#include "GameState.h"
#include <stdlib.h>    
#include <time.h>    
#include <math.h>
#include <Windows.h>

GameState::GameState()
{
	powerbar = PowerBar(400, 400, 10, 10);
	CreatePlatforms();
	spawnTimer = spawnTimerLimit;
	if (!this->platformTexture.loadFromFile("platform.png"))
	{
		std::cout << "Error loading platform texture" << std::endl;
	}
	else
	{
		sf::Vector2u TextureSize = platformTexture.getSize();
		float ScaleX = (float)150 / TextureSize.x;
		float ScaleY = (float)30 / TextureSize.y;
		platformSprite.setTexture(platformTexture);
		platformSprite.setScale(ScaleX, ScaleY);
		platformSprite.setPosition(400, 400);
	}

	platformTexturePointer = &platformTexture;
	
}

void GameState::spawnSingleEnemy(int type, double x, double y)
{
	enemies.push_back(Enemy(0,x,y));
}

void GameState::spawnTimerLimitAlghoritm() {
	int substraction = timer/10;
	spawnTimerLimit = spawnTimerLimitDefault - substraction;
	if (spawnTimerLimit < 100)
	{
		spawnTimerLimit = 100;
	}
}

void GameState::spawner()
{
	if (spawnTimer > spawnTimerLimit)
	{
		spawnTimer = 0;
		spawnRandomEnemy(Shooter);
	}
}
void GameState::spawnRandomEnemy(int type)
{

	srand(time(NULL));

	int x, y;

	int location = rand() % 4;
	if (location == 0)
	{
		x = -30;
		y = -30;
	}
	else if (location == 1)
	{
		x = 1024 + 30;
		y = 768 + 30;
	}
	else if (location == 2)
	{
		x = -30;
		y = 768 + 30;
	}
	else if (location == 3)
	{
		x = 1024 + 30;
		y = -30;
	}
	int enemytype = rand() % 6;
	enemies.push_back(Enemy(enemytype, x, y));
}


void GameState::drawObject(int xCoord, int yCoord)
{

}

void GameState::draw(sf::RenderWindow& window)
{
	player.draw(window);
	for (std::vector<Platform>::iterator it = platforms.begin(); it != platforms.end(); ++it)
	{
		it->draw(window);
	}
	for (auto it = arrows.begin(); it != arrows.end(); ++it)
	{
		it->draw(window);
	}

	for (auto it = explosions.begin(); it != explosions.end(); ++it)
	{
		it->draw(window);
	}

	for (auto it = enemies.begin(); it != enemies.end(); ++it)
	{   
		it->draw(window);
		//std::cout << "X: " << it->xCoord << "Y: " << it->yCoord << std::endl;
	}
	powerbar.draw(window);
}


void GameState::updateExplosion()
{
	for (int i = 0; i<explosions.size();i++)
	{
		if (explosions[i].radius > explosions[i].explosionSize)
		{
			explosions.erase(explosions.begin() + i);
			i--;
		}
		else
		{
		}
	}
}

void GameState::refresh()
{
	spawnTimerLimitAlghoritm();
	timer += 1;
	spawnTimer += 1;
	player.refresh();
	playerPlatformCollision();
	player.entityOutOfBounds();
	setPlayerDirection();
	Detonate();
	DrawArrow();
	powerbar.refresh(player.xCoord, player.yCoord, shotPower);
	for (auto it = arrows.begin(); it != arrows.end(); ++it)
	{
		it->arrowOutOfBounds();
		it->refresh();
	}
	EraseArrowFromExistence();
	for (auto it = platforms.begin(); it != platforms.end(); ++it)
	{
		it->platformSetPosition(440, 400, 250, platformTexture);
		//std::cout << it->xCoord<<std::endl;
	}
	ArrowCollisionEvent();
	EnemyCollisionEvent(0.025);
	updateExplosion();
	killEnemy(enemies);
	for (auto it = enemies.begin(); it != enemies.end(); ++it)
	{
		it->incrementInterval();
		it->refresh();
		it->entityOutOfBounds();
		it->goTowardsTarget(player.xCoord, player.yCoord);
		if (player.collisionsOn)
			livingEntitiesCollisionEvent(it, player, 0.5, 0.5);
		if (it->shootInterval > it->shootIntervalVal) {
			enemyShootArrowAtPlayer(*it, player);
			it->shootInterval = 0;
		}
	}
	player.resetInvulnerability();
	for (auto it = explosions.begin(); it != explosions.end();it++)
	{
		it->refresh();
	}
	lookForExplosionCollisions();
	ArrowEntityCollisionLoop();
	spawner();
	//playerPlatformCollisionPredict();
} 

void GameState::ArrowEntityCollisionLoop() {
	for (int i = 0; i < arrows.size(); i++)
	{
		for (int t = 0; t < enemies.size(); t++)
		{
			if (livingEntityArrowCollision(enemies[t], arrows[i]))
			{
				if (arrows[i].arrowType != EnemyBullet && arrows[i].landed != 1 && arrows[i].arrowType != EnemyBigBullet && arrows[i].arrowType != EnemyRocket) {
					arrowEntityCollisionEvent(enemies[t], arrows[i], 0.25, 0.25);
					enemies[t].dealDamage(arrows[i].arrowDamage);
					//std::cout << "Enemy " << t << " hp: " << enemies[t].hp;
					if (arrows[i].arrowType == PlayerArrow)
					{
						arrows[i].markForRemoval = 1;
					}
				}
			}
		}
		if (livingEntityArrowCollision(player, arrows[i]) && (arrows[i].arrowType == EnemyBullet || arrows[i].arrowType == EnemyBigBullet || arrows[i].arrowType == EnemyRocket))
		{
			if (player.collisionsOn && arrows[i].arrowType != EnemyRocket) {
				arrowEntityCollisionEvent(player, arrows[i], 0.25, 0.25);
				player.ChangeHP(-20);
				arrows[i].markForRemoval = 1;
			}
			else if (player.collisionsOn && arrows[i].arrowType == EnemyRocket)
			{
				player.ChangeHP(-10);
				arrows[i].markForDetonation = 1;
			}
		}
		if (arrows[i].markForRemoval == 1)
		{
			arrows.erase(arrows.begin() + i);
			i--;
		}
	}
}

void GameState::playerJump(bool dir)
{
	if (dir)
		player.Jump(1);
	else
		player.Jump(0);
}

void GameState::setPlayerDirection()
{
	if (AkeyDown == 1)
		player.setDirection(1);
	if (DkeyDown == 1)
		player.setDirection(2);
	if(AkeyDown + DkeyDown == 2)
		player.setDirection(0);
	if(AkeyDown + DkeyDown == 0)
		player.setDirection(0);
	if (spaceDown == 1)
		if(blockFreeze!=1)
			playerFreeze();
}

void GameState::setKeyDowns(bool aord)
{
	if (aord)
	{
		AkeyDown = 1;
	}
	if (!aord)
		DkeyDown = 1;
}

void GameState::ShootArrow(int xMouse, int yMouse)
{  
	if (shotPower > 0) {
		float xDif;
		float yDif;
		int ratioDeg = 0;
		int ratioReverse = 1;
		int playerXcentre = player.xCoord;
		int playerYcentre = player.yCoord;
		yDif = sqrt((yMouse - playerYcentre) * (yMouse - playerYcentre));
		xDif = sqrt((xMouse - playerXcentre) * (xMouse - playerXcentre));
		float aglTg = yDif / xDif;
		double xVelocity = cos(atan(aglTg)) * shotPower/4;
		double yVelocity = sin(atan(aglTg)) * shotPower/4;
		if (xMouse<playerXcentre && yMouse>playerYcentre) {
			ratioDeg = 2;
			ratioReverse = -1;
			xVelocity = -xVelocity;
		}
		if (xMouse > playerXcentre && yMouse < playerYcentre) {
			ratioDeg = 0;
			ratioReverse = -1;
			yVelocity = -yVelocity;
		}
		if (xMouse < playerXcentre && yMouse < playerYcentre) {
			ratioDeg = 2;
			ratioReverse = 1;
			xVelocity = -xVelocity;
			yVelocity = -yVelocity;
		}
		double aglRot = ratioReverse * (atan(aglTg) * 180 / 3.14159412412 + 90 * ratioDeg);
		shotPower = 0;
		drawingArrow = 0;
		if (chosenWeapon == 0)
			arrows.push_back(Arrow(playerXcentre, playerYcentre, aglRot, xVelocity+player.xVelocity, yVelocity+player.yVelocity, PlayerGrenade));
		if (chosenWeapon == 1)
		{
			arrows.push_back(Arrow(playerXcentre, playerYcentre, aglRot, xVelocity * 1.75 + player.xVelocity, yVelocity * 1.75 + player.yVelocity, PlayerArrow));
		}
	}
}


void GameState::enemyShootArrowAtPlayer(Enemy enemy, Player player)
{
		float xDif;
		float yDif;
		float speed=100;
		int ratioDeg = 0;
		int ratioReverse = 1;
		int enemyXcentre = enemy.xCoord + enemy.radius;
		int enemyYcentre = enemy.yCoord + enemy.radius;
		yDif = sqrt((player.yCoord - enemyYcentre) * (player.yCoord - enemyYcentre));
		xDif = sqrt((player.xCoord - enemyXcentre) * (player.xCoord - enemyXcentre));
		float aglTg = yDif / xDif;
		speed = enemy.bulletSpeed;  
		double xVelocity = cos(atan(aglTg))*speed;
		double yVelocity = sin(atan(aglTg))*speed;
		if (player.xCoord<enemyXcentre && player.yCoord>enemyYcentre) {
			ratioDeg = 2;
			ratioReverse = -1;
			xVelocity = -xVelocity;
		}
		if (player.xCoord > enemyXcentre && player.yCoord < enemyYcentre) {
			ratioDeg = 0;
			ratioReverse = -1;
			yVelocity = -yVelocity;
		}
		if (player.xCoord < enemyXcentre && player.yCoord < enemyYcentre) {
			ratioDeg = 2;
			ratioReverse = 1;
			xVelocity = -xVelocity;
			yVelocity = -yVelocity;
		}
		double aglRot = ratioReverse * (atan(aglTg) * 180 / 3.14159412412 + 90 * ratioDeg);
		arrows.push_back(Arrow(enemyXcentre, enemyYcentre, aglRot, xVelocity / 2, yVelocity / 2, enemy.bulletType));
}

void GameState::DrawArrow()
{  
		if (drawingArrow) {
			if(shotPower <75)
			shotPower = shotPower + 1;
		};
}

void GameState::explosionHit(Explosion explosion, Entity& entity)
{
	double xDif, yDif;
	yDif = sqrt((entity.yCoord - explosion.yCoord) * (entity.yCoord - explosion.yCoord));
	xDif = sqrt((entity.xCoord - explosion.xCoord) * (entity.xCoord - explosion.xCoord));
	float aglTg = yDif / xDif;
	double xVelocity = cos(atan(aglTg)) * 10;
	double yVelocity = sin(atan(aglTg)) * 10;
	if (entity.xCoord<explosion.xCoord && entity.yCoord > explosion.yCoord) {
		xVelocity = -xVelocity;
	}
	if (entity.xCoord > explosion.xCoord && entity.yCoord < explosion.yCoord) {
		yVelocity = -yVelocity;
	}
	if (entity.xCoord < explosion.xCoord && entity.yCoord < explosion.yCoord) {
		xVelocity = -xVelocity;
		yVelocity = -yVelocity;
	}
	//std::cout << xVelocity << yVelocity;
	entity.xVelocity = entity.xVelocity + xVelocity;
	entity.yVelocity = entity.yVelocity + yVelocity;
	//std::cout << entity.xVelocity;
};

void GameState::markForDetonation()
{
	for (auto it = arrows.begin(); it != arrows.end(); ++it)
	{
		if (it->arrowType == PlayerGrenade || it->arrowType == EnemyRocket)
		{
			it-> markForDetonation = 1;
			//it--;
		}
	}
}

void GameState::Detonate()
{
	for (int i = 0; i < arrows.size(); i++)
	{
		if (arrows[i].arrowType == PlayerGrenade || arrows[i].arrowType == EnemyRocket) {
			if (arrows[i].markForDetonation == 1)
			{
				int explosionSize;
				if (arrows[i].arrowType == EnemyRocket)
					explosionSize = 50;
				else
					explosionSize = 100;

				explosions.push_back(Explosion(5, explosionSize, arrows[i].xCoord, arrows[i].yCoord));
				arrows.erase(arrows.begin() + i);
				i--;
			}
		}
	}
}


void GameState::EraseArrowFromExistence()
{
	for (int i = 0; i < arrows.size(); i++)
	{
		arrows[i].arrowTimer += 1;
	    if (arrows[i].arrowTimer == arrows[i].arrowTimeLimit)
			{
				arrows.erase(arrows.begin() + i);
				i--;
			}
	}
}


void GameState::ResetKeyDowns(bool aord)
{
	if (aord)
	{
		AkeyDown = 0;
	}
	if (!aord)
		DkeyDown = 0;
}

void GameState::CreatePlatform(int xCoord, int yCoord, int xSize, int ySize, int id)
{
	platforms.push_back(Platform(xCoord, yCoord, xSize, ySize, id, platformTexture));
	std::cout << "Platofmr created." << std::endl;
	std::cout << platformTexture.getSize().x;
}

void GameState::CreatePlatforms()
{
	CreatePlatform(100, 250, 150, 30, 1);
	CreatePlatform(100, 250, 150, 30, 2);
	CreatePlatform(100, 250, 150, 30, 3);
	CreatePlatform(100, 250, 150, 30, 4);
	CreatePlatform(100, 250, 150, 30, 5);
	CreatePlatform(100, 250, 150, 30, 6);
}

void GameState::makeExplosion()
{
}

bool GameState::killEnemy(std::vector<Enemy>& enemy)
{
	for (int i = 0; i < enemy.size(); i++)
	{
		if (enemy[i].hp <= 0)
		{   
			if (enemy[i].enemyType == SmallCharger)
			{
				explosions.push_back(Explosion(5, 50, enemy[i].xCoord, enemy[i].yCoord));
			}
			if (enemy[i].enemyType == BigCharger)
			{
				explosions.push_back(Explosion(5, 100, enemy[i].xCoord, enemy[i].yCoord));
			}
			enemy.erase(enemy.begin() + i);
			player.hp += 5;
			i--;
		}
	}
	return true;
}