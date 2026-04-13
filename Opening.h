#pragma once

#include "BaseEngine\Level.h"
#include "BaseEngine\Button.h"

class OpeningScreen : public Level
{
	int time;
	Button *Exit, *Play, *Easy, *Hard;
public:
	virtual void Load();
	virtual void Unload();
	virtual void Update(long ms);
	virtual void Render();
	virtual void Mouse(int m_Event, int x, int y);
	virtual void Keyboard(int m_Event, WPARAM wParam);
};