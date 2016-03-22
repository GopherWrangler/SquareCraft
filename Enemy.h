#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <time.h>
#include "People.h"

class Enemy
{
public:
	Enemy(sf::RenderWindow* window, sf::Vector2f* buildPos);
	void takeDamage();
	int getHealth();
	sf::Vector2f getPos();
	float dist(float x0, float y0, float x1, float y1);
	//float dist(float x0, float y0, float x1, float y1);
	float buildingCollisionDist(Building* obj);
	void normalizeVelocity(sf::Vector2f& vel);
	void Update(sf::RenderWindow* window, sf::Time& dt);
	void Draw(sf::RenderWindow* window);

private:
	bool returnCourse;
	bool timerStarted;
	int mHealth;
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
	float mBuildDist;
	float mForDist2;
	float velMag;
	Building* mNearestBuilding;

};