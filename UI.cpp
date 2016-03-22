#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <time.h>
#include "APEngine.h"
#include "UI.h"


UI::UI()
{
	// Buttons for each building type
	// Display for resources
	Globals::houseActive = false;
	Globals::barracksActive = false;
	Globals::housePressed = false;
	Globals::barracksPressed = false;

	mStoneAmnt = 0;
	mButtonBox = new sf::RectangleShape;
	mResources = new sf::RectangleShape;
	mHouse = new sf::RectangleShape;
	mBarracks = new sf::CircleShape;
	font = new sf::Font;

	mResources->setSize(sf::Vector2f(550, 50));
	mResources->setFillColor(sf::Color::White);
	mResources->setPosition(25, 25);

	mButtonBox->setSize(sf::Vector2f(100, 175));
	mButtonBox->setFillColor(sf::Color::White);
	mButtonBox->setPosition(1100, 450);

	mHouse->setSize(sf::Vector2f(50, 50));
	mHouse->setFillColor(sf::Color::Red);
	mHouse->setPosition(1125, 475);

	mBarracks->setRadius(25);;
	mBarracks->setFillColor(sf::Color::Blue);
	mBarracks->setPosition(1125, 550);

	font->loadFromFile("goodTimes.ttf");
	mWoodDisp = new sf::Text;
	mStoneDisp = new sf::Text;
	mTextStoneAmnt = new sf::Text;
	mTextWoodAmnt = new sf::Text;

	mTextStoneAmnt->setFont(*font);
	mTextStoneAmnt->setCharacterSize(12);
	mTextStoneAmnt->setColor(sf::Color::Black);
	mTextStoneAmnt->setPosition(sf::Vector2f(395, 45));

	mTextWoodAmnt->setFont(*font);
	mTextWoodAmnt->setCharacterSize(12);
	mTextWoodAmnt->setColor(sf::Color::Black);
	mTextWoodAmnt->setPosition(sf::Vector2f(110, 45));

	mWoodDisp->setString("Wood");
	mWoodDisp->setFont(*font);
	mWoodDisp->setCharacterSize(12);
	mWoodDisp->setColor(sf::Color::Black);
	mWoodDisp->setPosition(sf::Vector2f(35, 45));

	mStoneDisp->setString("Stone");
	mStoneDisp->setFont(*font);
	mStoneDisp->setCharacterSize(12);
	mStoneDisp->setColor(sf::Color::Black);
	mStoneDisp->setPosition(sf::Vector2f(300, 45));

}


void UI::Update(sf::RenderWindow* window)
{
	mousePos = sf::Mouse::getPosition(*window);
	mHouseSize = mHouse->getSize();
	mHousePos = mHouse->getPosition();
	mBarracksSize = mBarracks->getRadius();
	mBarracksPos = mBarracks->getPosition();

	//House Button
	//Check for overlapping x-coordinates
	if (mousePos.x >= mHousePos.x && mousePos.x <= (mHousePos.x + mHouseSize.x))
	{
		//Check for overlapping y-coordinates
		if (mousePos.y >= mHousePos.y && mousePos.y <= (mHousePos.y + mHouseSize.y))
		{
			if (!Globals::housePressed)
			{
				if (Globals::houseActive == false)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						//If Left Mouse button has not already been pressed,
						//mouse button pressed changes outline and shrinks size of button rectangle
						mHouse->setOutlineThickness(3);
						mHouse->setOutlineColor(sf::Color::Blue);
						mHouse->setSize(sf::Vector2f(55, 55));
						Globals::houseActive = true;
						Globals::housePressed = true;
					}
				}
				else
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						//If Left Mouse button has already been pressed,
						//mouse button pressed deletes outline and grows size of button rectangle
						mHouse->setOutlineThickness(0);
						mHouse->setSize(sf::Vector2f(50, 50));
						//set button color to white
						Globals::houseActive = false;
						Globals::housePressed = true;
					}
				}
			}
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
				Globals::housePressed = false;
		}
	}

	//Barracks Button
	//Check for overlapping x-coordinates
	if (mousePos.x >= mBarracksPos.x && mousePos.x <= (mBarracksPos.x + mBarracksSize))
	{
		//Check for overlapping y-coordinates
		if (mousePos.y >= mBarracksPos.y && mousePos.y <= (mBarracksPos.y + mBarracksSize))
		{
			if (!Globals::barracksPressed)
			{
				if (Globals::barracksActive == false)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						//If Left Mouse button has not already been pressed,
						//mouse button pressed changes outline and shrinks size of button rectangle
						mBarracks->setOutlineThickness(3);
						mBarracks->setOutlineColor(sf::Color::Yellow);
						mBarracks->setRadius(30);
						Globals::barracksActive = true;
						Globals::barracksPressed = true;

					}
				}
				else
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						//If Left Mouse button has already been pressed,
						//mouse button pressed deletes outline and grows size of button rectangle
						mBarracks->setOutlineThickness(0);
						mBarracks->setRadius(25);
						//set button color to white
						Globals::barracksActive = false;
						Globals::barracksPressed = true;
					}
				}
			}
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
				Globals::barracksPressed = false;
		}
	}
	/*
	for (int i = 0; i < Globals::mQuarries.size(); i++)
	{
	mStoneAmnt += Globals::mQuarries[i]->getStoneAmnt();
	}
	mStoneResourceAmnt = std::to_string(mStoneAmnt);
	*/
	mStoneResourceAmnt = std::to_string(Globals::playerStoneAmnt);
	mTextStoneAmnt->setString(mStoneResourceAmnt);

	mWoodResourceAmnt = std::to_string(Globals::playerWoodAmnt);
	mTextWoodAmnt->setString(mWoodResourceAmnt);
}

void UI::Draw(sf::RenderWindow* window)
{
	window->draw(*mButtonBox);
	window->draw(*mResources);
	window->draw(*mHouse);
	window->draw(*mBarracks);
	window->draw(*mWoodDisp);
	window->draw(*mStoneDisp);
	window->draw(*mTextStoneAmnt);
	window->draw(*mTextWoodAmnt);

	/*
	switch (LifeIndex)
	{
	case 3:
	window->draw(*Life1);
	window->draw(*Life2);
	window->draw(*Life3);
	break;
	case 2:
	window->draw(*Life1);
	window->draw(*Life2);
	break;
	case 1:
	window->draw(*Life1);
	break;
	case 0:
	break;
	}
	*/
}