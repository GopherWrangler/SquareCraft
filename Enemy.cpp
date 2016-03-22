//#include "APEngine.cpp"
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <time.h>
#include "APEngine.h"
#include "People.h"
#include "Enemy.h"


Enemy::Enemy(sf::RenderWindow* window, sf::Vector2f* buildPos)
{
	mDist1 = 2000;
	mHealth = 50;

	returnCourse = false;
	timerStarted = false;
	//homeBarracks = homeBuilding;

	mPerson = new sf::RectangleShape;
	mPos = *buildPos;
	startPos = *buildPos;

	mPerson->setSize(sf::Vector2f(5, 5));
	mPerson->setFillColor(sf::Color::Red);
	mPerson->setPosition(mPos.x - 20, mPos.y - 20);
}

void Enemy::takeDamage()
{
	mHealth -= 10;
}

int Enemy::getHealth()
{
	return mHealth;
}

sf::Vector2f Enemy::getPos()
{
	return mPerson->getPosition();
}

float Enemy::dist(float x0, float y0, float x1, float y1)
{
	float dx = x1 - x0;
	float dy = y1 - y0;
	return sqrtf(dx*dx + dy*dy);
}

float Enemy::buildingCollisionDist(Building* obj)
{
	buildingPos = obj->getBuildPos();
	return dist(buildingPos.x, buildingPos.y, mPos.x, mPos.y);
}

void Enemy::normalizeVelocity(sf::Vector2f& vel)
{
	Vel = vel;

	Vel.x = Vel.x / (Vel.x*Vel.x + Vel.y*Vel.y);
	Vel.y = Vel.y / (Vel.x*Vel.x + Vel.y*Vel.y);
}

void Enemy::Update(sf::RenderWindow* window, sf::Time& dt)
{
	//-------------------Find the nearest building to attack-----------------------//
	if (Globals::mBuildings.size() != NULL)
	{
		for (int i = 0; i < Globals::mBuildings.size(); i++)
		{
			mDist2 = buildingCollisionDist(Globals::mBuildings[i]);
			if (mDist2 < mDist1)
			{
				mBuildDist = mDist2;
				mDist1 = mDist2;
				mNearestBuilding = Globals::mBuildings[i];
			}
		}

		mVel = mNearestBuilding->getBuildPos() - mPos;

		mVel.x *= dt.asSeconds();
		mVel.y *= dt.asSeconds();

		velMag = sqrtf((mVel.x*mVel.x) + (mVel.y*mVel.y));

		if (velMag > MAX_SPEED)
		{
			normalizeVelocity(mVel);
			mVel = mVel * MAX_SPEED;
		}

		mPos += mVel;

		mPerson->setPosition(mPos.x, mPos.y);

		if (mNearestBuilding->getHealth() <= 0)
		{
			mDist1 = 2000;
		}
	}
	else
	{
		mVel.x = 0;
		mVel.y = 0;

		mPos += mVel;

		mPerson->setPosition(mPos.x, mPos.y);
	}

}

void Enemy::Draw(sf::RenderWindow* window)
{
	window->draw(*mPerson);
}