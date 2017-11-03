#include "face.h"

face::face(wchar_t * Basefilename, Graphics * gfx, float height, float width,float speed)
{
	objHeight = height;
	objWidth = width;
	xPosition = 0;
	yPosition = (height * 10) / 2;
	beginningXPosition = xPosition;
	beginningYPosition = yPosition;
	this->gfx = gfx;
	headshot = new SpriteSheet(Basefilename, gfx);
	chromaface = doChroma(headshot, 0.2f, 1);

	
	headshot->bmp = convertImageToBitmap(chromaface, headshot->bmp->GetPixelSize());
	
	setconstantspeed(speed);

	tempwidth = objWidth;
	tempheight = objHeight;
	
}

face::~face()
{
	delete headshot;
	delete chromaface;
}

ID2D1Effect * face::doChroma(SpriteSheet * ptr, float tolerance, int whichOne)
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

ID2D1Bitmap * face::convertImageToBitmap(ID2D1Effect * pImg, D2D1_SIZE_U size)
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

void face::Draw()
{
	//updateCenterPoints();
	if ((abs(finalX - xPosition) <= ConstSpeed / 2) && (abs(finalY - yPosition) <= ConstSpeed / 2))
	{
		
		drawStill();
	}
	else
	{
		drawWithRotation();
	}
		
	
}

float face::getXPosition()
{
	return xPosition;
}

float face::getYPosition()
{
	return yPosition;
}

void face::setXPosition(float value)
{
	xPosition = value;
}

void face::setYPosition(float value)
{
	yPosition = value;
}

float face::getfinalXPosition()
{
	return finalX;
}

float face::getfinalYPosition()
{
	return finalY;
}

void face::setfinalXPosition(float value)
{
	finalX = value;
}

void face::setfinalYPosition(float value)
{
	finalY = value;
}

float face::getconstantspeed()
{
	return ConstSpeed;
}

void face::setconstantspeed(float value)
{
	ConstSpeed = value;
}

int face::getwhichrotation()
{
	return whichrotation;
}

void face::setwhichrotation(int value)
{
	whichrotation = value;
}

float face::getCentreX()
{
	return centreX;
}

float face::getCentreY()
{
	return centreY;
}

float face::getWidth()
{
	return objWidth;
}

float face::getHeight()
{
	return objHeight;
}

float face::calculateSpeed(float finalval, float current)
{
	float speed;

	distance = sqrt(pow(finalX - xPosition, 2) + pow(finalY - yPosition, 2));

	float deltaValue = finalval - current;

	speed = (deltaValue*ConstSpeed) / distance;

	return speed;
}

void face::updateCenterPoints()
{
	centreX = xPosition + objWidth / 2;
	centreY = yPosition + objHeight / 2;
}

void face::calculateSpeedandDraw()
{
	xSpeed = calculateSpeed(finalX, xPosition);
	ySpeed = calculateSpeed(finalY, yPosition);
	xPosition = xPosition + xSpeed;
	yPosition = yPosition + ySpeed;

	headshot->Draw(xPosition + xSpeed, yPosition + ySpeed, objWidth, objHeight);
}

void face::scaleUpDown(int updown)
{
	//scale up
	if (updown == 2)
	{
		if (((tempwidth + (tempwidth*0.9)) == (objWidth + (objWidth * 0.3))) || ((tempheight + (tempheight*0.9)) == (objHeight + (objHeight * 0.3))))
		{
			//do nothing;
		}
		else
		{
			objWidth = objWidth + (objWidth * 0.3);
			objHeight = objHeight + (objHeight*0.3);
		}

	}
	else if (updown == 1) //scale down
	{
		if (((tempwidth - (tempwidth*0.9)) == (objWidth - (objWidth * 0.3))) || ((tempheight - (tempheight*0.9)) == (objHeight - (objHeight * 0.3))))
		{
			//do nothing
		}
		else
		{
			objWidth = objWidth - (objWidth * 0.3);
			objHeight = objHeight - (objHeight * 0.3);
		}

	}
}

void face::drawWithRotation()
{
	if (whichrotation == 1)
	{
		calculateSpeedandDraw();
	}
	else if (whichrotation == 2)
	{
		updateCenterPoints();
		this->gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Rotation(-90, D2D1::Point2F(centreX, centreY)));
		calculateSpeedandDraw();
		this->gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	}
	else if (whichrotation == 3)
	{
		updateCenterPoints();
		this->gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Rotation(90, D2D1::Point2F(centreX, centreY)));
		calculateSpeedandDraw();
		this->gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	}
}

void face::drawStill()
{
	if (whichrotation == 1)
	{
		headshot->Draw(xPosition, yPosition, objWidth, objHeight);
	}
	else if (whichrotation == 2)
	{
		updateCenterPoints();
		this->gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Rotation(-90, D2D1::Point2F(centreX, centreY)));
		headshot->Draw(xPosition, yPosition, objWidth, objHeight);
		this->gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	}
	else if (whichrotation == 3)
	{
		updateCenterPoints();
		this->gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Rotation(90, D2D1::Point2F(centreX, centreY)));
		headshot->Draw(xPosition, yPosition, objWidth, objHeight);
		this->gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	}
}
