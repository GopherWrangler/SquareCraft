#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <time.h>
#include "APEngine.h"
#include "People.h"
#include "Enemy.h"
#include "Warrior.h"
#include "UI.h"
class Globals;
class People;
class Warrior;

class Game
{
public:
	Game(sf::RenderWindow* window);
	float dist(float x0, float y0, float x1, float y1);
	void Loop(sf::RenderWindow* window, sf::Time dt);
	void Draw(sf::RenderWindow* window);

	std::vector<People*> mWorkers;
	std::vector<Warrior*> mWarriors;
	Building* homeBuilding;

private:
	bool btnPressed;

	float mDamageDist;

	sf::RectangleShape* bckGround;
	sf::RectangleShape* river;

	sf::Vector2i mousePos;
	sf::Vector2f homePos;
	sf::Vector2f mBuildingDamagePos;
	sf::Vector2f mEnemyDamagePos;
	sf::Vector2f* pos;

	UI* snazyUI;
	Enemy* myEnemy;

	/*
	sf::Text endMsg;
	sf::Clock clock;
	sf::Time invulTime;
	//sf::SoundBuffer buffer1;
	//sf::SoundBuffer buffer2;
	//sf::Sound laser;
	//sf::Sound explosion;
	*/
};