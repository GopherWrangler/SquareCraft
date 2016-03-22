#pragma once

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <time.h>

class Quarry
{
public:
	Quarry(sf::RenderWindow* window);
	int getStoneAmnt();
	void setStoneAmnt();
	sf::Vector2f getQuarrySize();
	sf::Vector2f getQuarryPos();
	void Update(sf::RenderWindow* window);
	void Draw(sf::RenderWindow* window);

	int m_stoneLoad;
	sf::Vector2f mPos;

private:
	sf::RectangleShape m_node;
	sf::Vector2u windowSize;
};
