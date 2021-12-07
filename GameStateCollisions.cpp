#include "GameState.h"

void GameState::playerPlatformCollision()
{
	for (std::vector<Platform>::iterator it = platforms.begin(); it != platforms.end(); ++it)
	{
		player.ToggleSideCollision(false);
		player.ToggleTopCollision(false);
		player.ToggleBotCollision(false);
		if (detectCollision(it) || predictCollision(it))
		{
			sf::Texture nulltexture;
			Platform uwu = Platform(it->xCoord, it->yCoord, it->xSize, it->ySize, 0, nulltexture);
			if ((player.xCoord + player.radius - 5 < uwu.xCoord) || (player.xCoord - player.radius + 5 > uwu.xCoord + uwu.xSize))
			{
				player.ToggleSideCollision(true);
				PlayerCollisionEvent(uwu);
				break;
			}
			else if (player.yVelocity < 0 && player.yCoord>uwu.yCoord)
			{
				player.ToggleBotCollision(true);
				PlayerCollisionEvent(uwu);
				break;
			}
			else if ((player.yVelocity > 0 || player.yCoord + player.radius - 1 > uwu.yCoord))
			{
				player.ToggleTopCollision(true);
				PlayerCollisionEvent(uwu);
				break;
			}

		}
		else
			blockFreeze = 0;
	}
}

void GameState::playerPlatformCollisionPredict()
{
	for (std::vector<Platform>::iterator it = platforms.begin(); it != platforms.end(); ++it)
	{
		player.ToggleSideCollision(false);
		player.ToggleTopCollision(false);
		player.ToggleBotCollision(false);

		if (predictCollision(it))
		{
			sf::Texture nulltexture;
			Platform uwu = Platform(it->xCoord, it->yCoord, it->xSize, it->ySize, 0, nulltexture);
			if ((1))
			{
				player.ToggleSideCollision(true);
					PlayerCollisionEvent(uwu);
				break;
			}
			else if ((player.yVelocity > 0 || player.yCoord + player.radius - 1 > uwu.yCoord))
			{
				player.ToggleTopCollision(true);
				PlayerCollisionEvent(uwu);
				break;
			}
			else if (player.yVelocity < 0)
			{
				player.ToggleBotCollision(true);
				PlayerCollisionEvent(uwu);
				break;
			}
		}
	}
}

void GameState::PlayerCollisionEvent(Platform platform)
{
	if (player.onSideOfPlatform)
	{
		player.xVelocity = -player.xVelocity;
		if (player.xCoord + player.xVelocity < platform.xCoord)
			player.xCoord = platform.xCoord - player.radius;
		if (player.xCoord + player.xVelocity > platform.xCoord)
			player.xCoord = platform.xCoord + platform.xSize + player.radius;
	}
	if(player.onBottomOfPlatform)
	{
		if (player.yCoord < platform.yCoord+platform.ySize)
			player.yCoord = platform.yCoord + player.radius+platform.ySize;
		player.yVelocity = -player.yVelocity;
	}
	if (player.onTopOfPlatform)
	{
		if (player.yCoord > platform.yCoord)
			player.yCoord = platform.yCoord - player.radius;
		player.yVelocity = -player.yVelocity;
	}
}

