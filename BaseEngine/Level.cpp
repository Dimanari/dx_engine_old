#include "Level.h"

Graphics* Level::gfx;
POINT Level::Cursor = { 0,0 };
bool Level::inRegion(POINT pos, RECT area)
{
	if ((pos.x >= area.left) && (pos.x <= area.right) && (pos.y >= area.top) && (pos.y <= area.bottom))
		return true;
	return false;
}