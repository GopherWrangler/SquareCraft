//Make General GameObject class to handle all the game objects, Forests, Buildings, People, etc are all subclasses of GameObject
//Can then call one Update and Draw function to handle all objects at once
//========Update, Draw, and any functions that would be shared between subclasses of Game Objects are virtual functions========//
//========virtual functions mean that function can be shared and overwritten by subclasses=====================================//
//=============================================================================================================================//

#include "stdafx.h"
#include "targetver.h"
#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include <vector>
#include <cmath>
#include <time.h>
#include "APEngine.h"
#include "UI.h"
#include "Building.h"
#include "Forest.h"
#include "Tree.h"
#include "Quarry.h"
#include "People.h"	
#include "Enemy.h"
#include "Warrior.h"
#include "Game.h"


//---------------------------------Global Variables---------------------------------------//

bool Globals::housePressed = false;
bool Globals::barracksPressed = false;
bool Globals::houseActive = false;
bool Globals::barracksActive = false;

int Globals::playerStoneAmnt = 0;
int Globals::playerWoodAmnt = 50;

std::vector<Tree*> Globals::mDeadTrees;
std::vector<Quarry*> Globals::mQuarries;
std::vector<Quarry*> Globals::mDeadQuarries;
std::vector<Forest*> Globals::mForests;
std::vector<Building*> Globals::mBuildings;
std::vector<Enemy*> Globals::mEnemies;

/*

//-----------------------------------------------------------------------------------------------------//
//----------------------------------Building Class-----------------------------------------------------//
/*
enum Structure
{
	HOUSE = 0,
	BARRACKS = 1
};

class Building
{
public:
	Building();
	Building(sf::RenderWindow*window, Structure type, sf::Vector2i mousePos);
	sf::Vector2f getBuildPos();
	void MinusHealth();
	int getHealth();
	void Update(sf::RenderWindow* window);
	void Draw(sf::RenderWindow* window);

private:
	int mHealth;
	Structure mType;
	sf::RectangleShape* mBase;
	sf::RectangleShape* mTop;
	sf::CircleShape* mRoof;
	sf::Vector2f mPos;


};

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
*/

