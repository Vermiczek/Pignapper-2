#pragma once
#include "Entity.h"
enum {Shooter, SmallCharger, BigCharger, Spammer, Wkurwiacz, Rakietowiec};

class Enemy : public Entity
{
	public:
		Enemy(int type, double x, double y)
		{
			enemyType = type;
			xCoord = x;
			yCoord = y;
			sf::Vector2f position = sf::Vector2f(x, y);
			if (type == Shooter) {
				hp = 100;
				radius = 25;
				sf::Vector2f position = sf::Vector2f(x, y);
				maxSpeed = 5;
				acceleration = 0.025;
				shootIntervalVal = 150;
				bulletSpeed = 20;
				bulletType = 4;
			    
			}
			if (type == SmallCharger) {
				hp = 10;
				radius = 15;
				sf::Vector2f position = sf::Vector2f(x, y);
				maxSpeed = 20;
				acceleration = 0.2;
				shootIntervalVal = 9999999999999999;
				bulletSpeed = 10;
				bulletType = 3;
			}
			if (type == BigCharger) {
				hp = 300;
				radius = 50;
				sf::Vector2f position = sf::Vector2f(x, y);
				maxSpeed = 15;
				acceleration = 0.1;
				shootIntervalVal = 9999999999999999;
				bulletSpeed = 10;
				bulletType = 3;
			}
			if (type == Spammer) {
				hp = 100;
				radius = 35;
				sf::Vector2f position = sf::Vector2f(x, y);
				maxSpeed = 1;
				acceleration = 0.025;
				shootIntervalVal = 50;
				bulletSpeed = 10;
				bulletType = 3;
			}
			if (type == Wkurwiacz) {
				hp = 25;
				radius = 20;
				sf::Vector2f position = sf::Vector2f(x, y);
				maxSpeed = 20;
				acceleration = 0.2;
				shootIntervalVal = 200;
				bulletSpeed = 10;
				bulletType = 3;
			}
			if (type == Rakietowiec) {
				hp = 25;
				radius = 20;
				sf::Vector2f position = sf::Vector2f(x, y);
				maxSpeed = 10;
				acceleration = 0.2;
				shootIntervalVal = 200;
				bulletSpeed = 10;
				bulletType = 4;
			}
			enemyHitbox.setPosition(position);
			enemyHitbox.setOrigin(radius, radius);
			enemyHitbox.setRadius(radius);
			enemyHitbox.setFillColor(sf::Color::Red);

		}

		void incrementInterval()
		{
			shootInterval += 1;
	}
	float maxVelocity = 10;
	int enemyType;
	sf::CircleShape enemyHitbox;
	int shootInterval = 0;
	int bulletSpeed;
	int rangedDamage = 0;
	int meleeDamage = 0;
	int maxSpeed;
	int shootIntervalVal;
	int bulletType;
	void draw(sf::RenderWindow& window);

	void refresh();

	void limitSpeed();

	void refreshPreviousPosition();

	void goTowardsTarget(int targetXcoord, int targetYcoord);

	void moveEnemyVel();

private:
	double acceleration = 0.25;
}; 