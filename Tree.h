#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <time.h>

class Tree
{
public:
	Tree(sf::Vector2f& size, sf::Vector2f& position, sf::Color& color);
	void setWoodLoad();
	int getWoodLoad();
	void deadTree();
	sf::Vector2f getTreePos();
	float dist(sf::Vector2f pos1, sf::Vector2f pos2);
	void Update(sf::Time dt);
	void Draw(sf::RenderWindow* window);

private:
	sf::RectangleShape* tree;
	int mWoodLoad;
};