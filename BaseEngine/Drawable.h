#pragma once
#include "Graphics.h"
class Drawable
{
protected:
	static Graphics *gfx;
public:
	static void setGraphics(Graphics *_gfx) { gfx = _gfx; }
};