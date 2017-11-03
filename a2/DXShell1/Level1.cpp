/*
PROJECT NAME : SETTrek
FILE NAME	: Level1.cpp
DESCRIPTION : the purose of this file is to create a visual spaceship and 
planets(by removing the greenscreen) and display it to the screen.
DATE : 2017-17-02
NAME OF THE PROGRAMMER : ARINDM SHARMA
*/

#include "GameController.h"
#include "Graphics.h"
#include "Level1.h"
#pragma warning(push)
#pragma warning(disable: 4005)
#include <intsafe.h>

#pragma warning(pop)

/*
Meathod		: Level1()
DESCRIPTION : the purose of this method is to act as the constructor of the Level1 class 
and the initialize the required variables.
PARAMETERS  : none
RETURNS     : nothing
*/
Level1::Level1()
{
	//storing the value of current screen width and height
	screenWidth = gfx->GetRenderTarget()->GetSize().width;
	screenHeight = gfx->GetRenderTarget()->GetSize().height;

	//diving the space into 100 squares 10 per row each column
	objWidth = screenWidth / 10;
	objHeight = screenHeight / 10;

	soundeffects = new sound();
	soundeffects->backgroundSoundStart();

	changedir = true;
	changedir2 = true;
	changerotate = true;
	scale = true;
}

Level1::~Level1()
{
	soundeffects->backgroundSoundStop();
}

/*
Meathod		: Load()
DESCRIPTION : the purose of this method is to load all the object images from the provided bmp's
PARAMETERS  : none
RETURNS     : nothing
*/
void Level1::Load()
{
	/* initialize random seed: */
	srand(time(NULL));

	int i = (int)screenWidth - objWidth;
	int j = (int)screenHeight - objHeight;
	//between 1 and width/height
	float randXpos = rand() % i + 1;
	float randYpos = rand() % j + 1;
	// specifying file systems.
	sprites = new SpriteSheet(L"background.bmp", gfx); 

	float randspeed = rand() % 4 + 1;

	face1 = new face(L"face1.bmp",gfx, objHeight, objWidth, randspeed);
	face1->setXPosition(randXpos);
	face1->setYPosition(randYpos);

	//between 1 and width/height
	randXpos = rand() % i + 1;
	randYpos = rand() % j + 1;

	randspeed = rand() % 4 + 1;

	face2 = new face(L"face1.bmp", gfx, objHeight, objWidth, randspeed);
	face2->setXPosition(randXpos);
	face2->setYPosition(randYpos);

	//between 1 and width/height
	randXpos = rand() % i + 1;
	randYpos = rand() % j + 1;

	face1->setfinalXPosition(randXpos);
	face1->setfinalYPosition(randYpos);

	//between 1 and width/height
	randXpos = rand() % i + 1;
	randYpos = rand() % j + 1;

	face2->setfinalXPosition(randXpos);
	face2->setfinalYPosition(randYpos);

	//start = std::chrono::high_resolution_clock::now();
	start = clock();

	int ifrotate = rand() % (3 - 1 + 1) + 1;

	face1->setwhichrotation(ifrotate);
	ifrotate = rand() % (3 - 1 + 1) + 1;
	face2->setwhichrotation(ifrotate);

	//face1->scaleUpDown(1);

}

/*
Meathod		: Unload()
DESCRIPTION : the purose of this method is to delete all the used memory allocations in the end.
PARAMETERS  : none
RETURNS     : nothing
*/
void Level1::Unload()
{
	delete sprites;
}

/*
Meathod		: Update()
DESCRIPTION : the purose of this method is to update the position of the ship each time its called 
and randomise planets when the x poisiton of the ship exceeds the screenwidth.
PARAMETERS  : none
RETURNS     : nothing
*/
void Level1::Update(double xpos, double ypos, bool MD)
{


}

/*
Meathod		: Render()
DESCRIPTION : the purose of this method is to print out all the differentg spritesheet 
objects onto the screen
PARAMETERS  : none
RETURNS     : nothing
*/
void Level1::Render()
{
	clock_t end = (clock() - start)/(double)CLOCKS_PER_SEC;
	//auto end = std::chrono::high_resolution_clock::now() - start;
	//seconds = std::chrono::duration_cast<std::chrono::seconds>(end).count();
	seconds = end;
	soundeffects->backgroundSoundPlay();

	if (((faceDistance() <= objWidth) || (faceDistance() <= objHeight) || (face2->getXPosition() >= screenWidth)) && (changedir2)) //if the faces collide
	{
		
		int i = (int)screenWidth - objWidth;
		int j = (int)screenHeight - objHeight;

		float randspeed = rand() % 4 + 1;
		face1->setconstantspeed(randspeed);
		randspeed = rand() % 4 + 1;
		face2->setconstantspeed(randspeed);

		//between 1 and width/height
		float randXpos = rand() % i + 1;
		float randYpos = rand() % j + 1;

		face1->setfinalXPosition(randXpos);
		face1->setfinalYPosition(randYpos);

		randXpos = rand() % i + 1;
		randYpos = rand() % j + 1;

		face2->setfinalXPosition(randXpos);
		face2->setfinalYPosition(randYpos);
		changedir2 = false;
	}
	else
	{
		changedir2 = true;
	}

	if ((seconds % 5 == 0) &&(changedir))//change direction and speed
	{

		int i = (int)screenWidth - objWidth;
		int j = (int)screenHeight - objHeight;

		float randspeed = rand() % 4 + 1;
		face1->setconstantspeed(randspeed);
		randspeed = rand() % 4 + 1;
		face2->setconstantspeed(randspeed);

		//between 1 and width/height
		float randXpos = rand() % i + 1;
		float randYpos = rand() % j + 1;

		face1->setfinalXPosition(randXpos);
		face1->setfinalYPosition(randYpos);

		randXpos = rand() % i + 1;
		randYpos = rand() % j + 1;

		face2->setfinalXPosition(randXpos);
		face2->setfinalYPosition(randYpos);

		changedir = false;
	}
	else if ((seconds % 5 != 0))
	{
		changedir = true;
	}
	if ((seconds % 3 == 0)&&(changerotate)) //rotate
	{
		int randNum = rand() % (3 - 1 + 1) + 1;
		face1->setwhichrotation(randNum);
		randNum = rand() % (3 - 1 + 1) + 1;
		face2->setwhichrotation(randNum);
		changerotate = false;
	}
	else if((seconds % 3 != 0))
	{
		changerotate = true;
	}

	if ((seconds % 2 == 0) &&(scale))//shrink - scale up
	{
		srand(time(NULL));
		int randNum = rand() % (2 - 1 + 1) + 1;

		face1->scaleUpDown(randNum);
		randNum = rand() % (2 - 1 + 1) + 1;
		face2->scaleUpDown(randNum);

		scale = false;
	}
	else if (seconds % 2 != 0)
	{
		scale = true;
	}

	sprites->Draw();
	face1->Draw();
	face2->Draw();
}

