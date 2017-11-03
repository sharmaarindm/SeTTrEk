/*
PROJECT NAME : SETTrek
FILE NAME	: Ship.cpp
DESCRIPTION : the purose of this file is to model a spaceship that are the main charaters of our game.
DATE : 2017-17-02
NAME OF THE PROGRAMMER : ARINDM SHARMA
*/

#include "Ship.h"

/*
Meathod		: Ship()
DESCRIPTION : the purose of this method is to act as the constructor of the Ship class
and to initialize the required variables for a player ship.
PARAMETERS  : none
RETURNS     : nothing
*/
Ship::Ship(wchar_t * Basefilename, wchar_t * Detailfilename, Graphics * gfx,float height,float width)
{
	setConstantSpeed(4);
	initial = true;
	shiptype = true;
	objHeight = height;
	objWidth = width;
	xPosition = 0;
	yPosition = (height * 10) / 2;
	finalX = xPosition;
	finalY = yPosition;
	xSpeed = 0;
	ySpeed = 0;
	setHealth(900);
	setBeginningXPosition(xPosition);
	setBeginningYPosition(yPosition);
	setScience(0);
	stay = false;
	this->gfx = gfx;
	spaceship = new SpriteSheet(Basefilename, gfx);
	spaceship2 = new SpriteSheet(Detailfilename, gfx);
	explosion = new SpriteSheet(L"explosion.bmp", gfx);
	sheild = new SpriteSheet(L"sheild.bmp", gfx);
	chromaspaceship = doChroma(spaceship, 0.2f,1);
	chromaspaceship2 = doChroma(spaceship2, 0.2f,1);

	chromaexplosion = doChroma(explosion, 0.2f, 1);
	explosion->bmp = convertImageToBitmap(chromaexplosion, explosion->bmp->GetPixelSize());
	chromasheild = doChroma(sheild, 0.2f, 1);
	sheild->bmp = convertImageToBitmap(chromasheild, explosion->bmp->GetPixelSize());
	//converting back to bitmap
	spaceship->bmp = convertImageToBitmap(chromaspaceship, spaceship->bmp->GetPixelSize());
	spaceship2->bmp = convertImageToBitmap(chromaspaceship2, spaceship2->bmp->GetPixelSize());

	//compositing to create the ship
	chromaspaceship = doComposite(spaceship, spaceship2);

	//converting the composite ship 
	spaceship->bmp = convertImageToBitmap(chromaspaceship, spaceship->bmp->GetPixelSize());

	//remove the excessive green from the inside of the ship
	chromaspaceship = doChroma(spaceship,0.6f,1);
	spaceship->bmp = convertImageToBitmap(chromaspaceship, spaceship->bmp->GetPixelSize());
}

/*
Meathod		: Ship()
DESCRIPTION : the purose of this method is to act as the constructor of the Ship class
and to initialize the required variables for an enemy ship.
PARAMETERS  : none
RETURNS     : nothing
*/
Ship::Ship(wchar_t * filename, Graphics * gfx,float height, float width)
{
	stay = false;
	setConstantSpeed(2);
	setHealth(900);
	shiptype = false;
	initial = true;
	this->gfx = gfx;
	objHeight = height;
	objWidth = width;
	xPosition = objWidth*9;
	yPosition = (height * 10) / 2;
	setBeginningXPosition(xPosition);
	setBeginningYPosition(yPosition);
	finalX = xPosition;
	finalY = yPosition;
	xSpeed = 0;
	ySpeed = 0;
	spaceship = new SpriteSheet(filename, gfx);
	chromaspaceship = doChroma(spaceship, 0.2f,2);
	//converting back to bitmap
	spaceship->bmp = convertImageToBitmap(chromaspaceship, spaceship->bmp->GetPixelSize());
}

/*
Meathod		: ~Ship()
DESCRIPTION : the purose of this method is to act as the destuctor for the ship object.
PARAMETERS  : none
RETURNS     : nothing
*/
Ship::~Ship()
{
	delete spaceship;
	delete spaceship2;
	delete explosion;
}

float Ship::getXSpeed()
{
	return xSpeed;
}

