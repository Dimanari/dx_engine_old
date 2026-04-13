#include "Button_Text.h"

float _min(float x, float y)
{
	return (x > y) ? (y) : (x);
}


void Button_T::DrawMe()
{
	gfx->FillRect(x, y, width, height, 0.2f, 0.6f, 0.5f);
	gfx->DrawString(x, y, width, height, text //to include Null
		, _min( (float)height , 2.5*width/ ((float)lenght)),true,0,0,0);
}

Button_T::Button_T(WCHAR* _text, int _x, int _y, int _width, int _height)
	:Button(_x,_y, _width, _height)
{
	text = _text;
	lenght = stringlenght(_text);
}

Button_T::~Button_T()
{
	delete text;
}
