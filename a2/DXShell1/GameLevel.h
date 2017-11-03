/*
PROJECT NAME : SETTrek
FILE NAME	: GameLevel.h
DESCRIPTION : The intent of the GameLevel class is to provide virtual methods that whichever class inherits it has to implement.
DATE : 2017-17-02
NAME OF THE PROGRAMMER : ARINDM SHARMA
*/

#pragma once

#include "Graphics.h"
#include "SpriteSheet.h"

/*
Name : Ship
Purpose : this class acts as the model for a Gamelevel object.
*/
class GameLevel
{
protected:
	static Graphics* gfx; //current graphics object

public:
	static void Init(Graphics* graphics)
	{
		gfx = graphics;
	}

	//virtual methods.
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(double xpos, double ypos, bool MD) = 0;
	virtual void Render() = 0;
};