float Ship::getYSpeed()
{
	return ySpeed;
}

void Ship::setScience(float value)
{
	Science = value;
}

float Ship::getScience()
{
	return Science;
}

void Ship::setInitialBool(bool value)
{
	initial = value;
}

void Ship::setHealth(float value)
{
	health = value;
	if (health >= 900)
	{
		health = 900;
	}
}

float Ship::getHealth()
{
	return health;
}

void Ship::setXPosition(float value)
{
	xPosition = value;
}

float Ship::getXPosition()
{
	return xPosition;
}

void Ship::setYPosition(float value)
{
	yPosition = value;
}

float Ship::getYPosition()
{
	return yPosition;
}

void Ship::setFinalYPosition(float value)
{
	if (shiptype)
	{
		if (initial)
		{
			finalY = yPosition;
		}
		else
		{
			finalY = value - objHeight / 2;
		}
	}
	else
	{
		finalY = value;
	}


}

float Ship::getFinalYPosition()
{
	return finalY;
}

void Ship::setFinalXPosition(float value)
{
	if (shiptype)
	{
		if (initial)
		{
			finalX = xPosition;
		}
		else
		{
			finalX = value - objWidth / 2;
		}

	}
	else
	{
		finalX = value;
	}
}

float Ship::getFinalXPosition()
{
	return  finalX;
}

void Ship::setAngle(float value)
{
	angle = value;
}

float Ship::getAngle()
{
	return angle;
}

float Ship::getConstantSpeed()
{
	return ConstSpeed;
}

void Ship::setConstantSpeed(float value)
{
	ConstSpeed = value;
}

float Ship::getBeginningXPosition()
{
	return beginningXPosition;
}

void Ship::setBeginningXPosition(float value)
{
	beginningXPosition = value;
}

float Ship::getBeginningYPosition()
{
	return beginningYPosition;
}

void Ship::setBeginningYPosition(float value)
{
	beginningYPosition = value;
}

float Ship::getCentreX()
{
	return centreX;
}

float Ship::getCentreY()
{
	return centreY;
}

void Ship::setStay(bool value)
{
	stay = value;
}

/*
Meathod		: calculateSpeed()
DESCRIPTION : the purpose of this method is to calculate the increase in 
coordinate length for a given delta value.
PARAMETERS  : float finalval - final x/y coordinate
				float current - current x/y coordinate.
RETURNS     : float - the calulcated speed.
*/
float Ship::calculateSpeed(float finalval, float current)
{
	float speed;

    distance = calcD();//--------------------------------------------------------------------------------------------------------------

	float deltaValue = finalval - current;

	speed = (deltaValue*ConstSpeed) / distance;

	return speed;
}

/*
Meathod		: calcD()
DESCRIPTION : the purpose of this method is to calculate the distance between two given points.
PARAMETERS  : nothing
RETURNS     : float - the calulcated distance.
*/
float Ship::calcD()
{
	distance = sqrt(pow(finalX - xPosition, 2) + pow(finalY - yPosition, 2));	
	return distance;
}

/*
Meathod		: Draw()
DESCRIPTION : the purpose of this method is to draw the ship object.
PARAMETERS  : none
RETURNS     : nothing
*/
void Ship::Draw()
{	
	updateCenterPoints();

	if ((abs(finalX - xPosition) <= ConstSpeed/2 && abs(finalY - yPosition) <= ConstSpeed/2) )
	{
		if (initial)
		{
			this->gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(centreX, centreY)));
		}
		else
		{
			if (shiptype)
			{
				this->gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(centreX, centreY)));
			}
			else
			{
				this->gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Rotation(180 + angle, D2D1::Point2F(centreX, centreY)));
			}
		}

		spaceship->Draw(xPosition, yPosition, objWidth, objHeight);
		this->gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	}
	else
	{
		
		if (shiptype)
		{
			this->gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Rotation(rotate(), D2D1::Point2F(centreX, centreY)));
		}
		else
		{
			this->gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Rotation(180+rotate(), D2D1::Point2F(centreX, centreY)));
		}

		if (!stay) {
			xSpeed = calculateSpeed(finalX, xPosition);
			ySpeed = calculateSpeed(finalY, yPosition);
			xPosition = xPosition + xSpeed;
			yPosition = yPosition + ySpeed;
			initial = false;
		}

		spaceship->Draw(xPosition + xSpeed, yPosition + ySpeed, objWidth, objHeight);
		this->gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	}
	
}

