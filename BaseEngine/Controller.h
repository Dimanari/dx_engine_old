#pragma once

#include "Level.h"

class Controller
{
	Controller();
	static Level* CurrentLevel;
	static bool Loading;
public:
	static void LoadInitialLevel(Level *Lv);
	static void SwitchLevel(Level *Lv);
	static void Render();
	static void Update(long ms);
	static void Mouse(int m_Event, int x, int y);
	static void Keyboard(int m_Event, WPARAM wParam);
	static void ShutDown();
};