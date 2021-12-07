#pragma once
#include "Entity.h"

class Player : public Entity 
{
public:
	//functions
	Player(int setHP, int x, int y, int xs, int ys);
	~Player();
	void ChangeHP(int value);
	void draw(sf::RenderWindow& window);
	void refresh();
	void setDirection(int dir);
	void refeshMovementVelocity();
	void refreshPreviousPosition();
	void movePlayerVel();
	void refeshGravityVerticalVelocity();
	void refeshVelocity();
	void ToggleTopCollision(bool value);
	void ToggleBotCollision(bool value);
	void ToggleSideCollision(bool value);
	void Jump(bool dir);

	void resetInvulnerability() {
		//std::cout << std::endl << invulCounter;
		if (collisionsOn!=true) {
			invulCounter += 1;
		}
		if (invulCounter >= 100)
		{
			invulCounter = 0;
			collisionsOn = true;
		}
	}

	//variables
	int previousx;
	int previousy;
	bool onTopOfPlatform = 0;
	bool onBottomOfPlatform = 0;
	bool onSideOfPlatform = 0;
	bool collisionsOn = true;
	int invulCounter = 0;

private:
	int horizontalMovement = Stay;
	sf::CircleShape hitbox;
	sf::Sprite playerSprite;
	sf::Texture playerTexture;
};