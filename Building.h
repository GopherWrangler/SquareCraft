#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <time.h>

enum Structure
{
	HOUSE = 0,
	BARRACKS = 1
};

class Building
{
public:
	Building();
	Building(sf::RenderWindow*window, Structure type, sf::Vector2i mousePos);
	sf::Vector2f getBuildPos();
	void MinusHealth();
	int getHealth();
	void Update(sf::RenderWindow* window);
	void Draw(sf::RenderWindow* window);

private:
	int mHealth;
	Structure mType;
	sf::RectangleShape* mBase;
	sf::RectangleShape* mTop;
	sf::CircleShape* mRoof;
	sf::Vector2f mPos;


};
