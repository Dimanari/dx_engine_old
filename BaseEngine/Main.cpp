#include <Windows.h>
#include "Controller.h"
#include "Graphics.h"
#include "../Opening.h"

#pragma comment(lib,"Winmm.lib")
//global
Graphics *gfx;
LRESULT CALLBACK WindowProc(
	HWND   hwnd,
	UINT   uMsg,
	WPARAM wParam,
	LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hInstance = hInst;
	wc.lpszClassName = "MainWindow";
	wc.lpfnWndProc = WindowProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx(&wc);
	RECT rc = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	AdjustWindowRectEx(&rc, WS_OVERLAPPEDWINDOW, NULL, WS_EX_OVERLAPPEDWINDOW);
	HWND hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MainWindow", "Dimanari 2d Engine", WS_OVERLAPPEDWINDOW, 50, 50, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInst, NULL);
	if (!hwnd)
		return -1;
	gfx = new Graphics();
	if (!gfx->Init(hwnd))
	{
		delete gfx;
		return -1;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	ShowCursor(FALSE);
	Level::Init(gfx);
	Button::setGraphics(gfx);
	Controller::LoadInitialLevel(new OpeningScreen());
	DWORD pretime;
	DWORD time = timeGetTime();
	srand(timeGetTime());
	pretime = time;
	MSG msg;
	do
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			time = timeGetTime();
			//update
			Controller::Update(time - pretime);
			//InvalidateRect(hwnd, NULL, false);
			pretime = time;
			//render
			gfx->BeginDraw();
			Controller::Render();
			gfx->EndDraw();
		}
	} while (msg.message != WM_QUIT);
	delete gfx;
	Controller::ShutDown();
	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	POINTS ptsBegin;
	//all events
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		//keyboard event
		Controller::Keyboard(0, wParam);
		break;
	case WM_KEYUP:
		Controller::Keyboard(1, wParam);
		//keyboard event
		break;
	case WM_MOUSEMOVE:
		SetCapture(hwnd);
		ptsBegin = MAKEPOINTS(lParam);
		Controller::Mouse(0, ptsBegin.x, ptsBegin.y);
		break;
	case WM_LBUTTONDOWN:
		SetCapture(hwnd);
		ptsBegin = MAKEPOINTS(lParam);
		Controller::Mouse(1, ptsBegin.x, ptsBegin.y);
		break;
	case WM_LBUTTONUP:
		SetCapture(hwnd);
		ptsBegin = MAKEPOINTS(lParam);
		Controller::Mouse(3, ptsBegin.x, ptsBegin.y);
		break;
	case WM_RBUTTONDOWN:
		SetCapture(hwnd);
		ptsBegin = MAKEPOINTS(lParam);
		Controller::Mouse(2, ptsBegin.x, ptsBegin.y);
		break;
	case WM_RBUTTONUP:
		SetCapture(hwnd);
		ptsBegin = MAKEPOINTS(lParam);
		Controller::Mouse(4, ptsBegin.x, ptsBegin.y);
		break;
	}
	return DefWindowProc(hwnd,uMsg,wParam, lParam);
}

void Quit()
{
	PostQuitMessage(0);
}
