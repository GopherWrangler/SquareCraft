#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <time.h>
#include "APEngine.h"
#include "Forest.h"
#include "Tree.h"


Forest::Forest()
{

}

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
}