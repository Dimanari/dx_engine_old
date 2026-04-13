#pragma once
#include "Button.h"
class Button_T : public Button
{
	WCHAR* text;
	int lenght;
	virtual void DrawMe();
public:
	Button_T(WCHAR* text, int _x, int _y,int _width,int _height);
	~Button_T();
};