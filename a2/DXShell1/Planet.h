/*
PROJECT NAME : SETTrek
FILE NAME	: Planet.h
DESCRIPTION : the purose of this file is to model a Planet object that constitute of the background of the game.
DATE : 2017-17-02
NAME OF THE PROGRAMMER : ARINDM SHARMA
*/
#pragma once
#include "GameLevel.h"
#include <cmath>

/*
Name : Ship
Purpose : this class acts as the model for a Planet object.
*/
class Planet
{
private:
	SpriteSheet* PlanetSprite; //planet sprite.
	float objWidth; // the width of a grid
	float objHeight; // the height of a grid
	float xPosition; //current x position coordinate
	float yPosition; //current y position coordinate
	Graphics * gfx; // the current gfx obj.

	//effect to store the chromekeyed images.
	ID2D1Effect *chromaPlanet;

public:
	//constructor for a planet
	Planet(wchar_t * filename, Graphics * gfx, float height, float width,float tolerance);
	//destructor for the class.
	~Planet();

	//accessors and mutators for the various private variables.
	void setXPosition(float value);
	float getXPosition();
	void setYPosition(float value);
	float getYPosition();

	//to draw a planet
	void Draw(float startX, float startY, float Width, float Height);


	ID2D1Effect* doChroma(SpriteSheet* ptr, float tolerance); // method to perform chromakey effect.
	ID2D1Bitmap* convertImageToBitmap(ID2D1Effect* pImg, D2D1_SIZE_U size); // convert the ID2D1Effect* to ID2D1Bitmap*.

};