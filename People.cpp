#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <time.h>
#include "APEngine.h"
#include "People.h"
#include "Building.h"
#include "Forest.h"
#include "Quarry.h"

People::People()
{

}

People::People(sf::RenderWindow* window, sf::Vector2f* buildPos, Building* homeBuilding)
{
	mDist1 = 2000;
	mForDist1 = 2000;
	returnCourse = false;
	timerStarted = false;
	homeBase = homeBuilding;

	mPerson = new sf::RectangleShape;
	mPos = *buildPos;
	startPos = *buildPos;

	mPerson->setSize(sf::Vector2f(5, 5));
	mPerson->setFillColor(sf::Color::Blue);
	mPerson->setPosition(mPos.x - 20, mPos.y - 20);
}

void People::destroyBuilding()
{
	delete homeBase;
	homeBase = 0;
}

sf::Vector2f People::getPos()
{
	return mPerson->getPosition();
}

float People::dist(float x0, float y0, float x1, float y1)
{
	float dx = x1 - x0;
	float dy = y1 - y0;
	return sqrtf(dx*dx + dy*dy);
}

float People::buildingCollisionDist(Building* obj)
{
	buildingPos = obj->getBuildPos();
	return dist(buildingPos.x, buildingPos.y, mPos.x, mPos.y);
}

bool People::quarryCollision(Quarry* obj)
{
	mSize = obj->getQuarrySize();
	return dist(obj->mPos.x, obj->mPos.y, mPos.x, mPos.y) < mSize.x + mSize.x;
}

float People::quarryCollisionDist(Quarry* obj)
{
	//mSize = obj->getQuarrySize();
	return dist(obj->mPos.x, obj->mPos.y, mPos.x, mPos.y);
}

bool People::forestCollision(Forest* obj)
{
	mSize = obj->getForestSize();
	return dist(obj->mPos.x, obj->mPos.y, mPos.x, mPos.y) < mSize.x + mSize.x;
}

float People::forestCollisionDist(sf::Vector2f pos)
{
	//mSize = obj->getForestSize();
	return dist(pos.x, pos.y, mPos.x, mPos.y);
}

void People::normalizeVelocity(sf::Vector2f& vel)
{
	Vel = vel;

	Vel.x = Vel.x / (Vel.x*Vel.x + Vel.y*Vel.y);
	Vel.y = Vel.y / (Vel.x*Vel.x + Vel.y*Vel.y);
}

