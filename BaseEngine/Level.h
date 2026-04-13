#pragma once
#include "Graphics.h"
#include "Sprite.h"
class Level
{
protected:
	static POINT Cursor;
	static Graphics* gfx;
	static bool inRegion(POINT pos, RECT area);
public:
	static void Init(Graphics* _graphics)
	{
		gfx = _graphics;
	}
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(long ms) = 0;
	virtual void Render() = 0;
	virtual void Mouse(int m_Event, int x, int y) = 0;
	virtual void Keyboard(int m_Event, WPARAM wParam) = 0;
};
enum {M_MOVE, M_LBDOWN, M_RBDOWN
	, M_LBUP, M_RBUP
};
void Quit();
void SwitchLevel(Level* Lv);