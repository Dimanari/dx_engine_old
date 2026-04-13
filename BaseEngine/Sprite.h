#pragma once

#include <wincodec.h>
#include "Drawable.h"

class Sprite : public Drawable
{
protected:
	ID2D1Bitmap* bmp;
	int width, height;
	int across;
public:
	static void graphicsCall(Graphics* _gfx)
	{
		if (gfx)
			return;
		gfx = _gfx;
	}
	Sprite(wchar_t* filename);
	Sprite(wchar_t* filename,int SpriteWidth,int SpriteHeight);
	~Sprite();
	const int getWidth() { return width; }
	const int getHeight() { return height; }
	void Draw();
	void Draw(int x,int y,int frame);
};