#include "Button.h"
void Button::DrawSelection()
{
	for (int size = 2; size > -3; size--)
		gfx->DrawRect(x - size, y - size, width + 2 * size, height + 2 * size, 0.1, 0.5, 0.9);
}
void Button::DrawMe()
{
	gfx->DrawRect(x, y, width, height, 0.2f, 0.6f, 0.5f);
}
void Button::update()
{
	if (Active)
	{
		;
	}
	else
		;
}

RECT Button::getArea()
{
	return{ x,y,x+ width,y+ height };
}

void Button::Toggle()
{
}

void Button::Draw()
{
	//Image->Draw(x, y, frame);
	
	this->DrawMe();
	if(Active)
		DrawSelection();
}

Button::Button(int _x, int _y, int _width, int _height)
{
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	Active = false;
}

Button::~Button()
{
}
