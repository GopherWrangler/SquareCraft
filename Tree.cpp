#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <time.h>
#include "Tree.h"

Tree::Tree(sf::Vector2f& size, sf::Vector2f& position, sf::Color& color)
{
	tree = new sf::RectangleShape;

	tree->setSize(sf::Vector2f(size));
	tree->setPosition(sf::Vector2f(position));
	tree->setFillColor(sf::Color(color));

	mWoodLoad = 200;
}

void Tree::setWoodLoad()
{
	mWoodLoad -= 10;
}

int Tree::getWoodLoad()
{
	return mWoodLoad;
}

void Tree::deadTree()
{
	tree->setSize(sf::Vector2f(10, 10));
	tree->setFillColor(sf::Color::Black);
}
sf::Vector2f Tree::getTreePos()
{
	return tree->getPosition();
}

float Tree::dist(sf::Vector2f pos1, sf::Vector2f pos2)
{
	float dx = pos2.x - pos1.x;
	float dy = pos2.y - pos1.y;
	return sqrtf(dx*dx + dy*dy);
}

void Tree::Update(sf::Time dt)
{
	/*for (int i = 0; i < mWorkers.size(); i++)
	{
	if (dist(tree->getPosition(), mWorkers[i]->getPos()) <= 5)
	{
	//Save local workers in array and make sure to only save Worker once
	}
	}*/
}

void Tree::Draw(sf::RenderWindow* window)
{
	window->draw(*tree);
}