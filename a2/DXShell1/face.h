#pragma once
#include "GameLevel.h"
#include <cmath>

#define PI 3.14159265

/*
Name : face
Purpose : this class acts as the model for a face object.
*/
class face
{
	//private variables
private:
	float beginningXPosition; // backup for the xposition.
	float beginningYPosition; //backup for the yposition
	float objWidth; // the width of a grid
	float objHeight; //the height of a grid
	float xPosition; // the current x coordinate.
	float yPosition;// the current y coordinate
	float finalX; // the destination x coordinate.
	float finalY;// the destination y coordinate.
	float distance; // the distance between dest and current positions
	float ConstSpeed;
	float xSpeed;
	float ySpeed;
	int whichrotation;
	float rotationangle;
	float centreX;
	float centreY;

	float tempwidth;
	float tempheight;

	SpriteSheet* headshot;//face sprite.

	//chromakeyed face effects
	ID2D1Effect *chromaface;

public:
	Graphics * gfx;

	//constructor for the face object.
	face(wchar_t* Basefilename, Graphics* gfx, float height, float width, float speed);

	//destructor
	~face();

	ID2D1Effect* doChroma(SpriteSheet* ptr, float tolerance, int whichOne); // method to perform chromakey effect.
	ID2D1Bitmap* convertImageToBitmap(ID2D1Effect* pImg, D2D1_SIZE_U size); // convert the ID2D1Effect* to ID2D1Bitmap*.

	void Draw();//for drawing the face

	float getXPosition();
	float getYPosition();
	void setXPosition(float value);
	void setYPosition(float value);

	float getfinalXPosition();
	float getfinalYPosition();
	void setfinalXPosition(float value);
	void setfinalYPosition(float value);

	float getconstantspeed();
	void setconstantspeed(float value);

	int getwhichrotation();
	void setwhichrotation(int value);

	float getCentreX();
	float getCentreY();

	float getWidth();
	float getHeight();

	float calculateSpeed(float finalval, float current);


	void updateCenterPoints();

	void calculateSpeedandDraw();

	void scaleUpDown(int updown);

	void drawWithRotation();

	void drawStill();
};