//----------------------------------------------------------------------------------------//
//------------------------------Tree Class---------------------------------------------//
/*
class Tree
{
public:
	Tree(sf::Vector2f& size, sf::Vector2f& position, sf::Color& color);
	void setWoodLoad();
	int getWoodLoad();
	void deadTree();
	sf::Vector2f getTreePos();
	float dist(sf::Vector2f pos1, sf::Vector2f pos2);
	void Update(sf::Time dt);
	void Draw(sf::RenderWindow* window);

private:
	sf::RectangleShape* tree;
	int mWoodLoad;
	//std::vector<People> mLocalWorkers;

};

Tree::Tree(sf::Vector2f& size, sf::Vector2f& position, sf::Color& color)
{
	tree = new sf::RectangleShape;

	tree->setSize(sf::Vector2f(size));
	tree->setPosition(sf::Vector2f(position));
	tree->setFillColor(sf::Color(color));

	mWoodLoad = 200;
	
	
	/*
	mType = type;
	mPos.x = posX;
	mPos.y = posY;
	mVel.x = velX;
	mVel.y = velY;
	mRotVel = 0;
	mRot = 0;
	mTDeath = false;


	Size = window->getSize();

	switch (mType)
	{
	case BIG_ASTEROID:
		Asteroid = new sf::CircleShape;
		mRad = 75.0f;
		//Shape to represent BIG_ASTEROID
		Asteroid->setRadius(mRad);
		Asteroid->setPointCount(7);
		Asteroid->setFillColor(sf::Color::Blue);
		

		do
		{
			mPos.x = (((float)rand() / RAND_MAX) * Size.x);
			mPos.y = (((float)rand() / RAND_MAX) * Size.y);
		} 
		while (dist(mPos.x, mPos.y, Size.x / 2.0f, Size.y / 2.0f) < mRad+100);

		Asteroid->setPosition(mPos);
		mRotVect.x = BIG_ASTEROID_SPEED;
		mRotVect.y = 0;
		mVel = rotate(mRotVect, ((float)rand() / RAND_MAX) * 0 + 6.28f);
		mRotVel = ((float)rand() / RAND_MAX) * ASTEROID_ROT_SPEED + (-ASTEROID_ROT_SPEED);
		mRot = ((float)rand() / RAND_MAX) * 0 + 6.28f;
		printf("Made Big Asteroid\n");
		break;
	case SMALL_ASTEROID:
		//Shape to represent SMALL_ASTEROID
		Asteroid = new sf::CircleShape;
		mRad = 25.0f;

		Asteroid->setRadius(mRad);
		Asteroid->setPointCount(5);
		Asteroid->setFillColor(sf::Color::Green);
		mRotVect.x = SMALL_ASTEROID_SPEED;
		mRotVect.y = 0;
		mVel = rotate(mRotVect, ((float)rand() / RAND_MAX) * 0 + 6.28f);
		mRotVel = ((float)rand() / RAND_MAX) * ASTEROID_ROT_SPEED + (-ASTEROID_ROT_SPEED);
		mRot = ((float)rand() / RAND_MAX) * 0 + 6.28f;
		printf("Made Small Asteroid\n");
		break;
	case SHIP:
		//Shape for SHIP
		Asteroid = new sf::CircleShape;
		mRad = 20.0f;
		mPos.x = Size.x / 2.0f;
		mPos.y = Size.y / 2.0f;
		Asteroid->setRadius(mRad);
		Asteroid->setPointCount(3);
		Asteroid->setFillColor(sf::Color::Red);
		Asteroid->setOrigin(20.0f, 20.0f);
		Asteroid->setPosition(mPos);
		printf("Made Ship\n");
		break;
	case BULLET:
		//Shape for BULLET
		Asteroid = new sf::CircleShape;
		mRad = 3;
		Asteroid->setRadius(mRad);
		printf("Made Bullet\n");

		break;
	}
	
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
	}
}

void Tree::Draw(sf::RenderWindow* window)
{
	window->draw(*tree);
}

/*
sf::Vector2f SpaceObject::rotate(const sf::Vector2f &p, float angle)
{
	return sf::Vector2f(p.x * cos(angle) - p.y * sin(angle), p.x * sin(angle) + p.y * cos(angle));
}

float SpaceObject::dist(float x0, float y0, float x1, float y1)
{
	float dx = x1 - x0;
	float dy = y1 - y0;
	return sqrtf(dx*dx + dy*dy);
}


bool SpaceObject::collision(SpaceObject *obj)
{
	return dist(obj->mPos.x, obj->mPos.y, mPos.x, mPos.y) < obj->mRad + mRad;
}

void SpaceObject::normalizeVelocity()
{
	mVel.x = mVel.x / (mVel.x*mVel.x + mVel.y*mVel.y);
	mVel.y = mVel.y / (mVel.x*mVel.x + mVel.y*mVel.y);
}

void SpaceObject::Update(sf::Time dt)
{
	float time = dt.asSeconds();
	
	mRot += mRotVel*time;
	mPos += mVel*time;

	int W = Size.x;
	int H = Size.y;
	bool killBullet = false;
	if (mPos.x > W)
	{
		killBullet = true;
		mPos.x -= W;
	}
	else if (mPos.x < 0)
	{
		killBullet = true;
		mPos.x += W;
	}
	if (mPos.y > H)
	{
		killBullet = true;
		mPos.y -= H;
	}
	else if (mPos.y < 0)
	{
		killBullet = true;
		mPos.y += H;
	}

	if (mType == BULLET && killBullet)
	{
		//Get time of bullet hit then add 0.2 to kill ship
		mTDeath = true;
	}
	Asteroid->setPosition(mPos);
	Asteroid->setRotation(mRot);
}

void SpaceObject::Draw(sf::RenderWindow* window)
{
	window->draw(*Asteroid);
}
*/