void People::Update(sf::RenderWindow* window, sf::Time& dt)
{
	for (int i = 0; i < Globals::mBuildings.size(); i++)
	{
		if (Globals::mBuildings[i] == homeBase)
		{
			homeDestroyed = false;
			break;
		}
		else
		{
			homeDestroyed = true;
		}
	}
	if (homeDestroyed)
	{
		homeBase = 0;
	}

	if (homeBase != NULL)
	{
		if (Globals::mQuarries.size() != NULL || Globals::mForests.size() != NULL)
		{
			//Find nearest Quarry
			if (Globals::mQuarries.size() != NULL)
			{
				for (int i = 0; i < Globals::mQuarries.size(); i++)
				{
					mDist2 = quarryCollisionDist(Globals::mQuarries[i]);

					if (mDist2 < mDist1)
					{
						mNearestQuarry = Globals::mQuarries[i];
						mQuarryDist = mDist2;
						mDist1 = mDist2;
					}
				}
			}

			//Find nearest Forest
			if (Globals::mForests.size() != NULL)
			{
				for (int i = 0; i < Globals::mForests.size(); i++)
				{


					if (Globals::mForests[i]->mTrees.size() != NULL)
					{
						for (int j = 0; j < Globals::mForests[i]->mTrees.size(); j++)
						{
							mForDist2 = forestCollisionDist(Globals::mForests[i]->mTrees[j]->getTreePos());

							if (mForDist2 < mForDist1)
							{
								mNearestForest = Globals::mForests[i];
								mNearestTree = Globals::mForests[i]->mTrees[j];
								mForestDist = mForDist2;
								mForDist1 = mForDist2;
							}
						}
					}
				}
			}

			//-----------------Decide whether to harvest stone or wood-------------------//
			//
			//------Go to Quarry if quarry is closer----------//
			if (mQuarryDist < mForestDist)
			{
				if (!returnCourse)
				{
					mVel = mNearestQuarry->getQuarryPos() - mPos;

					mVel.x *= dt.asSeconds();
					mVel.y *= dt.asSeconds();

					if (quarryCollisionDist(mNearestQuarry) <= 5 && returnCourse == false)
					{
						if (!timerStarted)
						{
							mVel.x = 0;
							mVel.y = 0;

							timer.restart();

							timerStarted = true;
						}
						else
						{
							time = timer.getElapsedTime();
							if (time.asSeconds() < HARVEST_TIME_QUARRY)
							{
								mVel.x = 0;
								mVel.y = 0;
							}
							else
							{
								mPos.x += 10;
								mPos.y += 10;
								returnCourse = true;
								timerStarted = false;
							}
						}
					}
				}
			
				else if (returnCourse)
				{
					mVel = homeBase->getBuildPos() - mPos;

					mVel.x *= dt.asSeconds();
					mVel.y *= dt.asSeconds();

					if (buildingCollisionDist(homeBase) <= 5 && returnCourse == true)
					{
						if (!timerStarted)
						{
							mVel.x = 0;
							mVel.y = 0;

							timer.restart();
							mNearestQuarry->setStoneAmnt();
							Globals::playerStoneAmnt += 10;

							timerStarted = true;
						}
						else
						{
							time = timer.getElapsedTime();
							if (time.asSeconds() < HARVEST_TIME_QUARRY)
							{
								mVel.x = 0;
								mVel.y = 0;
							}
							else
							{
								mPos.x += 10;
								mPos.y += 10;

								returnCourse = false;
								timerStarted = false;
							}
						}
					}
				}

				if (mNearestQuarry->getStoneAmnt() <= 0)
				{
					mDist1 = 2000;
					for (int i = 0; i < Globals::mQuarries.size(); i++)
					{
						if (Globals::mQuarries[i] == mNearestQuarry)
						{
							Globals::mDeadQuarries.push_back(Globals::mQuarries[i]);
							Globals::mQuarries.erase(Globals::mQuarries.begin() + i);
						}
					}
				}

				velMag = sqrtf((mVel.x*mVel.x) + (mVel.y*mVel.y));

				if (velMag > MAX_SPEED)
				{
					normalizeVelocity(mVel);
					mVel = mVel * MAX_SPEED;
				}

				mPos += mVel;

				mPerson->setPosition(mPos.x, mPos.y);
			}
			//-----------------------------Go to Forest if trees are closer-------------------------------//
			else
			{
				if (!returnCourse)
				{
					mVel = mNearestTree->getTreePos() - mPos;

					mVel.x *= dt.asSeconds();
					mVel.y *= dt.asSeconds();

					if (forestCollisionDist(mNearestTree->getTreePos()) <= 5)
					{
						if (!timerStarted)
						{
							mVel.x = 0;
							mVel.y = 0;

							timer.restart();

							timerStarted = true;
						}
						else
						{
							time = timer.getElapsedTime();
							if (time.asSeconds() < HARVEST_TIME_LUMBER)
							{
								mVel.x = 0;
								mVel.y = 0;
							}
							else
							{
								mPos.x += 10;
								mPos.y += 10;
								mNearestTree->setWoodLoad();
								returnCourse = true;
								timerStarted = false;
								printf("Returning Home.\n");
							}
						}
					}
				}
				else if (returnCourse)
				{
					mVel = homeBase->getBuildPos() - mPos;

					mVel.x *= dt.asSeconds();
					mVel.y *= dt.asSeconds();

					if (buildingCollisionDist(homeBase) <= 5)
					{
						if (!timerStarted)
						{
							mVel.x = 0;
							mVel.y = 0;

							timer.restart();

							Globals::playerWoodAmnt += 5;

							timerStarted = true;
							printf("Made it Home. \n");
						}
						else
						{
							time = timer.getElapsedTime();
							if (time.asSeconds() < HARVEST_TIME_LUMBER)
							{
								mVel.x = 0;
								mVel.y = 0;
							}
							else
							{
								mPos.x += 10;
								mPos.y += 10;

								returnCourse = false;
								timerStarted = false;
							}
						}
					}
				}

				if (Globals::mForests.size() != NULL)
				{
					for (int i = 0; i < Globals::mForests.size(); i++)
					{
						if (Globals::mForests[i]->mTrees.size() == NULL)
						{
							Globals::mForests.erase(Globals::mForests.begin() + i);
						}
					}
				}

				mForDist1 = 2000;

			}

			velMag = sqrtf((mVel.x*mVel.x) + (mVel.y*mVel.y));

			if (velMag > MAX_SPEED)
			{
				normalizeVelocity(mVel);
				mVel = mVel * MAX_SPEED;
			}

			mPos += mVel;

			mPerson->setPosition(mPos.x, mPos.y);
		}
		else
		{
			mVel.x = 0;
			mVel.y = 0;

			mPos += mVel;
			mPerson->setPosition(mPos.x, mPos.y);
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

void People::Draw(sf::RenderWindow* window)
{
	window->draw(*mPerson);
}