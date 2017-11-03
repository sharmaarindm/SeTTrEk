/*
PROJECT NAME : SETTrek
FILE NAME	: SpriteSheet.h
DESCRIPTION : the purose of this file is to setup the sprisheet that will inturn help to transform and draw the varous objects.
NAME OF THE PROGRAMMER : ARINDM SHARMA
*/

#pragma once

#include <wincodec.h> //This is the WIC codec header - we need this to decode image files
#include "Graphics.h" //This includes both Windows and D2D libraries
//Remember to add "windowscodecs.lib" to your Linker/Input/AdditionalDependencies

class SpriteSheet
{
	Graphics* gfx; //Reference to the Graphics class

public:
	ID2D1Bitmap* bmp; //This will hold our loaded and converted Bitmap file

	//Constructor
	SpriteSheet(wchar_t* filename, Graphics* gfx);

	//Destructor
	~SpriteSheet();

	//Draw bitmap to the render target
	void Draw();
	void Draw(float startX, float startY, float Width, float Height);

};