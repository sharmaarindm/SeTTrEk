/*
PROJECT NAME : SETTrek
FILE NAME	: GameController.cpp
DESCRIPTION : the purose of this file is to act as the gamecontroller for our settreck game.
DATE : 2017-17-02
NAME OF THE PROGRAMMER : ARINDM SHARMA
*/

#include "GameController.h"

GameLevel* GameController::currentLevel;
bool GameController::Loading;

/*
Meathod		: Init()
DESCRIPTION : the purose of this method is to setup the current level of the game.
PARAMETERS  : none
RETURNS     : nothing
*/
void GameController::Init()
{
	Loading = true;
	currentLevel = 0;
}

/*
Meathod		: LoadInitialLevel()
DESCRIPTION : the purose of this method is to setup the current level to the provided level of the game.
PARAMETERS  : GameLevel* lev
RETURNS     : nothing
*/
void GameController::LoadInitialLevel(GameLevel* lev)
{
	Loading = true; //This can help us avoid loading activity while rendering
	currentLevel = lev;
	currentLevel->Load();
	Loading = false;
}

/*
Meathod		: SwitchLevel()
DESCRIPTION : the purose of this method is to setup the current level to faculitate switching of the levels of the game.
PARAMETERS  : none
RETURNS     : nothing
*/
void GameController::SwitchLevel(GameLevel* lev)
{
	Loading = true;
	currentLevel->Unload();
	lev->Load();
	delete currentLevel;
	currentLevel = lev;
	Loading = false;
}

/*
Meathod		: Render()
DESCRIPTION : the purose of this method is to call the render method of the level.
PARAMETERS  : none
RETURNS     : nothing
*/
void GameController::Render()
{
	//Do not update or render if the scene is loading.
	if (Loading) return;
	currentLevel->Render();
}

/*
Meathod		: Update()
DESCRIPTION : the purose of this method is to call the update method of the curretn level and 
pass the current position of x,y coordinates along with a status flag.
PARAMETERS  : double x, double y, bool MD
RETURNS     : nothing
*/
void GameController::Update(double x, double y, bool MD)
{
	//Do not update or render if the scene is loading.
	if (Loading) return; 
	currentLevel->Update(x,y,MD);
}