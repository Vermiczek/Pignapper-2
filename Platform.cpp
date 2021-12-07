#include "Platform.h"

Platform::Platform(int x, int y, int xs, int ys, int id, sf::Texture& spr)
{
	xSize = xs;
	ySize = ys;
	xCoord = x;
	yCoord = y;
	sf::Vector2f position = sf::Vector2f(x, y);
	
	platformTexturePtr = &spr;
	sf::Texture tempTxt = spr;
		if (!this->platformTexture.loadFromFile("platform.png"))
	{

	}
	else
	{
			sf::Vector2u TextureSize = platformTexturePtr->getSize(); 
				std::cout << platformTexturePtr->getSize().x;
				TextureSize.x = 100;
				TextureSize.y = 150;
		float ScaleX = (float)150 / TextureSize.x;
		float ScaleY = (float)30 / TextureSize.y;
		platformSprite.setTexture(platformTexture);
		platformSprite.setScale(ScaleX, ScaleY);
		platformSprite.setPosition(400, 400);
	}

	spin = id;
}



Platform::Platform(int x, int y, int xs, int ys, int id, sf::Sprite spr)
{
	xSize = xs;
	ySize = ys;
	xCoord = x;
	yCoord = y;
	sf::Vector2f position = sf::Vector2f(x, y);

	platformSprite = spr;

	spin = id;
}

Platform::~Platform()
{

}

void Platform::platformSetPosition(int xCentre, int yCentre, int distanceFromCenter, sf::Texture &tex)
{
	spin = spin+0.001;
	double x = cos(spin) * distanceFromCenter;
	double y = sin(spin) * distanceFromCenter;
	//std::cout << cos(spin) << std::endl;
	platformSprite.setTexture(tex);
	xCoord = xCentre + x;
	yCoord = yCentre + y;
	platformSprite.setPosition(xCoord, yCoord);
}

void Platform::platformSetPosition(int xCentre, int yCentre, int distanceFromCenter, sf::Sprite tex)
{
	spin = spin + 0.001;
	double x = cos(spin) * distanceFromCenter;
	double y = sin(spin) * distanceFromCenter;
	//std::cout << cos(spin) << std::endl;
	//platformSprite.setTexture(tex);
	xCoord = xCentre + x;
	yCoord = yCentre + y;
	platformSprite = tex;
}

void Platform::draw(sf::RenderWindow& window)
{
	window.draw(platformSprite);
	//std::cout << "print'";
}