//-----------------------------------------------------------------------------------------------------//
//----------------------------------Quarry Class-------------------------------------------------------//
/*
class Quarry
{
public:
	Quarry(sf::RenderWindow* window);
	int getStoneAmnt();
	void setStoneAmnt();
	sf::Vector2f getQuarrySize();
	sf::Vector2f getQuarryPos();
	void Update(sf::RenderWindow* window);
	void Draw(sf::RenderWindow* window);

	int m_stoneLoad;
	sf::Vector2f mPos;

private:
	sf::RectangleShape m_node;
	sf::Vector2u windowSize;



};

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
*/
//-----------------------------------------------------------------------------------------------------//
//----------------------------------Forest Class-------------------------------------------------------//
//std::vector<Tree*> Globals::mDeadTrees;

/*
class Forest
{
public:
	Forest(sf::RenderWindow* window);
	//int getWoodLoad(sf::RectangleShape* tree);
	//void setWoodLoad(Forest* forest, sf::RectangleShape* tree);
	sf::Vector2f getForestSize();
	void Update(sf::RenderWindow* window);
	void Draw(sf::RenderWindow* window);
	sf::Vector2f mPos;
	std::vector<Tree*> mTrees;
	//-----Make a new Tree class to handle wood deductions-------//
	//std::vector<int*> mWood;

private:
	//int* mWoodLoad;
	int randX;
	int randLength;
	int randDist;

	sf::Vector2u windowSize;
	sf::Vector2f mTreeSize;
	sf::Vector2f mTreePos;

	sf::RectangleShape* mTreeptimusPrime;

	//std::vector<sf::RectangleShape*> mTrees;
};

Forest::Forest(sf::RenderWindow* window)
{
	sf::Color treeColor;

	windowSize = window->getSize();
	//mWoodLoad = new int(100);

	mTreeptimusPrime = new sf::RectangleShape;
	mTreeptimusPrime->setSize(sf::Vector2f(20, 20));
	mPos.x = (((float)rand() / RAND_MAX) * windowSize.x);
	mPos.y = (((float)rand() / RAND_MAX) * windowSize.y);
	mTreeptimusPrime->setPosition(mPos);
	treeColor.r = 2;
	treeColor.g = 92;
	treeColor.b = 12;
	treeColor.a = 255;
	mTreeptimusPrime->setFillColor(treeColor);
	//mTrees.push_back(mTreeptimusPrime);

	//Initialize forest growth 
	/*mTree = new sf::RectangleShape;
	mTree->setSize(sf::Vector2f(20, 20));
	mTree->setFillColor(treeColor);

	for (int i = mPos.y; i < (mPos.y + 140); (i = i + 20))
	{
		randX = rand() % (-120) + 100;
		randLength = rand() % 180 + 160;
		randDist = rand() % 10 + 20;

		for (int j = mPos.x + randX; j < (mPos.x + randLength); (j = j + randDist))
		{
			mTreeSize.x = 20;
			mTreeSize.y = 20;
			mTreePos.x = j;
			mTreePos.y = i;

			mTrees.push_back(new Tree(mTreeSize, mTreePos, treeColor));
			//mWood.push_back(new int(100));

			randDist = rand() % 10 + 20;
		}
	}
}
/*
int Forest::getWoodLoad(sf::RectangleShape* tree)
{
for (int i = 0; i < mTrees.size(); i++)
{
if (mTrees[i] == tree)
{
return *mWood[i];
}
}
}

void Forest::setWoodLoad(Forest* forest, sf::RectangleShape* tree)
{
for (int i = 0; i < forest->mTrees.size(); i++)
{
if (forest->mTrees[i] == tree)
{
forest->mWood[i] -= 25;
}
}
}

sf::Vector2f Forest::getForestSize()
{
	//return mTree->getSize();
}

void Forest::Update(sf::RenderWindow* window)
{
	for (int i = 0; i < mTrees.size(); i++)
	{
		if (mTrees[i]->getWoodLoad() <= 0)
		{
			//mForDist1 = 2000;
			mTrees[i]->deadTree();

			Globals::mDeadTrees.push_back(mTrees[i]);
			mTrees.erase(mTrees.begin() + i);
		}
	}
}

void Forest::Draw(sf::RenderWindow* window)
{
	for (int i = 0; i < mTrees.size(); i++)
	{
		mTrees[i]->Draw(window);
	}

	//window->draw(*mTreeptimusPrime);
}
*/
//-----------------------------------------------------------------------------------------------------//
//----------------------------------People Class-------------------------------------------------------//