void GameState::ArrowCollisionEvent()
{
	for (auto it = arrows.begin(); it != arrows.end(); it++)
	{
		for (auto itr = platforms.begin(); itr != platforms.end(); itr++)
		{
			if (detectArrowCollision(itr, it))
			{
				if (it->arrowType == PlayerGrenade) {
					if (detectSideArrowCollision(itr, it))
					{
						it->xVelocity = -it->xVelocity;
						if (it->xCoord + it->xVelocity < itr->xCoord)
							it->xCoord = itr->xCoord - it->radius;
						if (it->xCoord + it->xVelocity > itr->xCoord)
							it->xCoord = itr->xCoord + itr->xSize + it->radius;
						break;
					}
					else
					{
						if (sqrt((it->yVelocity) * (it->yVelocity)) > 0.5)
							it->yVelocity = -(it->yVelocity - (0.3 * it->Velocity));
						else
							it->yVelocity = 0;

						if (it->previousy < itr->yCoord)
							it->yCoord = itr->yCoord - it->radius - 1;
						if (it->previousy > itr->yCoord)
							it->yCoord = itr->yCoord + itr->ySize + it->radius + 1;

					}
				}
				if (it->arrowType == EnemyBigBullet) {
					if (detectSideArrowCollision(itr, it))
					{
						it->xVelocity = -it->xVelocity;
						if (it->xCoord + it->xVelocity < itr->xCoord)
							it->xCoord = itr->xCoord - it->radius;
						if (it->xCoord + it->xVelocity > itr->xCoord)
							it->xCoord = itr->xCoord + itr->xSize + it->radius;
						break;
					}
					else
					{
						it->yVelocity = - it->yVelocity;

						if (it->previousy < itr->yCoord)
							it->yCoord = itr->yCoord - it->radius - 1;
						if (it->previousy > itr->yCoord)
							it->yCoord = itr->yCoord + itr->ySize + it->radius + 1;

					}
				}
				if (it->arrowType == PlayerArrow||it->arrowType == EnemyBullet)
				{
					it->landed = 1;
				}
				if (it->arrowType == EnemyRocket)
				{
					it->markForDetonation= 1;
				}
			}
		}
	}
}

void GameState::EnemyCollisionEvent(float bounceRatio)
{
	for (auto it = enemies.begin(); it != enemies.end(); it++)
	{
		for (auto itr = platforms.begin(); itr != platforms.end(); itr++)
		{
			if (detectEnemyCollision(itr, it))
			{
					if (detectSideEnemyCollision(itr, it))
					{
						it->xVelocity = -it->xVelocity*bounceRatio/10;
						if (it->xCoord + it->xVelocity < itr->xCoord)
							it->xCoord = itr->xCoord - it->radius;
						if (it->xCoord + it->xVelocity > itr->xCoord)
							it->xCoord = itr->xCoord + itr->xSize + it->radius;
						break;
					}
					else
					{
						if (sqrt((it->yVelocity) * (it->yVelocity)) > 0.5)
							it->yVelocity = -it->yVelocity * bounceRatio/10;
						if (it->previousy < itr->yCoord)
							it->yCoord = itr->yCoord - it->radius - 1;
						if (it->previousy > itr->yCoord)
							it->yCoord = itr->yCoord + itr->ySize + it->radius + 1;
					}
			}
		}
	}
}

void GameState::livingEntitiesCollisionEvent(std::vector<Enemy>::iterator entity1, Entity &entity2, double ratio1, double ratio2)
{
	if (livingEntitiesCollision(entity1, entity2))
	{
		float collisionSpeedX = entity1->xVelocity - entity2.xVelocity;
		float collisionSpeedY = entity1->yVelocity - entity2.yVelocity;
		entity1->xVelocity = -collisionSpeedX;
		entity1->yVelocity = -collisionSpeedY;
		entity2.xVelocity = collisionSpeedX / 2;
		entity2.yVelocity = collisionSpeedY / 2;
		//std::cout << "Entity collision";
		player.collisionsOn = false;
		entity1->hp -= 20;
		entity2.hp -= 20;
	    
	}
}

void GameState::arrowEntityCollisionEvent(Entity& entity1, Entity& entity2, double ratio1, double ratio2)
{
	if (livingEntityArrowCollision(entity1, entity2))
	{
		float collisionSpeedX = entity1.xVelocity - entity2.xVelocity;
		float collisionSpeedY = entity1.yVelocity - entity2.yVelocity;
		entity1.xVelocity = -collisionSpeedX;
		entity1.yVelocity = -collisionSpeedY;
		entity2.xVelocity = collisionSpeedX / 2;
		entity2.yVelocity = collisionSpeedY / 2;
		//std::cout << "Entity collision";
		player.collisionsOn = false;
	}
}
bool GameState::livingEntitiesCollision(std::vector<Enemy>::iterator entity1, Entity entity2)
{
		float Dif = calculateDistance(entity1->xCoord, entity1->yCoord, entity2.xCoord, entity2.yCoord);
		//std::cout <<"Dif: "<<Dif<<std::endl<<"Radiuses sum: "<<entity.radius;
		if (Dif < (entity1->radius + entity2.radius))
		{
			return true;
		}
		else
			return false;
	}