/*
Meathod		: rotate()
DESCRIPTION : the purpose of this method is to calculate the angle of rotation, 
using the current and destination points.
PARAMETERS  : none
RETURNS     : float - the angle to rotate at.
*/
float Ship::rotate()
{
	float differenceX;
	float differenceY;
		
	differenceX = this->getFinalXPosition() - this->getXPosition();
	differenceY = this->getFinalYPosition() - this->getYPosition();

	angle = 90 - atan2(differenceX, differenceY) * 180 / PI;//the angle to rotate at.

	return angle;
}

/*
Meathod		: updateCenterPoints()
DESCRIPTION : the purpose of this method is to update the centre points for the ship
PARAMETERS  : none
RETURNS     : nothing
*/
void Ship::updateCenterPoints()
{
	centreX= xPosition + objWidth / 2;
	centreY= yPosition + objHeight / 2;
}

/*
Meathod		: resetShip()
DESCRIPTION : the purpose of this method is to reset the ship location to default and default set all the variables.
PARAMETERS  : none
RETURNS     : nothing
*/
void Ship::resetShip()
{
	//reset the whole system
	if (shiptype) // if its the player ship
	{
		setConstantSpeed(4);
		initial = true;
		shiptype = true;
		xPosition = 0;
		yPosition = (objHeight * 10) / 2;
		finalX = xPosition;
		finalY = yPosition;
		xSpeed = 0;
		ySpeed = 0;
		setHealth(getHealth());
		setBeginningXPosition(xPosition);
		setBeginningYPosition(yPosition);
		angle = 0;
		stay = false;
	}
	else //if its the enemy ship
	{
		setConstantSpeed(2);
		setHealth(900);
		shiptype = false;
		initial = true;
		this->gfx = gfx;
		xPosition = objWidth * 9;
		yPosition = (objHeight * 10) / 2;
		setBeginningXPosition(xPosition);
		setBeginningYPosition(yPosition);
		finalX = xPosition;
		finalY = yPosition;
		xSpeed = 0;
		ySpeed = 0;
		angle = 0;
		stay = false;
	}
}

void Ship::changeShips(wchar_t * Basefilename, wchar_t * Detailfilename)
{
	
	SpriteSheet* temp = new SpriteSheet(Basefilename, gfx);
	SpriteSheet* temp2 = new SpriteSheet(Detailfilename, gfx);
	chromaspaceship = doChroma(temp, 0.2f, 1);
	chromaspaceship2 = doChroma(temp2, 0.2f, 1);

	//converting back to bitmap
	temp->bmp = convertImageToBitmap(chromaspaceship, temp->bmp->GetPixelSize());
	temp2->bmp = convertImageToBitmap(chromaspaceship2, temp2->bmp->GetPixelSize());

	//compositing to create the ship
	chromaspaceship = doComposite(temp, temp2);

	//converting the composite ship 
	//temp->bmp = convertImageToBitmap(tempchromaspaceship, temp->bmp->GetPixelSize());
	spaceship->bmp = convertImageToBitmap(chromaspaceship, spaceship->bmp->GetPixelSize());

	//remove the excessive green from the inside of the ship
	chromaspaceship = doChroma(spaceship, 0.6f, 1);
	spaceship->bmp = convertImageToBitmap(chromaspaceship, spaceship->bmp->GetPixelSize());

	delete temp;
	delete temp2;
}

void Ship::explode()
{
	updateCenterPoints();
	explosion->Draw(xPosition + xSpeed, yPosition + ySpeed, objWidth, objHeight);

}