//std::vector<Quarry*> Globals::mQuarries;
//std::vector<Quarry*> mDeadQuarries;
//std::vector<Forest*> Globals::mForests;
//std::vector<Building*> mBuildings;
//std::vector<Enemy*> Globals::mEnemies;
//std::vector<People*> mWorkers;
//std::vector<sf::RectangleShape*> Globals::mDeadTrees;
/*
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
	//mSize = obj->getQuarrySize();  mPos is person location
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
		if (mBuildings[i] == homeBase)
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
				/*mVel = mNearestQuarry->getQuarryPos() - mPos;

				mVel.x *= dt.asSeconds();
				mVel.y *= dt.asSeconds();

				mPos += mVel;

				velMag = sqrtf((mVel.x*mVel.x) + (mVel.y*mVel.y));

				if (velMag > MAX_SPEED)
				{
				normalizeVelocity(mVel);
				mVel = mVel * MAX_SPEED;
				}
				
				/*
				//make separate function for pathing to node
				if (quarryCollisionDist(mNearestQuarry) <= 5 && returnCourse == false)
				{
				if (!timerStarted)
				{
				mVel.x = 0;
				mVel.y = 0;

				timer.restart();
				//time = timer.getElapsedTime();

				timerStarted = true;

				//Use time to have worker stop for 5 seconds, then return to house
				}
				else
				{
				if (time.asSeconds() < 5)
				{
				mVel.x = 0;
				mVel.y = 0;
				}
				else if (time.asSeconds() == 5)
				{
				mPos.x += 1;
				mPos.y += 1;
				returnCourse = true;
				timerStarted = false;
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
							playerStoneAmnt += 10;

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
							mDeadQuarries.push_back(Globals::mQuarries[i]);
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

							playerWoodAmnt += 5;

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

				/*
				for (int i = 0; i < mNearestForest->mTrees.size(); i++)
				{
				if (mNearestForest->mTrees[i] == mNearestTree)
				{
				if (mNearestForest->mWood[i] == 0)
				{
				mForDist1 = 2000;

				Globals::mDeadTrees.push_back(mNearestForest->mTrees[i]);
				mNearestForest->mTrees.erase(mNearestForest->mTrees.begin() + i);
				}
				}
				}
				
				/*
				velMag = sqrtf((mVel.x*mVel.x) + (mVel.y*mVel.y));

				if (velMag > MAX_SPEED)
				{
				normalizeVelocity(mVel);
				mVel = mVel * MAX_SPEED;
				}

				mPos += mVel;

				mPerson->setPosition(mPos.x, mPos.y);
				
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
*/
//-------------------------------Enemy Class-------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//
/*
class Enemy :public People
{
public:
	Enemy(sf::RenderWindow* window, sf::Vector2f* buildPos);
	void takeDamage();
	int getHealth();
	sf::Vector2f getPos();
	//float dist(float x0, float y0, float x1, float y1);
	float buildingCollisionDist(Building* obj);
	//float enemyCollisionDist(Enemy* enemy);
	//bool quarryCollision(Quarry* obj);
	//float quarryCollisionDist(Quarry* obj);
	//bool forestCollision(Forest* obj);
	//float forestCollisionDist(sf::Vector2f pos);
	//void normalizeVelocity(sf::Vector2f& vel);
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
	sf::Clock timer;
	sf::Time time;
	float mDist1;
	float mDist2;
	float mBuildDist;
	float mForDist2;
	float velMag;
	//Quarry* mNearestQuarry;
	//Forest* mNearestForest;
	//Tree* mNearestTree;
	Building* mNearestBuilding;

};

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

float Enemy::buildingCollisionDist(Building* obj)
{
	buildingPos = obj->getBuildPos();
	return dist(buildingPos.x, buildingPos.y, mPos.x, mPos.y);
}

void Enemy::Update(sf::RenderWindow* window, sf::Time& dt)
{
	//-------------------Find the nearest building to attack-----------------------//
	if (Globals::mBuildings.size() != NULL)
	{
		for (int i = 0; i < Globals::mBuildings.size(); i++)
		{
			mDist2 = buildingCollisionDist(mBuildings[i]);
			if (mDist2 < mDist1)
			{
				mBuildDist = mDist2;
				mDist1 = mDist2;
				mNearestBuilding = mBuildings[i];
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

	/*
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
	
}

void Enemy::Draw(sf::RenderWindow* window)
{
	window->draw(*mPerson);
}
*/

