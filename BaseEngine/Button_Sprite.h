#pragma once
#include "Button.h"
#include "Sprite.h"
class Button_S : public Button
{
	Sprite* Image; 
	int maxSprite; int frame;
	virtual void DrawMe();
public:
	virtual void update();
	Button_S(Sprite* _Image, int _x, int _y, int _numOfFrames = 1);
	~Button_S();
};