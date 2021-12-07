#pragma once
#include "Goodies.h"
#include "Player.h"
#include "Platform.h"
#include "PowerBar.h"
#include "Arrow.h"
#include "Enemy.h"
#include "Explosion.h"
#include <list>
#include <vector>
const int spawnTimerLimitDefault = 500;

class GameState
{
public:
	GameState();
	void spawnSingleEnemy(int type, double x, double y);
	void spawnTimerLimitAlghoritm();
	void spawner();
	void spawnRandomEnemy(int type);
	void drawObject(int xCoord, int yCoord);
	void draw(sf::RenderWindow& window);
	void entityOutOfBounds(Entity& entity);
	void updateExplosion();
	void explodeMissile();
	void refresh();
	void ArrowEntityCollisionLoop();
	void playerJump(bool dir);
	void CreatePlatform(int xCoord, int yCoord, int xSize, int ySize);
	void CreatePlatforms();
	void makeExplosion();
	void playerPlatformCollision();
	void playerPlatformCollisionPredict();
	void DealDamage(Entity entity);
	bool detectCollision(std::vector<Platform>::iterator platform);
	bool predictCollision(std::vector<Platform>::iterator platform);
	bool detectSideCollision(std::vector<Platform>::iterator platform);
	bool detectArrowCollision(std::vector<Platform>::iterator platform, std::vector<Arrow>::iterator arrow);
	bool detectEnemyCollision(std::vector<Platform>::iterator platform, std::vector<Enemy>::iterator enemy);
	bool detectSideEnemyCollision(std::vector<Platform>::iterator platform, std::vector<Enemy>::iterator enemy);
	bool detectPreviousCollision(std::vector<Platform>::iterator platform);
	void explosionHit(Explosion explosion, Entity &entity);
	void lookForExplosionCollisions();
	void explosionCollisionsRefresh();
	void explosionHit();
	bool entityExplosionCollision(Explosion explosion, Entity entity);
	bool entityExplosionCollision(Explosion explosion);
	bool detectSideArrowCollision(std::vector<Platform>::iterator platform, std::vector<Arrow>::iterator arrow);
	bool killEntity(Entity entity);
	bool killEnemy(std::vector<Enemy>& enemy);
	bool detectPreviousArrowCollision(std::vector<Platform>::iterator platform, std::vector<Arrow>::iterator arrow);
	void setPlayerDirection();
	void setKeyDowns(bool aord);
	void setSpaceDown() {
		spaceDown = 1;
	}
	void setSpaceUp()
	{
		spaceDown = 0;
	}
	void Detonate(Arrow arrow);
	void Detonate();
	void EraseArrowFromExistence();
	void DetonateArrow(Arrow arrow);
	void ResetKeyDowns(bool aord);
	void CreatePlatform(int xCoord, int yCoord, int xSize, int ySize, int id);
	void PlayerCollisionEvent(Platform platform);
	void ArrowCollisionEvent();
	void EnemyCollisionEvent(float bounceRatio);
	void livingEntitiesCollisionEvent(Entity entity1, Entity entity2, double ratio1, double ratio2);
	void livingEntitiesCollisionEvent(std::vector<Enemy>::iterator entity1, Entity& entity2, double ratio1, double ratio2);
	void arrowEntityCollisionEvent(Entity& entity1, Entity& entity2, double ratio1, double ratio2);
	bool livingEntitiesCollision(std::vector<Enemy>::iterator entity1, Entity entity2);
	bool livingEntityArrowCollision(Entity entity, Entity arrow);
	void EnemyCollisionEvent();
	void playerArrowCollision(Arrow arrow);
	void arrowCollisionEvent(Platform platform, Arrow arrow);
	void ShootArrow(int xMouse, int yMouse);
	void enemyShootArrowAtPlayer(Enemy enemy, Player player);
	void DrawArrow();
	void markForDetonation();
	void playerFreeze()
	{
		player.xVelocity = 0;
		player.yVelocity = 0;
	}
	bool blockFreeze = 0;
	bool AkeyDown;
	bool DkeyDown;
	bool spaceDown = 0;
	bool drawingArrow = 0;
	bool chosenWeapon = 0;
	int timer = 0;
	int gametimer = 0;
	int spawnTimer = 0;
	int spawnTimerLimit = 300;
	int shotArrows;
	int returnPlayerHp()
	{
		return player.hp;
	}
	void loadTextures() {
		if (!this->platformTexture.loadFromFile("platform.png"))
		{
			std::cout << "Error loading platform texture" << std::endl;
		}
	}
	sf::Texture platformTexture;
	sf::Texture* platformTexturePointer = &platformTexture;
	sf::Sprite platformSprite;


private:

	Player player = Player(100, 400, 400, 30, 30);
	PowerBar powerbar = PowerBar(0,0,0,0);
	std::vector<Platform> platforms;
	std::vector<Arrow> arrows;
	std::vector<Explosion> explosions;
	std::vector<Enemy> enemies;
	int shotPower = 0;
	bool grenadeExists = 0;
};