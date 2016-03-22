#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <time.h>
#include "Building.h"

Building::Building()
{

}

Building::Building(sf::RenderWindow* window, Structure type, sf::Vector2i mousePos)
{
	mType = type;

	switch (type)
	{
	case HOUSE:
		mHealth = 100;
		mBase = new sf::RectangleShape;
		mRoof = new sf::CircleShape;
		mTop = new sf::RectangleShape;

		mBase->setSize(sf::Vector2f(40, 40));
		mBase->setFillColor(sf::Color::Black);
		mRoof->setRadius(22);
		mRoof->setPointCount(3);
		mRoof->setFillColor(sf::Color::Black);
		mTop->setSize(sf::Vector2f(1, 1));
		mTop->setFillColor(sf::Color::Transparent);
		//set position according to mouse coords
		mBase->setPosition(mousePos.x, mousePos.y);
		mRoof->setPosition(mousePos.x - 2, (mousePos.y - 32));
		mTop->setPosition(mousePos.x, mousePos.y);
		break;
	case BARRACKS:
		mHealth = 150;
		mBase = new sf::RectangleShape;
		mRoof = new sf::CircleShape;
		mTop = new sf::RectangleShape;

		mBase->setSize(sf::Vector2f(65, 20));
		mBase->setFillColor(sf::Color::Black);
		mRoof->setRadius(22);
		mRoof->setPointCount(3);
		mRoof->setFillColor(sf::Color::Black);
		mTop->setSize(sf::Vector2f(76, 12));
		mTop->setFillColor(sf::Color::Black);

		//set position according to mouse coords
		mBase->setPosition(mousePos.x, mousePos.y);
		mTop->setPosition(mousePos.x - 6, mousePos.y - 12);
		mRoof->setPosition(mousePos.x + 10, (mousePos.y - 33));
		break;
	}
}

sf::Vector2f Building::getBuildPos()
{
	return mBase->getPosition();
}

void Building::MinusHealth()
{
	mHealth -= 10;
}

int Building::getHealth()
{
	return mHealth;
}

void Building::Update(sf::RenderWindow* window)
{

}

void Building::Draw(sf::RenderWindow* window)
{
	window->draw(*mBase);
	window->draw(*mRoof);
	window->draw(*mTop);
}