void Ship::DrawSheild()
{
	if ((abs(finalX - xPosition) <= ConstSpeed / 2 && abs(finalY - yPosition) <= ConstSpeed / 2))
	{
		if (initial)
		{
			this->gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(centreX, centreY)));
		}
		else
		{
			if (shiptype)
			{
				this->gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(centreX, centreY)));
			}
			else
			{
				this->gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Rotation(180 + angle, D2D1::Point2F(centreX, centreY)));
			}
		}

		sheild->Draw(xPosition, yPosition, objWidth, objHeight);
		this->gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	}
	else
	{

		if (shiptype)
		{
			this->gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Rotation(rotate(), D2D1::Point2F(centreX, centreY)));
		}
		else
		{
			this->gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Rotation(180 + rotate(), D2D1::Point2F(centreX, centreY)));
		}

		if (!stay) {
			xSpeed = calculateSpeed(finalX, xPosition);
			ySpeed = calculateSpeed(finalY, yPosition);
			initial = false;
		}

		sheild->Draw(xPosition + xSpeed, yPosition + ySpeed, objWidth, objHeight);
		this->gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	}


}


/*
Meathod		: doChroma()
DESCRIPTION : the purose of this method is to perform chromakey effect on the bitmap of
the provided spritesheet.
PARAMETERS  : SpriteSheet * ptr - pointer to the spritesheet
float tolerance - custom tolerancce value.
RETURNS     : ID2D1Effect* - containing the resultant effect.
*/
ID2D1Effect * Ship::doChroma(SpriteSheet * ptr, float tolerance, int whichOne)
{
	ID2D1Effect *chromakeyEffect; //creating a ID2D1Effect* (which will hold the resultant image)

	gfx->GetRenderTarget()->CreateEffect(CLSID_D2D1ChromaKey, &chromakeyEffect); // setup the type of effect

	chromakeyEffect->SetInput(0, ptr->bmp); //the bmp on which the effect is being performed.
	if (whichOne == 1)
	{
		chromakeyEffect->SetValue(D2D1_CHROMAKEY_PROP_COLOR, D2D1::Vector3F(0.0f, 1.0f, 0.0f)); // remove the green value.
	}
	else if (whichOne == 2)
	{
		chromakeyEffect->SetValue(D2D1_CHROMAKEY_PROP_COLOR, D2D1::Vector3F(0.0f, 0.0f, 1.0f)); // remove the blue value.
	}

	chromakeyEffect->SetValue(D2D1_CHROMAKEY_PROP_TOLERANCE, tolerance); // tolerance value
	chromakeyEffect->SetValue(D2D1_CHROMAKEY_PROP_INVERT_ALPHA, 0);// alpha value
	chromakeyEffect->SetValue(D2D1_CHROMAKEY_PROP_FEATHER, 0);//whether the edges need to softened or not.
	return chromakeyEffect; // return the effect back
}

/*
Meathod		: doComposite()
DESCRIPTION : the purose of this method is to perform composite effect on the two bitmaps of
the provided spritesheets.
PARAMETERS  : SpriteSheet * image1 - pointer to the 1st spritesheet
SpriteSheet * image2 - pointer to the 2nd spritesheet
RETURNS     : ID2D1Effect* - containing the resultant effect.
*/
ID2D1Effect * Ship::doComposite(SpriteSheet * image1, SpriteSheet * image2)
{

	ID2D1Effect* compositeEffect;//creating a ID2D1Effect* (which will hold the resultant image)

	this->gfx->GetRenderTarget()->CreateEffect(CLSID_D2D1Composite, &compositeEffect); // setup the type of effect

	compositeEffect->SetInput(0, image1->bmp); // bitmap one.
	compositeEffect->SetInput(1, image2->bmp); // bitmap two

	return compositeEffect; // return the effect back
}

/*
Meathod		: convertImageToBitmap()
DESCRIPTION : the purose of this method is to convert ID2D1Effect* into ID2D1Bitmap*
PARAMETERS  : ID2D1Effect* pImg - the effect we wish to convert
D2D1_SIZE_U size -  the size to the ID2D1Bitmap*
RETURNS     : ID2D1Bitmap* - containing the resultant bitmap.
Reference : http://stackoverflow.com/questions/31118397/direct2d-convert-id2d1image-to-id2d1bitmap
*/
ID2D1Bitmap * Ship::convertImageToBitmap(ID2D1Effect * pImg, D2D1_SIZE_U size)
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