//-------------------------------------Warrior Class---------------------------------------//
//-----------------------------------------------------------------------------------------//
//std::vector<Enemy*> Globals::mEnemies;
/*
class Warrior:public People
{
public:
	Warrior(sf::RenderWindow* window, sf::Vector2f* buildPos, Building* homeBuilding);
	sf::Vector2f getPos();
	void MinusHealth();
	int getHealth();
	//float dist(float x0, float y0, float x1, float y1);
	//float buildingCollisionDist(Building* obj);
	float enemyCollisionDist(Enemy* enemy);
	//bool quarryCollision(Quarry* obj);
	//float quarryCollisionDist(Quarry* obj);
	//bool forestCollision(Forest* obj);
	//float forestCollisionDist(sf::Vector2f pos);
	//void normalizeVelocity(sf::Vector2f& vel);
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
	//Quarry* mNearestQuarry;
	//Forest* mNearestForest;
	//Tree* mNearestTree;
	Building* homeBarracks;
	Enemy* mNearestEnemy;
};

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
*/
//-----------------------------------------------------------------------------------------------------//
//----------------------------------Game Class---------------------------------------------------------//
/*
class Game
{
public:
	Game(sf::RenderWindow* window);
	float dist(float x0, float y0, float x1, float y1);
	void Loop(sf::RenderWindow* window, sf::Time dt);
	void Draw(sf::RenderWindow* window);

	//std::vector<Building*> mBuildings;
	std::vector<People*> mWorkers;
	std::vector<Warrior*> mWarriors;
	Building* homeBuilding;

	//void newLevel(sf::RenderWindow* window);
	//float degToRad(float deg);
	//sf::Vector2f rotate(const sf::Vector2f &p, float angle);
	//void GameOver(sf::RenderWindow* window);
	//void Loop(sf::RenderWindow* window, sf::Time dt);
	//void Death();
	// implementation of KeyboardListener:
	//void keyUp();
	//void keyDown(sf::RenderWindow* window);

private:
	bool btnPressed = false;
	
	float mDamageDist;
	
	sf::RectangleShape* bckGround;
	sf::RectangleShape* river;

	//std::vector<Quarry*> Globals::mQuarries;
	//std::vector<Forest*> Globals::mForests;
	//std::vector<Building*> mBuildings;

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

	SpaceObject* mShip;
	UI* snazyUI;

	std::vector<SpaceObject*> mAsteroids;
	std::vector<SpaceObject*> mBullets;
	
};

Game::Game(sf::RenderWindow* window)
{
	bckGround = new sf::RectangleShape;
	river = new sf::RectangleShape;
	snazyUI = new UI;
	pos = new sf::Vector2f;
	pos->x = 100;
	pos->y = 100;
	myEnemy = new Enemy(window, pos);
	Globals::mEnemies.push_back(myEnemy);
	
	bckGround->setPosition(0, 0);
	bckGround->setSize(sf::Vector2f(1280, 720));
	bckGround->setFillColor(sf::Color::Green);

	river->setPosition(350, 0);
	river->setSize(sf::Vector2f(100, 720));
	river->setFillColor(sf::Color::Blue);

	//Initialize Forests and Quarries
	int amnt;
	for (int i = 0; i < 3; i++)
	{
		Globals::mQuarries.push_back(new Quarry(window));
		amnt = Globals::mQuarries[i]->getStoneAmnt();
		printf("Stone amount: %d \n", amnt);
	}

	for (int i = 0; i < 2; i++)
	{
		Globals::mForests.push_back(new Forest(window));
	}


	/*
	gameOver = false;
	mForward = false;
	mLevel = 1;
	mLives = 3;
	lifeCase = 0;
	velMag = 0;
	endMsg.setString("Game Over!");
	mShip = new SpaceObject(window, SHIP);
	snazyUI = new UI;
	invulTime = clock.getElapsedTime();

	/*buffer1.loadFromFile("Laser Gun.wav");
	buffer2.loadFromFile("Explosion 01.wav");
	laser.setBuffer(buffer1);
	explosion.setBuffer(buffer2);

	// create some asteroids:
	for (int i = 0; i<MIN_ASTEROIDS + mLevel - 1; i++)
	{
		mAsteroids.push_back(new SpaceObject(window, BIG_ASTEROID));
	}
	printf("Set Up Game\n");
	
}
/*
void Game::newLevel(sf::RenderWindow* window)
{
	mLevel++;

	if (mShip != NULL)
	{
		delete mShip;
	}

	mShip = new SpaceObject(window, SHIP);
	for (int i = 0; i < MIN_ASTEROIDS + mLevel - 1; i++)
	{
		mAsteroids.push_back(new SpaceObject(window, BIG_ASTEROID));
	}

	while (mBullets.size() > 0)
	{
		delete *(mBullets.begin());
		mBullets.erase(mBullets.begin());
	}
}

float Game::degToRad(float deg)
{
	return deg * PI / 180.0f;
}

sf::Vector2f Game::rotate(const sf::Vector2f &p, float angle)
{
	return sf::Vector2f(p.x * cos(angle) - p.y * sin(angle), p.x * sin(angle) + p.y * cos(angle));
}

void Game::GameOver(sf::RenderWindow *window)
{
	window->draw(endMsg);
}

void Game::keyUp()
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		mLeft = false;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		mRight = false;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		mForward = false;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		//Arm gun again
		mGunArmed = true;
	}
}

void Game::keyDown(sf::RenderWindow* window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		mLeft = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		mRight = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		mForward = true;
	}

	//When spacebar pressed and gun is armed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && mGunArmed && mShip != NULL)
	{
		//Add bullet
		sf::Vector2f bulletVel = rotate(sf::Vector2f(0.0f, -BULLET_SPEED), degToRad(mShip->mRot));
		mBullets.push_back(new SpaceObject(window, BULLET, mShip->mPos.x, mShip->mPos.y, bulletVel.x, bulletVel.y));

		//laser.play();

		mGunArmed = false;
	}
}

void Game::Death()
{
	//Destroy the ship
	delete mShip;
	mShip = NULL;

	//Take away life and check for Game Over
	mLives--;
	lifeCase++;

	if (mLives == 0)
	{
		gameOver = true;
	}
	printf("Ship Died\n");
}
//Remake Ship 


float Game::dist(float x0, float y0, float x1, float y1)
{
	float dx = x1 - x0;
	float dy = y1 - y0;
	return sqrtf(dx*dx + dy*dy);
}

void Game::Loop(sf::RenderWindow* window, sf::Time dt)
{	
	//-------------When houseActive, ready to creat new house with mose button press-----------------//
	if (houseActive)
	{
		if (!btnPressed)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				mousePos = sf::Mouse::getPosition(*window);
				homePos.x = mousePos.x - 10;
				homePos.y = mousePos.y;
				homeBuilding = new Building(window, HOUSE, mousePos);
				Globals::mBuildings.push_back(homeBuilding);
				for (int i = 0; i < NUM_WORKERS_TO_SPAWN; i++)				
				{
					homePos.y += 10 + (i * 20);
					mWorkers.push_back(new People(window, &homePos, homeBuilding));
				}
				//newHouse = new Building(window, HOUSE, mousePos);
				btnPressed = true;
			}
		}
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			btnPressed = false;
		}	
	}
	//-------------When barracksActive, raedy to create new barracks with mouse button press-----------//
	if (barracksActive)
	{
		if (!btnPressed)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				mousePos = sf::Mouse::getPosition(*window);
				homePos.x = mousePos.x - 10;
				homePos.y = mousePos.y;
				homeBuilding = new Building(window, BARRACKS, mousePos);
				Globals::mBuildings.push_back(homeBuilding);
				for (int i = 0; i < NUM_WARRIORS_TO_SPAWN; i++)
				{
					homePos.y += 10 + (i * 10);
					mWarriors.push_back(new Warrior(window, &homePos, homeBuilding));
				}

				btnPressed = true;
			}
		}
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			btnPressed = false;
		}
	}
	
	//-----------------------Update all vectors for Workers, Quarries, DeadQuarries, Forests, Warriors, Enemies----------------------------//
	for (int i = 0; i < mWorkers.size(); i++)
	{
		mWorkers[i]->Update(window, dt);
	}

	for (int i = 0; i < Globals::mQuarries.size(); i++)
	{
		Globals::mQuarries[i]->Update(window);
	}

	if (mDeadQuarries.size() != NULL)
	{
		for (int i = 0; i < mDeadQuarries.size(); i++)
		{
			mDeadQuarries[i]->Update(window);
		}
	}

	for (int i = 0; i < Globals::mForests.size(); i++)
	{
		Globals::mForests[i]->Update(window);
	}

	if (mWarriors.size() != NULL)
	{
		for (int i = 0; i < mWarriors.size(); i++)
		{
			mWarriors[i]->Update(window, dt);
		}
	}

	for (int i = 0; i < Globals::mEnemies.size(); i++)
	{
		Globals::mEnemies[i]->Update(window, dt);
		if (Globals::mEnemies[i]->getHealth() <= 0)
		{
			Globals::mEnemies.erase(Globals::mEnemies.begin() + i);
		}
	} 
	

	if (Globals::mBuildings.size() != NULL && Globals::mEnemies.size() != NULL)
	{
		for (int i = 0; i < Globals::mBuildings.size(); i++)
		{
			for (int j = 0; j < Globals::mEnemies.size(); j++)
			{
				mBuildingDamagePos = mBuildings[i]->getBuildPos();
				mEnemyDamagePos = Globals::mEnemies[j]->getPos();
				mDamageDist = dist(mBuildingDamagePos.x, mBuildingDamagePos.y, mEnemyDamagePos.x, mEnemyDamagePos.y);

				if (mDamageDist <= 5)
				{
					mBuildings[i]->MinusHealth();
				}
				if (mBuildings[i]->getHealth() <= 0)
				{
					Globals::mBuildings.erase(Globals::mBuildings.begin() + i);
				}
			}
		}
	}
	
	snazyUI->Update(window);
	
	
/*	
	keyDown(window);
	keyUp();

	/*if (mShip != NULL)
	{
		velMag = sqrtf((mShip->mVel.x*mShip->mVel.x) + (mShip->mVel.y*mShip->mVel.y));
	}
		
	//Update the Ship
	if (mShip != NULL)
	{
		mShip->Update(dt);
		velMag = sqrtf((mShip->mVel.x*mShip->mVel.x) + (mShip->mVel.y*mShip->mVel.y));

		if (mLeft && !mRight)
		{
			mShip->mRotVel = -SHIP_ROT_SPEED;
		}
		else if (mRight && !mLeft)
		{
			mShip->mRotVel = SHIP_ROT_SPEED;
		}
		else
		{
			mShip->mRotVel = 0;
		}

		if (mForward)
		{
			mShip->mVel += rotate(sf::Vector2f(0, -SHIP_ACCEL), degToRad(mShip->mRot));
		}
		else if (!mForward)
		{
			mShip->mVel.x = 0.0f;
			mShip->mVel.y = 0.0f;
		}

		if (velMag > SHIP_MAX_SPEED)
		{
			mShip->normalizeVelocity();
			mShip->mVel = mShip->mVel * SHIP_MAX_SPEED;
		}
		//printf("Updated Ship\n");
	}
	else if (!gameOver && mShip == NULL)
	{
		mShip = new SpaceObject(window, SHIP);
		//invulTime = new sf::Time;
		clock.restart();
		printf("Created New Ship\n");
	}

	//Update the Asteroids
	for (int i = mAsteroids.size() - 1; i >= 0; i--)
	{
		mAsteroids[i]->Update(dt);

		//Check for Asteroid collision with bullets
		for (int j = mBullets.size() - 1; j >= 0; j--)
		{
			if (mAsteroids[i]->collision(mBullets[j]))
			{
				//If collides with a large asteroid, make two small asteroids
				Objects Aster = mAsteroids[i]->mType;
				switch (Aster)
				{
				case BIG_ASTEROID:
					mAsteroids.push_back(new SpaceObject(window, SMALL_ASTEROID, mAsteroids[i]->mPos.x, mAsteroids[i]->mPos.y));
					mAsteroids.push_back(new SpaceObject(window, SMALL_ASTEROID, mAsteroids[i]->mPos.x, mAsteroids[i]->mPos.y));
					break;
				case SMALL_ASTEROID:
					break;
				}
				//Mark the hit asteroid for death
				mAsteroids[i]->mTDeath = true;

				//Mark bullet for death
				mBullets[j]->mTDeath = true;

				//explosion.play();

				//+Score

			}
		}
		//If asteroid collides with the ship
		if (mShip != NULL && mAsteroids[i]->collision(mShip))
		{
			invulTime = clock.getElapsedTime();
			if (invulTime.asSeconds() >= INVUL_TIME)
			{
				Death();
			}
			//Death();
		}
	}
	//printf("Updated Asteroids\n");
	//Remove dead asteroids
	for (int i = mAsteroids.size() - 1; i >= 0; i--)
	{
		if (mAsteroids[i]->mTDeath == true)
		{
			mAsteroids.erase(mAsteroids.begin() + i);
		}
	}
	//Update the bullets
	for (int i = mBullets.size() - 1; i >= 0; i--)
	{
		mBullets[i]->Update(dt);
		if (mBullets[i]->mTDeath == true)
		{
			mBullets.erase(mBullets.begin() + i);
		}
	}

	//If All asteroids destroyed, go to next level
	if (mAsteroids.size() == 0)
	{
		newLevel(window);
	}

	//Update the UI
	snazyUI->Update(window, lifeCase);

	if (gameOver)
	{
		GameOver(window);
	}
	
}

void Game::Draw(sf::RenderWindow* window)
{	
	window->draw(*bckGround);
	window->draw(*river);

	for (int i = 0; i < Globals::mQuarries.size(); i++)
	{
		Globals::mQuarries[i]->Draw(window);
	}

	if (mDeadQuarries.size() != NULL)
	{
		for (int i = 0; i < mDeadQuarries.size(); i++)
		{
			mDeadQuarries[i]->Draw(window);
		}
	}
	
	if (Globals::mForests.size() != NULL)
	{
		for (int i = 0; i < Globals::mForests.size(); i++)
		{
			Globals::mForests[i]->Draw(window);
		}
	}

	if (Globals::mBuildings.size() != NULL)
	{
		for (int i = 0; i < Globals::mBuildings.size(); i++)
		{
			mBuildings[i]->Draw(window);
		}
	}
	
	if (mWorkers.size() != NULL)
	{
		for (int i = 0; i < mWorkers.size(); i++)
		{
			mWorkers[i]->Draw(window);
		}
	}
	
	if (mWarriors.size() != NULL)
	{
		for (int i = 0; i < mWarriors.size(); i++)
		{
			mWarriors[i]->Draw(window);
		}
	}
	
	if (Globals::mEnemies.size() != NULL)
	{
		for (int i = 0; i < Globals::mEnemies.size(); i++)
		{
			Globals::mEnemies[i]->Draw(window);
		}
	}

	snazyUI->Draw(window);

	
	/*
	//draw the ship
	if (mShip != NULL)
	{
		mShip->Draw(window);
	}

	//draw asteroids
	for (int i = 0; i < mAsteroids.size(); i++)
	{
		mAsteroids[i]->Draw(window);
	}

	//draw bullets
	for (int i = 0; i < mBullets.size(); i++)
	{
		mBullets[i]->Draw(window);
	}

	//draw UI
	snazyUI->Draw(window);
	
}
*/


int _tmain(int argc, _TCHAR* argv[])
{

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Cubecraft");

	Game myGame(&window);

	sf::Clock clock;

	//Globals::playerStoneAmnt = 0;
	//Globals::playerWoodAmnt = 50;

    while (window.isOpen())
    {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		sf::Time dt = clock.restart();

		window.clear();

		myGame.Loop(&window, dt);
		myGame.Draw(&window);   			

		window.display();
    }

	return 0;
}

