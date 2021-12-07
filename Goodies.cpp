#include "Goodies.h"

sf::Sprite SetSpriteScaled(sf::RenderWindow window, sf::Texture texture)
{

	sf::Vector2u TextureSize = texture.getSize();
	sf::Sprite newSprite;

	float ScaleX = window.getSize().x / TextureSize.x;
	float ScaleY = window.getSize().y / TextureSize.y;
	newSprite.setTexture(texture);
	newSprite.setScale(ScaleX, ScaleY);

	return newSprite;
}