bool GameState::livingEntityArrowCollision(Entity entity, Entity arrow)
{

	float Dif = calculateDistance(entity.xCoord, entity.yCoord, arrow.xCoord, arrow.yCoord);
	//std::cout <<"Dif: "<<Dif<<std::endl<<"Radiuses sum: "<<entity.radius;
	if (Dif < (entity.radius + arrow.radius))
	{
		return true;
	}
	return false;
}


bool GameState::detectCollision(std::vector<Platform>::iterator platform)
{
	if (((player.yCoord + player.radius) > (platform->yCoord)) && ((player.yCoord -player.radius) < (platform->yCoord + platform->ySize)))
	{
		if (((player.xCoord + player.radius) > platform->xCoord) && (player.xCoord-player.radius < (platform->xCoord + platform->xSize)))
		{
			return true;
		}
		else
			return false;
	}

	return false;
}

bool GameState::predictCollision(std::vector<Platform>::iterator platform)
{
	if (((player.yCoord + player.radius+player.yVelocity) > (platform->yCoord)) && ((player.yCoord - player.radius+player.yVelocity) < (platform->yCoord + platform->ySize)))
	{
		if (((player.xCoord + player.radius+player.xVelocity) > platform->xCoord) && (player.xCoord-player.radius+player.xVelocity < (platform->xCoord + platform->xSize)))
		{
			return true;
		}
		else
			return false;
	}

	return false;
}

bool GameState::detectSideCollision(std::vector<Platform>::iterator platform)
{
	if (((player.yCoord + player.radius) > (platform->yCoord)) && ((player.yCoord) < (platform->yCoord + platform->ySize)))
	{
		if (((player.xCoord + player.radius) > platform->xCoord) && (player.xCoord + player.radius - player.xVelocity) < platform->xCoord)
		{
			//std::cout << "Left Side collision";
			return true;
		}
		if (((player.xCoord - player.radius) < (platform->xCoord+platform->ySize)) && ((player.xCoord - player.radius) > (platform->xCoord + platform->ySize)))
		{
			//std::cout << "Right side collision";
			return true;
		}
		else
			return false;
	}
	return false;
}

bool GameState::detectSideArrowCollision(std::vector<Platform>::iterator platform, std::vector<Arrow>::iterator arrow)
{

	if (((arrow->yCoord + arrow->radius) > (platform->yCoord)) && ((arrow->yCoord - arrow->radius) < (platform->yCoord + platform->ySize)))
	{
		if (((arrow->xCoord + arrow->radius + arrow->xVelocity) > platform->xCoord) && (arrow->xCoord - arrow->radius + arrow->xVelocity < (platform->xCoord + platform->xSize)))
		{
			if (((arrow->xCoord + arrow->radius - 10) < platform->xCoord) || ((arrow->xCoord - arrow->radius + 10) > (platform->xCoord + platform->xSize)))
			{
				return true;
			}
		}
		if (((arrow->previousx + arrow->radius - 10) < platform->xCoord) || ((arrow->previousx - arrow->radius + 10) > (platform->xCoord + platform->xSize)))
		{
			return true;
		}
	}

	return false;
}

bool GameState::detectArrowCollision(std::vector<Platform>::iterator platform, std::vector<Arrow>::iterator arrow)
{
	if (((arrow->yCoord + arrow->radius) > (platform->yCoord)) && ((arrow->yCoord - arrow->radius) < (platform->yCoord + platform->ySize)))
	{
		if (((arrow->xCoord + arrow->radius) > platform->xCoord) && (arrow->xCoord - arrow->radius < (platform->xCoord + platform->xSize)))
		{
			return true;
		}
	}
	if (((arrow->previousy + arrow->radius) > (platform->yCoord)) && ((arrow->previousy - arrow->radius) < (platform->yCoord + platform->ySize)))
	{
		if (((arrow->previousx - arrow->radius) > platform->xCoord) && (arrow->previousx + arrow->radius < (platform->xCoord + platform->xSize)))
		{
			return true;
		}
	}
	return false;
}

