#include "Button_Sprite.h"

void Button_S::DrawMe()
{
	Image->Draw(x, y, frame);
}

Button_S::Button_S(Sprite * _Image, int _x, int _y, int _numOfFrames)
	:Button(_x,_y,_Image->getWidth(), _Image->getHeight())
{
	Image = _Image;
	maxSprite = _numOfFrames;
	frame = 0;
}

Button_S::~Button_S()
{
	delete Image;
}

void Button_S::update()
{
	if (Active)
	{
		frame++;
		frame %= maxSprite;
	}
	else
		frame = 0;
}