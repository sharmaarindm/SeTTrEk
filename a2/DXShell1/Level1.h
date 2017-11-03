/*
PROJECT NAME : SETTrek
FILE NAME	: Level1.h
DESCRIPTION : the purose of this file is to create a visual spaceship and
planets(by removing the greenscreen) and display it to the screen.
DATE : 2017-17-02
NAME OF THE PROGRAMMER : ARINDM SHARMA
*/
#pragma once
#include "GameLevel.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <random>
#include "face.h"
#include <string>
#include <thread>

#include "sound.h"
//#include "wave.h"

#include <locale>
#include <codecvt>

using namespace std;
/*
Name : Level1
Purpose : this class acts as the game controller for the Set Trek game.
*/
class Level1 : public GameLevel
{
	sound *soundeffects;

	float x; //position of the spaceship
	IDWriteTextFormat* m_pTextFormat;
	ID2D1SolidColorBrush * m_pBlackBrush;


	face* face1;
	face* face2;

	float ClickX;
	float ClickY;
	int currentPlanetType;

	SpriteSheet* sprites; //background sprite.

	bool explosion;
	bool stopproc;
	bool UiMode;
	bool shieldActive; //bool id teh shield is active or not.
	bool todraw; //bool to signify if ui is needed or not
	float objWidth; // width of the small grid square.
	float objHeight; // height of the small grid square.
	float screenWidth; // overall width of the screen
	float screenHeight; // overall height of the screen 
	float grid[10][10]; // the 10x10 grid storing the various values (1,2,3,0)

	int currentScience; //vlaue for the science on the planet
	int currentEnergy;//value fot the enegergy on the planet

	int explosiontimer;

	clock_t start;

	long long seconds;

	bool randEnergySci;
	bool theForce;
	bool collision;
	bool changedir;
	bool changedir2;
	bool changerotate;
	bool scale;
public:
	// constructor
	Level1();

	//destructor
	~Level1();

	//overriden methods from gamelevel class.
	void Load() override;
	void Unload() override;
	void Update(double xpos, double ypos, bool MD) override;
	void Render() override;

	void randomizePlanets(); // randomize the planet position.
	int randomEnergyScience(); //get random science and energy
	float faceDistance(); //get the distance between the 2 ships
	bool planetCollissionDetection(); //check for collision detection

	float generateCentreX(float value); //calculate the centre x value
	float generateCentreY(float value); //calculate the centre y value

	float calculateDistance(float x1, float x2, float y1, float y2); //calculate distance between 2 give points
	void setTextFormat(const FLOAT msc_fontSize); //set the font size.
	void drawTextAmeth(const wstring toWrite, float x1, float y1, float x2, float y2);//draw the given wstring at the provided coordinates.

};