/*
Meathod		: randomizePlanets()
DESCRIPTION : the purose of this method is to place planets at random 
positions on the grid.
PARAMETERS  : none
RETURNS     : nothing
*/
void Level1::randomizePlanets()
{
	float dice = 0.0;
	
	//intialize random seed.
	srand(time(NULL));
	float whichOne = 0.0; // denotes the planed number (1,2,3)
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			dice = rand() % 100 + 1;// random number between 1-100
			if (dice < 6) //making sure its a 20% chance
			{
				whichOne = rand() % 3 + 1;
				grid[i][j] = whichOne;
			}
			else // if no planet has to go there.
			{
				grid[i][j] = 0; 
			}
		}
	}
}

/*
Meathod		: randomEnergyScience()
DESCRIPTION : the purose of this method is to generate a random number between 0-300 for energy and science.
PARAMETERS  : none
RETURNS     : int - the random number
*/
int Level1::randomEnergyScience()
{
	/* generate a number between 0 and 300: */
	int retval = rand() % 300 + 0;
	return retval;
}

/*
Meathod		: shipDistance()
DESCRIPTION : the purose of this method is to calculate the distance between the two ships.
PARAMETERS  : none
RETURNS     : float - the distance
*/
float Level1::faceDistance()
{
	float retval = 0.0;

	retval = sqrt(pow(face1->getXPosition() - face2->getXPosition(), 2) + pow(face1->getYPosition() - face2->getYPosition(), 2));
	return retval;
}

/*
Meathod		: planetCollissionDetection()
DESCRIPTION : the purose of this method is to check if the planets exist at the current coordinate or not.
PARAMETERS  : none
RETURNS     : bool - the status code 
*/
bool Level1::planetCollissionDetection()
{

	/*int currentGridVal = 0;
	float gridCentreX;
	float gridCentreY;
	float distance;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{	
			currentGridVal = grid[i][j];
			if ((currentGridVal == 1) || (currentGridVal == 2) || (currentGridVal == 3))
			{
				gridCentreX= generateCentreX(i);
				gridCentreY = generateCentreY(j);
				
				distance = calculateDistance(gridCentreX, PlayerShip->getCentreX(), gridCentreY, PlayerShip->getCentreY());
				if ((distance < objHeight/1.5) && (distance < objWidth/1.5))
				{
					currentPlanetType = currentGridVal;
					grid[i][j] = 0;
					todraw = true;
					return true;
				}

			}
		}
	}*/

	return false;
}

/*
Meathod		: generateCentreX()
DESCRIPTION : the purose of this method is to find the centre x coordinate of a given ship.
PARAMETERS  : float 
RETURNS     : float - the centre x value
*/
float Level1::generateCentreX(float value)
{
	float retval;
	retval = value*objWidth + objWidth / 2;

	return retval;
}

/*
Meathod		: generateCentreY()
DESCRIPTION : the purose of this method is to find the centre y coordinate of a given ship.
PARAMETERS  : float
RETURNS     : float - the centre y value
*/
float Level1::generateCentreY(float value)
{
	float retval;
	retval = value*objHeight + objHeight / 2;

	return retval;
}

/*
Meathod		: calculateDistance()
DESCRIPTION : the purose of this method is to calculate the distance between 2 give points
PARAMETERS  : float x1, float x2, float y1 , float y2
RETURNS     : float - the distance
*/
float Level1::calculateDistance(float x1, float x2, float y1 , float y2)
{
	float retval;
	retval = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	
	return retval;
}

/*
Meathod		: setTextFormat()
DESCRIPTION : the purose of this method is to setup a text format for the given font size.
PARAMETERS  : const FLOAT msc_fontSize
RETURNS     : nothing
*/
void Level1::setTextFormat(const FLOAT msc_fontSize)
{
	gfx->GetWriteFactory()->CreateTextFormat(
		L"Verdana",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		msc_fontSize,
		L"", //locale
		&m_pTextFormat
	);
}

/*
Meathod		: drawTextAmeth()
DESCRIPTION : the purose of this method is to draw a given text at a given location.
PARAMETERS  : const wstring toWrite,float x1, float y1, float x2, float y2
RETURNS     : nothing
*/
void Level1::drawTextAmeth(const wstring toWrite,float x1, float y1, float x2, float y2)
{
	gfx->GetRenderTarget()->DrawTextA(
		toWrite.c_str(),
		toWrite.size(),
		m_pTextFormat,
		D2D1::RectF(x1, y1, x2, y2),
		m_pBlackBrush
	);
}
