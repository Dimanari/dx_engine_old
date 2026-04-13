#pragma once
#include "Drawable.h"
class Button : public Drawable
{
protected:
	int x, y, width, height; bool Active;
	virtual void DrawSelection();
	virtual void DrawMe();
public:
	static void setGraphics(Graphics *_gfx) { gfx = _gfx; }
	virtual void update();
	RECT getArea();
	void Toggle();
	void SetActive(bool set) { Active = set; }
	virtual void Draw();
	Button(int _x, int _y,int _width,int _height);
	~Button();
};