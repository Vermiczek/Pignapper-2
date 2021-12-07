#ifndef ACTIONS_H
#define ACTIONS_H
#include "SFML/Graphics.hpp"
#include <vector>
#include <iostream>
#include <string> 
#include <cmath>
enum actions {MenuScr, GameScr, loadGameScr, OptionsScr, HighScoresScr, ExitApp};
sf::Sprite SetSpriteScaled(sf::RenderWindow window, sf::Texture texture);

struct highScore {
	std::string name;
	int score;
};

bool scoreSort(highScore one, highScore two)
{
	
	return one.score > two.score;
}

float calculateDistance(float x1, float y1, float x2, float y2)
{
	float xDif, yDif;
	yDif = sqrt((y1 - y2) * (y1 - y2));
	//std::cout << std::endl << "yDif" << std::endl<<yDif<<std::endl;
	xDif = sqrt((x1 - x2) * (x1 - x2));
	float Dif = sqrt((xDif * xDif) + (yDif * yDif));
	return Dif;
}


#endif