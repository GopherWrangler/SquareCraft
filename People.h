#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <time.h>
#include "APEngine.h"
#include "Enemy.h"
#include "Building.h"
#include "Forest.h"
#include "Quarry.h"
#include "UI.h"


class People
{
public:
	People();
	People(sf::RenderWindow* window, sf::Vector2f* buildPos, Building* homeBuilding);
	void destroyBuilding();
	sf::Vector2f getPos();
	float dist(float x0, float y0, float x1, float y1);
	float buildingCollisionDist(Building* obj);
	bool quarryCollision(Quarry* obj);
	float quarryCollisionDist(Quarry* obj);
	bool forestCollision(Forest* obj);
	float forestCollisionDist(sf::Vector2f pos);
	void normalizeVelocity(sf::Vector2f& vel);
	void Update(sf::RenderWindow* window, sf::Time& dt);
	void Draw(sf::RenderWindow* window);

private:
	bool returnCourse;
	bool timerStarted;
	bool homeDestroyed;
	int mQuarryDist;
	int mForestDist;
	int* mNearestWood;
	sf::RectangleShape* mPerson;
	sf::Vector2f mPos;
	sf::Vector2f buildingPos;
	sf::Vector2f startPos;
	sf::Vector2f mSize;
	sf::Vector2f mVel;
	sf::Vector2f Vel;
	sf::Clock timer;
	sf::Time time;
	float mDist1;
	float mDist2;
	float mForDist1;
	float mForDist2;
	float velMag;
	Quarry* mNearestQuarry;
	Forest* mNearestForest;
	Tree* mNearestTree;
	Building* homeBase;

};


class Warrior : public People
{
public:
	Warrior(sf::RenderWindow* window, sf::Vector2f* buildPos, Building* homeBuilding);
	sf::Vector2f getPos();
	void MinusHealth();
	int getHealth();
	float enemyCollisionDist(Enemy* enemy);
	void Update(sf::RenderWindow* window, sf::Time& dt);
	void Draw(sf::RenderWindow* window);

private:
	bool returnCourse;
	int mHealth;

	sf::RectangleShape* mPerson;
	sf::Vector2f mPos;
	sf::Vector2f enemyPos;
	sf::Vector2f startPos;
	sf::Vector2f mSize;
	sf::Vector2f mVel;
	sf::Vector2f Vel;
	float mDist1;
	float mDist2;
	float mEnemyDist;
	float velMag;
	Building* homeBarracks;
	Enemy* mNearestEnemy;
};