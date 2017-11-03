/*
PROJECT NAME : SET-JAB
FILE NAME	: main.cpp
DESCRIPTION : the purose of this file is to act as the main for our SET-JAB game.
DATE : 2017-04-20
NAME OF THE PROGRAMMER : ARINDM SHARMA and ZIVOJIN PECIN
*/
#include <Windows.h>
#include "Graphics.h"
#include "Level1.h"
#include "GameController.h"
#include <windowsx.h>
#include "sound.h"
#include <thread> 

//global variables.
Graphics* graphics;
//tracks mouse position for clicks
int xPos; 
int yPos;
bool mouseDown;

//callback procedure for trigerring the events
LRESULT CALLBACK WindowProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam )
{
	if (uMsg == WM_DESTROY) 
	{ 
		PostQuitMessage(0); return 0; 
	}
	
//if the left click is done.
	if (uMsg == WM_LBUTTONDOWN)
	{
		//get the current x and y coordinates.
		xPos = GET_X_LPARAM(lParam);
		yPos = GET_Y_LPARAM(lParam);
		mouseDown = true;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// window main to be able to work with a window
int WINAPI wWinMain(HINSTANCE hInstance,HINSTANCE prevInstance,LPWSTR cmd,int nCmdShow)
{

	// to generate a window
	WNDCLASSEX windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
	windowclass.hCursor = LoadCursor(NULL, IDC_CROSS); //cursor type
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW; //background color for the window
	windowclass.hInstance = hInstance; //current instance
	windowclass.lpfnWndProc = WindowProc;
	windowclass.lpszClassName = "MainWindow"; // name of window
	windowclass.style = CS_HREDRAW | CS_VREDRAW; // syte of window 

	//register the window
	RegisterClassEx(&windowclass);

	RECT rect = { 0, 0, 1024, 768 };//the initial size of the window required.
	AdjustWindowRectEx(&rect, WS_CAPTION|WS_MAXIMIZEBOX|WS_MINIMIZEBOX|WS_SYSMENU|WS_SIZEBOX, false, NULL);

	//creating the window with the name "SET-JAB", size of the rectangle specified above starting at 100,100 from the top left of the screen.
	HWND windowhandle = CreateWindowEx(NULL, "MainWindow", "SET-JAB", WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU | WS_SIZEBOX,
		100, 100, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);
	if (!windowhandle)
	{
		return -1;
	}

	// instatiating the graphics class.
	graphics = new Graphics();
	if (!graphics->Init(windowhandle))
	{
		delete graphics;
		return -1;
	}

	GameLevel::Init(graphics);
	ShowWindow(windowhandle, nCmdShow); //show the window
	GameController::LoadInitialLevel(new Level1());
#pragma region GameLoop


	//startup game loop
	MSG message;
	message.message = WM_NULL; //message initiallization.
	while (message.message != WM_QUIT) //if quit message is received
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			//send message to the window proc if there is one.
			DispatchMessage(&message);
			
		}
		else
		{
			//call the update method
			GameController::Update(xPos,yPos,mouseDown);
			if (mouseDown) 
			{ 
				mouseDown = false; 
			}

			//triger the render method to start drawing.
			graphics->BeginDraw();
			GameController::Render();
			graphics->EndDraw();

			DXGI_PRESENT_PARAMETERS parameters = { 0 };
			parameters.DirtyRectsCount = 0;
			parameters.pDirtyRects = nullptr;
			parameters.pScrollRect = nullptr;
			parameters.pScrollOffset = nullptr;

			HRESULT hr = graphics->GetSwapChain()->Present1(1, 0, &parameters);
		}
	}


#pragma endregion
	//cleanup
	delete graphics;
	return 0;
}