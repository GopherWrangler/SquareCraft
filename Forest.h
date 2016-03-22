#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <time.h>
#include "APEngine.h"
#include "Tree.h"

class Forest
{
public:
	Forest();
	Forest(sf::RenderWindow* window);
	//int getWoodLoad(sf::RectangleShape* tree);
	//void setWoodLoad(Forest* forest, sf::RectangleShape* tree);
	sf::Vector2f getForestSize();
	void Update(sf::RenderWindow* window);
	void Draw(sf::RenderWindow* window);
	sf::Vector2f mPos;
	std::vector<Tree*> mTrees;
	//-----Make a new Tree class to handle wood deductions-------//
	//std::vector<int*> mWood;

private:
	//int* mWoodLoad;
	int randX;
	int randLength;
	int randDist;

	sf::Vector2u windowSize;
	sf::Vector2f mTreeSize;
	sf::Vector2f mTreePos;

	sf::RectangleShape* mTreeptimusPrime;

	//std::vector<sf::RectangleShape*> mTrees;
};
