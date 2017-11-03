/*
PROJECT NAME : SETTrek
FILE NAME	: GameController.h
DESCRIPTION : the purose of this file is act as the gamecontroller for our settrek game.
DATE : 2017-17-02
NAME OF THE PROGRAMMER : ARINDM SHARMA
*/
#pragma once

#include "GameLevel.h"
#include "Graphics.h"

/*
Name : Level1
This will be a Singleton class (constructor is private)
*/
class GameController
{
	GameController() {}
	static GameLevel* currentLevel;
public:
	static bool Loading;
	static void Init();
	static void LoadInitialLevel(GameLevel* lev);
	static void SwitchLevel(GameLevel* lev);
	static void Render();
	static void Update(double x, double y, bool MD);
};