bool GameState::detectEnemyCollision(std::vector<Platform>::iterator platform, std::vector<Enemy>::iterator enemy)
{
	if (((enemy->yCoord + enemy->radius) > (platform->yCoord)) && ((enemy->yCoord - enemy->radius) < (platform->yCoord + platform->ySize)))
	{
		if (((enemy->xCoord + enemy->radius) > platform->xCoord) && (enemy->xCoord - enemy->radius < (platform->xCoord + platform->xSize)))
		{
			return true;
		}
	}
	return false;
}

bool GameState::detectSideEnemyCollision(std::vector<Platform>::iterator platform, std::vector<Enemy>::iterator enemy)
{

	if (((enemy->yCoord + enemy->radius) > (platform->yCoord)) && ((enemy->yCoord - enemy->radius) < (platform->yCoord + platform->ySize)))
	{
		if (((enemy->xCoord + enemy->radius + enemy->xVelocity) > platform->xCoord) && (enemy->xCoord - enemy->radius + enemy->xVelocity < (platform->xCoord + platform->xSize)))
		{
			if (((enemy->xCoord + enemy->radius - 10) < platform->xCoord) || ((enemy->xCoord - enemy->radius + 10) > (platform->xCoord + platform->xSize)))
			{
				return true;
			}
		}
		if (((enemy->previousx + enemy->radius - 10) < platform->xCoord) || ((enemy->previousx - enemy->radius + 10) > (platform->xCoord + platform->xSize)))
		{
			return true;
		}
	}

	return false;
}


bool GameState::detectPreviousArrowCollision(std::vector<Platform>::iterator platform, std::vector<Arrow>::iterator arrow)
{
	if (((arrow->previousy + arrow->radius) > (platform->yCoord)) && ((arrow->previousy - arrow->radius) < (platform->yCoord + platform->ySize)))
	{
		if (((arrow->previousx + arrow->radius) > platform->xCoord) && (arrow->previousx + arrow->radius < (platform->xCoord + platform->xSize)))
		{
			return true;
		}
	}
	return false;
}

bool GameState::detectPreviousCollision(std::vector<Platform>::iterator platform)
{

	if ((player.previousy < platform->yCoord) && ((player.yCoord) > (platform->yCoord)))
	{
		if (((player.xCoord + player.xSize) > platform->xCoord) && (player.xCoord < (platform->xCoord + platform->xSize)))
		{
			return true;
		}
		else
			return false;
	}
	return false;
}


void GameState::lookForExplosionCollisions()
{
	for (int i = 0; i < explosions.size(); i++)
	{
		if (entityExplosionCollision(explosions[i], player)&&player.collisionsOn)
		{
			explosionHit(explosions[i], player);
			player.dealDamage(10);
			player.collisionsOn = 0;
			//std::cout << "PlayerHit";
		}
		for (int i2 = 0; i2 < enemies.size(); i2++)
		{
			if (entityExplosionCollision(explosions[i], enemies[i2]))
			{
				explosionHit(explosions[i], enemies[i2]);
				enemies[i2].dealDamage(100);
			}

		}
		for (int i3 = 0; i3 < arrows.size(); i3++)
		{
			if (entityExplosionCollision(explosions[i], arrows[i3]))
			{
				explosionHit(explosions[i], arrows[i3]);
				arrows[i3].markForRemoval = 1;
			}

		}

	}
}

bool GameState::entityExplosionCollision(Explosion explosion, Entity entity)
{
	float Dif = calculateDistance(entity.xCoord, entity.yCoord, explosion.xCoord, explosion.yCoord);
	//std::cout <<"Dif: "<<Dif<<std::endl<<"Radiuses sum: "<<entity.radius;
	if (Dif<(entity.radius+explosion.radius))
	{
		//std::cout << std::endl << "Explosion collision!" << std::endl;
		return true;
	}
	return false;
}