/*
PROJECT NAME : SETTrek
FILE NAME	: Ship.h
DESCRIPTION : the purose of this file is to model a spaceship that are the main charaters of our game.
DATE : 2017-17-02
NAME OF THE PROGRAMMER : ARINDM SHARMA
*/
#pragma once
#include "GameLevel.h"
#include <cmath>

#define PI 3.14159265

/*
Name : Ship
Purpose : this class acts as the model for a ship object.
*/
class Ship 
{
	//private variables
private:
	float beginningXPosition; // backup for the xposition.
	float beginningYPosition; //backup for the yposition
	float ConstSpeed; //the constant speed with which we wish to travel
	float health; // the energy/heath of the ships
	float Science; // the score 
	float finalX; // the destination x coordinate.
	float finalY;// the destination y coordinate.
	float xPosition; // the current x coordinate.
	float yPosition;// the current y coordinate.
	float objWidth; // the width of a grid
	float objHeight; //the height of a grid
	float distance; // the distance between dest and current positions
	float angle; // the angle of rotation
	float xSpeed; // the increase in x coordinate.
	float ySpeed; // the increase in y coordinate.
	float centreX; // the centreof the ship - x coordinate.
	float centreY;// the centreof the ship - y coordinate.
	bool shiptype; // the type of ship - player/enemy
	bool initial; // if its the first time after refres/start
	
	bool stay;

	SpriteSheet* spaceship;//spaceship sprite.
	SpriteSheet* spaceship2;//spaceship sprite.
	SpriteSheet *explosion; //exlosion for collision
	SpriteSheet *sheild; //sheild for collision


	//chromakeyed ship effects
	ID2D1Effect *chromaspaceship; 
	ID2D1Effect *chromaspaceship2;
	ID2D1Effect *chromaexplosion;
	ID2D1Effect*chromasheild;

public:
	Graphics * gfx;
	//constructors:
	//constructor for the player ship
	Ship(wchar_t* Basefilename, wchar_t* Detailfilename, Graphics* gfx, float height, float width);
	//constructor for the evil enemy ship
	Ship(wchar_t* filename, Graphics* gfx, float height, float width);
	//destructor:
	~Ship();

	//public methods
	//setters and getters for the various private variables.
	float getXSpeed();
	float getYSpeed();
	void setScience(float value);
	float getScience();
	void setInitialBool(bool value);
	void setHealth(float value);
	float getHealth();
	void setXPosition(float value);
	float getXPosition();
	void setYPosition(float value);
	float getYPosition();
	void setFinalYPosition(float value);
	float getFinalYPosition();
	void setFinalXPosition(float value);
	float getFinalXPosition();
	void setAngle(float value);
	float getAngle();
	float getConstantSpeed();
	void setConstantSpeed(float value);
	float getBeginningXPosition();
	void setBeginningXPosition(float value);
	float getBeginningYPosition();
	void setBeginningYPosition(float value);
	float getCentreX();
	float getCentreY();
	void setStay(bool value);
	float calculateSpeed(float finalval, float current);
	bool getStay() { return stay; }
	
	float calcD();//calculates the distance between the dest cordinate and current coordinate

	void Draw();//for drawing the planet

	ID2D1Effect* doChroma(SpriteSheet* ptr, float toleranceint,int whichOne); // method to perform chromakey effect.
	ID2D1Effect* doComposite(SpriteSheet * image1, SpriteSheet * image2); // method to perform composite effect.
	ID2D1Bitmap* convertImageToBitmap(ID2D1Effect* pImg, D2D1_SIZE_U size); // convert the ID2D1Effect* to ID2D1Bitmap*.

	float rotate();//to find the angle of rotation

	void updateCenterPoints(); //set the centre points with respect to the origin points of ship.

	void resetShip(); // reset the ship object to start all over again

	void changeShips(wchar_t* Basefilename, wchar_t* Detailfilename);

	void explode();

	void DrawSheild();
};