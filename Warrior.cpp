#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <time.h>
#include "People.h"
#include "APEngine.h"
#include "Enemy.h"
#include "Warrior.h"

Warrior::Warrior(sf::RenderWindow* window, sf::Vector2f* buildPos, Building* homeBuilding)
{
	mDist1 = 2000;
	mHealth = 50;

	returnCourse = false;
	homeBarracks = homeBuilding;

	mPerson = new sf::RectangleShape;
	mPos = *buildPos;
	startPos = *buildPos;

	mPerson->setSize(sf::Vector2f(5, 5));
	mPerson->setFillColor(sf::Color::White);
	mPerson->setPosition(mPos.x - 20, mPos.y - 20);
}

sf::Vector2f Warrior::getPos()
{
	return mPerson->getPosition();
}

void Warrior::MinusHealth()
{
	mHealth -= 10;
}

int Warrior::getHealth()
{
	return mHealth;
}

float Warrior::enemyCollisionDist(Enemy* enemy)
{
	enemyPos = enemy->getPos();
	return dist(enemyPos.x, enemyPos.y, mPos.x, mPos.y);
}

void Warrior::Update(sf::RenderWindow* window, sf::Time& dt)
{
	if (Globals::mEnemies.size() != NULL)
	{
		//------------Find nearest Enemy to attack---------------//
		for (int i = 0; i < Globals::mEnemies.size(); i++)
		{
			mDist2 = enemyCollisionDist(Globals::mEnemies[i]);
			if (mDist2 < mDist1)
			{
				mEnemyDist = mDist2;
				mDist1 = mDist2;
				mNearestEnemy = Globals::mEnemies[i];
			}
		}

		mVel = mNearestEnemy->getPos() - mPos;

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
	}
	//-----------When in range, attack Enemies-------------------------//
	if (mDist1 <= 5)
	{
		mNearestEnemy->takeDamage();
	}

	//-----------No Enemies in vector, then stand still----------------//
	else
	{
		mVel.x = 0;
		mVel.y = 0;

		mPos += mVel;

		mPerson->setPosition(mPos.x, mPos.y);
	}
}

void Warrior::Draw(sf::RenderWindow* window)
{
	window->draw(*mPerson);
}