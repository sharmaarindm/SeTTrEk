/*
PROJECT NAME : SETTrek
FILE NAME	: Graphics.h
DESCRIPTION : The intent of the Graphics class is to handle our DirectX calls, and to be largely responsible
for managing the rendertarget.
DATE : 2017-17-02
NAME OF THE PROGRAMMER : ARINDM SHARMA
*/

#pragma once
#include <Windows.h>
#include <d2d1_1.h>
#include <d2d1_1helper.h>
#include <d3d11_1.h>
#include <d2d1effecthelpers.h>
#include <d2d1effects_2.h>
#include <dwrite_1.h>

/*
Name : Ship
Purpose : this class acts as the model for a Graphics object.
*/
class Graphics
{
	//Below, these are all COM interfaces we're using to create D2D resources.
	//We release them as part of the ~Graphics deconstructor... or bad things can happen
	ID2D1Factory1* factory; //The factory allows us to create many other types of D2D resources
	ID2D1DeviceContext* rendertarget; //this is typically an area in our GPU memory.. like a back buffer for 2d

	// Direct3D device
	ID3D11Device1 *Direct3DDevice;

	// Direct3D device context
	ID3D11DeviceContext1 *Direct3DContext;

	// Direct2D device
	ID2D1Device *Direct2DDevice;

	// DXGI swap chain
	IDXGISwapChain1 *DXGISwapChain;

	// Direct2D target rendering bitmap
	// (linked to DXGI back buffer which is linked to Direct3D pipeline)
	ID2D1Bitmap1 *Direct2DBackBuffer;

	IDWriteFactory1* m_pDWriteFactory;

public:
	Graphics();

	~Graphics();

	bool Init(HWND windowHandle);

	ID2D1DeviceContext* GetRenderTarget()
	{
		return rendertarget;
	}

	IDWriteFactory1* GetWriteFactory()
	{
		return m_pDWriteFactory;
	}


	void BeginDraw() { rendertarget->BeginDraw(); }
	void EndDraw() { rendertarget->EndDraw(); }

	void ClearScreen(float r, float g, float b);

	IDXGISwapChain1*  GetSwapChain();
	// Hrmmm... r, g, b, a? Where do we know these from?
};