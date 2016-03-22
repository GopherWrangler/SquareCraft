#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <time.h>
#include "APEngine.h"
#include "UI.h"
#include "Tree.h"
#include "Forest.h"
#include "Quarry.h"
#include "People.h"
#include "Enemy.h"
#include "Building.h"
#include "Warrior.h"
#include "Game.h"

Game::Game(sf::RenderWindow* window)
{
	btnPressed = false;
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
*/

float Game::dist(float x0, float y0, float x1, float y1)
{
	float dx = x1 - x0;
	float dy = y1 - y0;
	return sqrtf(dx*dx + dy*dy);
}

void Game::Loop(sf::RenderWindow* window, sf::Time dt)
{
	//-------------When houseActive, ready to creat new house with mose button press-----------------//
	if (Globals::houseActive)
	{
		printf("\nLooping");
		if (!btnPressed)
		{
			// If Mouse still hovering over button, do not spawn house
			// ******* //
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
				printf("\nHouse Created");
			}
		}
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			btnPressed = false;
		}
	}
	//-------------When barracksActive, raedy to create new barracks with mouse button press-----------//
	if (Globals::barracksActive)
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

	if (Globals::mDeadQuarries.size() != NULL)
	{
		for (int i = 0; i < Globals::mDeadQuarries.size(); i++)
		{
			Globals::mDeadQuarries[i]->Update(window);
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
				mBuildingDamagePos = Globals::mBuildings[i]->getBuildPos();
				mEnemyDamagePos = Globals::mEnemies[j]->getPos();
				mDamageDist = dist(mBuildingDamagePos.x, mBuildingDamagePos.y, mEnemyDamagePos.x, mEnemyDamagePos.y);

				if (mDamageDist <= 5)
				{
					Globals::mBuildings[i]->MinusHealth();
				}
				if (Globals::mBuildings[i]->getHealth() <= 0)
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
	*/
}

void Game::Draw(sf::RenderWindow* window)
{
	window->draw(*bckGround);
	window->draw(*river);

	for (int i = 0; i < Globals::mQuarries.size(); i++)
	{
		Globals::mQuarries[i]->Draw(window);
	}

	if (Globals::mDeadQuarries.size() != NULL)
	{
		for (int i = 0; i < Globals::mDeadQuarries.size(); i++)
		{
			Globals::mDeadQuarries[i]->Draw(window);
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
			Globals::mBuildings[i]->Draw(window);
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

}