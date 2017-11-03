/*
PROJECT NAME : SETTrek
FILE NAME	: SpriteSheet.h
DESCRIPTION : The concept behind this class is that it will be passed
a filename and graphics object/rendertarget, then, will
proceed to create the needed WIC components to read, 
decode, and then encode the bitmap file from disk into
a compatible D2D bitmap. 
DATE : 2017-17-02
NAME OF THE PROGRAMMER : ARINDM SHARMA
*/

#include "SpriteSheet.h"

/*
Meathod		: SpriteSheet()
DESCRIPTION : the purose of this method is to act as the constructor of the SpriteSheet class
and setup the spritesheet for a given bmp file.
PARAMETERS  : none
RETURNS     : nothing
*/
SpriteSheet::SpriteSheet(wchar_t* filename, Graphics* gfx)
{
	this->gfx = gfx; //save the gfx parameter for later
	bmp = NULL; //This needs to be NULL to start off
	HRESULT hr;

	//creating the wic Factory
	IWICImagingFactory2 *wicFactory = NULL;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicFactory); // pointer to wic factory.

	//creating decoder to read file into wic bmp.
	IWICBitmapDecoder *wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
		filename, //name of the file
		NULL,
		GENERIC_READ, // read from the file.
		WICDecodeMetadataCacheOnLoad,
		&wicDecoder); //pointer to the wic decoder

	//moving the image into the frame
	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame); //since we only have one fram using 0.


	//change wicbitmap to D2D bitmap
	//creating the wic converter
	IWICFormatConverter *wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);

	//configuring the converter
	hr = wicConverter->Initialize(
		wicFrame, //the wic frame that we made using the image
		GUID_WICPixelFormat32bppPBGRA, //Pixelformat
		WICBitmapDitherTypeNone,
		NULL,
		0.0, //value of Alpha Transparency.
		WICBitmapPaletteTypeCustom
	);

	//creating the D2Dbmp
	gfx->GetRenderTarget()->CreateBitmapFromWicBitmap(
		wicConverter, //the wic converter we instantiated
		NULL, //can specify proterties
		&bmp //destination bmp.
	);

	//relesing the local objects. ( if exists release).
	if (wicFactory)
	{
		wicFactory->Release();
	}
	if (wicDecoder)
	{
		wicDecoder->Release();
	}
	if (wicConverter)
	{
		wicConverter->Release();
	}
	if (wicFrame) 
	{
		wicFrame->Release();
	}
}

SpriteSheet::~SpriteSheet()
{
	//releasing the bmp pointer.
	if (bmp)
	{
		bmp->Release();
	}
}


/*
Meathod		: Draw()
DESCRIPTION : the purose of this method is to draw the provied ID2D1Bitmap object
			  object as background image.
PARAMETERS  : none
RETURNS     : nothing
Reference	: Foubert, R. et al. (2017) "DX_WICFiles", Graphics, Animation, and Sound (PROG2215). eConestoga Example. 
*/
void SpriteSheet::Draw()
{
	gfx->GetRenderTarget()->DrawBitmap(
		bmp, //bitmap created from wic
		D2D1::RectF(0.0f, 0.0f,
			bmp->GetSize().width, bmp->GetSize().height), //destination rec
		0.8f, //alpha value
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,// interpolation mode used
		D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height) //rectangle to draw.
		);
}

/*
Meathod		: Draw()
DESCRIPTION : the purose of this method is to draw the provied ID2D1Bitmap object
			  on the graphics object provided the required start pt and the width/height.
PARAMETERS  : none
RETURNS     : nothing
*/
void SpriteSheet::Draw(float startX, float startY,float Width, float Height)
{
	gfx->GetRenderTarget()->DrawBitmap(
		bmp, //bitmap created from wic
		D2D1::RectF(startX, startY, Width + startX, Height + startY), //destination rec
		1.0f, //Opacity or Alpha
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,// interpolation mode used
		D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height) //rectangle to draw.
	);
}
