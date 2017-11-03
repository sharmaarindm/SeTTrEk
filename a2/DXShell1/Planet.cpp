/*
PROJECT NAME : SETTrek
FILE NAME	: Planet.h
DESCRIPTION : the purose of this file is to model a Planet object that constitute of the background of the game.
DATE : 2017-17-02
NAME OF THE PROGRAMMER : ARINDM SHARMA
*/

#include "Planet.h"

/*
Meathod		: Planet()
DESCRIPTION : the purose of this method is to act as the constructor of the Planet class
and to initialize the required variables.
PARAMETERS  : none
RETURNS     : nothing
*/
Planet::Planet(wchar_t * filename, Graphics * gfx, float height, float width,float tolerance)
{
	this->gfx = gfx;
	PlanetSprite = new SpriteSheet(filename, gfx);
	//all of them chromkeyed
	chromaPlanet = doChroma(PlanetSprite, tolerance);
	//converiting the chromakeyed planets back to bitmaps.
	PlanetSprite->bmp = convertImageToBitmap(chromaPlanet, PlanetSprite->bmp->GetPixelSize());
}

/*
Meathod		: ~Planet()
DESCRIPTION : the purose of this method is to act as the destructor for the Planet class.
PARAMETERS  : none
RETURNS     : nothing
*/
Planet::~Planet()
{
	delete PlanetSprite;
}

void Planet::setXPosition(float value)
{
	xPosition = value;
}

float Planet::getXPosition()
{
	return xPosition;
}

void Planet::setYPosition(float value)
{
	yPosition = value;
}

float Planet::getYPosition()
{
	return yPosition;
}

/*
Meathod		: Draw()
DESCRIPTION : the purose of this method is to draw the planets at given coordinates.
PARAMETERS  : float startX, float startY, float Width, float Height
RETURNS     : nothing
*/
void Planet::Draw(float startX, float startY, float Width, float Height)
{
	PlanetSprite->Draw(startX, startY, Width, Height);
}

/*
Meathod		: doChroma()
DESCRIPTION : the purose of this method is to perform chromakey effect on the bitmap of
the provided spritesheet.
PARAMETERS  : SpriteSheet * ptr - pointer to the spritesheet
float tolerance - custom tolerancce value.
RETURNS     : ID2D1Effect* - containing the resultant effect.
*/
ID2D1Effect * Planet::doChroma(SpriteSheet * ptr, float tolerance)
{
	ID2D1Effect *chromakeyEffect; //creating a ID2D1Effect* (which will hold the resultant image)

	gfx->GetRenderTarget()->CreateEffect(CLSID_D2D1ChromaKey, &chromakeyEffect); // setup the type of effect

	chromakeyEffect->SetInput(0, ptr->bmp); //the bmp on which the effect is being performed.
	chromakeyEffect->SetValue(D2D1_CHROMAKEY_PROP_COLOR, D2D1::Vector3F(0.0f, 1.0f, 0.0f)); // remove the green value.
	chromakeyEffect->SetValue(D2D1_CHROMAKEY_PROP_TOLERANCE, tolerance); // tolerance value
	chromakeyEffect->SetValue(D2D1_CHROMAKEY_PROP_INVERT_ALPHA, 0);// alpha value
	chromakeyEffect->SetValue(D2D1_CHROMAKEY_PROP_FEATHER, 0);//whether the edges need to softened or not.
	return chromakeyEffect; // return the effect back
}

/*
Meathod		: convertImageToBitmap()
DESCRIPTION : the purose of this method is to convert ID2D1Effect* into ID2D1Bitmap*
PARAMETERS  : ID2D1Effect* pImg - the effect we wish to convert
D2D1_SIZE_U size -  the size to the ID2D1Bitmap*
RETURNS     : ID2D1Bitmap* - containing the resultant bitmap.
Reference : http://stackoverflow.com/questions/31118397/direct2d-convert-id2d1image-to-id2d1bitmap
*/
ID2D1Bitmap * Planet::convertImageToBitmap(ID2D1Effect * pImg, D2D1_SIZE_U size)
{
	ID2D1Image* oldTarget = NULL;
	ID2D1Bitmap1* targetBitmap = NULL;

	//Create a Bitmap with "D2D1_BITMAP_OPTIONS_TARGET"
	D2D1_BITMAP_PROPERTIES1 bitmapProperties =
		D2D1::BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)
		);
	gfx->GetRenderTarget()->CreateBitmap(size, 0, 0, bitmapProperties, &targetBitmap);

	//Save current Target, replace by ID2D1Bitmap
	gfx->GetRenderTarget()->GetTarget(&oldTarget);
	gfx->GetRenderTarget()->SetTarget(targetBitmap);

	gfx->BeginDraw();
	//Draw Image on Target (if currently not drawing also call Begin/EndDraw)
	gfx->GetRenderTarget()->DrawImage(pImg);

	gfx->EndDraw();
	//Set previous Target
	gfx->GetRenderTarget()->SetTarget(oldTarget);

	oldTarget->Release();

	return targetBitmap;
}
