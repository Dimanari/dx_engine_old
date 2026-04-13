#include "Controller.h"
Level* Controller::CurrentLevel;
bool Controller::Loading = false;
void Controller::LoadInitialLevel(Level * Lv)
{
	Loading = true;
	CurrentLevel = Lv;
	CurrentLevel->Load();
	Loading = false;
}

void Controller::SwitchLevel(Level * Lv)
{
	Loading = true;
	CurrentLevel->Unload();
	delete CurrentLevel;
	CurrentLevel = Lv;
	CurrentLevel->Load();
	Loading = false;
}
void SwitchLevel(Level * Lv)
{
	Controller::SwitchLevel(Lv);
}
void Controller::Render()
{
	if (!Loading)
		CurrentLevel->Render();
}

void Controller::Update(long ms)
{
	if (!Loading)
		CurrentLevel->Update(ms);
}

void Controller::Mouse(int m_Event, int x, int y)
{
	if (!Loading)
		CurrentLevel->Mouse(m_Event, x, y);
}

void Controller::Keyboard(int m_Event, WPARAM wParam)
{
	if (!Loading)
		CurrentLevel->Keyboard(m_Event, wParam);
}

void Controller::ShutDown()
{
	Loading = true;
	CurrentLevel->Unload();
	delete CurrentLevel;
}
