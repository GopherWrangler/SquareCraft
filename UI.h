#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <time.h>


class UI
{
public:
	UI();
	void Update(sf::RenderWindow* window);
	void Draw(sf::RenderWindow* window);

private:
	sf::RectangleShape* mButtonBox;
	sf::RectangleShape* mResources;
	sf::RectangleShape* mHouse;
	sf::CircleShape* mBarracks;

	sf::Font* font;
	sf::Text* mWoodDisp;
	sf::Text* mStoneDisp;
	sf::Text* mTextStoneAmnt;
	sf::Text* mTextWoodAmnt;

	sf::Vector2i mousePos;
	sf::Vector2f mHouseSize;
	sf::Vector2f mHousePos;
	int mBarracksSize;
	int mStoneAmnt;
	sf::Vector2f mBarracksPos;

	std::string mStoneResourceAmnt;
	std::string mWoodResourceAmnt;
};