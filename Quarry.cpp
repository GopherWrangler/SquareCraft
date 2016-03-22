#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <time.h>
#include "APEngine.h"
#include "Quarry.h"


Quarry::Quarry(sf::RenderWindow* window)
{
	windowSize = window->getSize();

	m_node.setSize(sf::Vector2f(30, 30));
	m_node.setFillColor(sf::Color::Yellow);
	mPos.x = (((float)rand() / RAND_MAX) * windowSize.x);
	mPos.y = (((float)rand() / RAND_MAX) * windowSize.y);
	m_node.setPosition(mPos);

	m_stoneLoad = rand() % 200 + 300;
}

int Quarry::getStoneAmnt()
{
	return m_stoneLoad;
}

void Quarry::setStoneAmnt()
{
	m_stoneLoad -= 10;
}

sf::Vector2f Quarry::getQuarrySize()
{
	return m_node.getSize();
}

sf::Vector2f Quarry::getQuarryPos()
{
	return m_node.getPosition();
}

void Quarry::Update(sf::RenderWindow* window)
{
	//Behavior for getting mined and becoming empty
	//
	//Once worker comes within distance of 5, subtract stone
	//If stone <= 0 destroy quarry
	if (m_stoneLoad <= 0)
	{
		m_node.setFillColor(sf::Color::Red);
		m_node.setSize(sf::Vector2f(20, 20));
	}
}

void Quarry::Draw(sf::RenderWindow* window)
{
	window->draw(m_node);
}