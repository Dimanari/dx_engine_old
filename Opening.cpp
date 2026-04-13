#include "Opening.h"
#include "BaseEngine\Controller.h"
#include "BaseEngine\Button_Text.h"
//#include "MazeLevel.h"
void OpeningScreen::Load()
{
	Exit = new Button_T(L"ExitButton", 50, 50, 120, 50);
	Play = new Button_T(L"Play Normal", 325, 400, 150, 50);
	Easy = new Button_T(L"Play Easy", 125, 400, 150, 50);
	Hard = new Button_T(L"Play Hard", 525, 400, 150, 50);
	time = 0;
}

void OpeningScreen::Unload()
{
	delete Exit;
	delete Play;
	delete Easy;
	delete Hard;
}

void OpeningScreen::Update(long ms)
{
	static int interval = (700 / 25);
	time += ms;
	while (time > interval)
	{
		time -= interval;
		Exit->update();
		Play->update();
		Easy->update();
		Hard->update();
	}

	Exit->SetActive(inRegion(Cursor, Exit->getArea()));
	Play->SetActive(inRegion(Cursor, Play->getArea()));
	Easy->SetActive(inRegion(Cursor, Easy->getArea()));
	Hard->SetActive(inRegion(Cursor, Hard->getArea()));
}

void OpeningScreen::Render()
{
	//make screen
	gfx->ClearScreen(0, 0, 0);
	//Draw Objects
	gfx->DrawRect(100, 100, 600, 400, 0.4, 0.7, 0.7);
	Exit->Draw();
	Play->Draw();
	Hard->Draw();
	Easy->Draw();
	gfx->DrawString(100, 100, 200, 50, L"שלום עולם", 24.0, false, 0.8, 0.3, 0.7);
	//Draw Cursor
	gfx->DrawCircle(Cursor.x, Cursor.y, 3.0, 1, 1, 1);
	gfx->DrawCircle(Cursor.x, Cursor.y, 5.0, 1, 1, 1);
}
void OpeningScreen::Mouse(int m_Event, int x, int y)
{
	switch (m_Event)
	{
	case M_MOVE:// M_LBDOWN, M_RBDOWN
				//, M_LBUP, M_RBUP:
		Cursor.x = x;
		Cursor.y = y;
		break;
	case M_LBDOWN:
		if (inRegion(Cursor, Exit->getArea()))
			Quit();
		else if (inRegion(Cursor, Play->getArea()))
		{
			//MazeLevel::setDiff(10);
			//SwitchLevel(new MazeLevel());
		}
		else if (inRegion(Cursor, Easy->getArea()))
		{
			//MazeLevel::setDiff(0);
			//SwitchLevel(new MazeLevel());
		}
		else if (inRegion(Cursor, Hard->getArea()))
		{
			//MazeLevel::setDiff(90);
			//SwitchLevel(new MazeLevel());
		}
		break;
	default:
		break;
	}
}
void OpeningScreen::Keyboard(int m_Event, WPARAM wParam)
{
	switch (m_Event)
	{
	case 0://keydown
		switch (wParam)
		{
		case VK_SPACE:
			//SwitchLevel(new MazeLevel());
			break;
		}
		break;
	}
}