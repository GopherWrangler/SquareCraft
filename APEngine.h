#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <time.h>
#include "Forest.h"
#include "Tree.h"
#include "Quarry.h"
#include "Building.h"
#include "People.h"
#include "Enemy.h"
#include "Warrior.h"
#include "Game.h"


#define MAX_SPEED 100.0f
#define NUM_WORKERS_TO_SPAWN 10
#define NUM_WARRIORS_TO_SPAWN 3
#define HARVEST_TIME_QUARRY .2f
#define HARVEST_TIME_LUMBER .2f

//---------------------------------Global Variables---------------------------------------//

class Globals
{
public:
	static bool housePressed;
	static bool barracksPressed;
	static bool houseActive;
	static bool barracksActive;	
	static int playerStoneAmnt;
	static int playerWoodAmnt;	
	static std::vector<Tree*> mDeadTrees;
	static std::vector<Quarry*> mQuarries;
	static std::vector<Quarry*> mDeadQuarries;
	static std::vector<Forest*> mForests;
	static std::vector<Building*> mBuildings;
	static std::vector<Enemy*> mEnemies;
};
