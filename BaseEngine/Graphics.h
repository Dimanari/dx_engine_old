#pragma once
#include <d2d1.h>
#include <dwrite.h>
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class Graphics
{
	ID2D1Factory *factory;
	ID2D1HwndRenderTarget *render;
	ID2D1SolidColorBrush *br;
	IDWriteFactory *dwriteFactory;
	IDWriteTextFormat *textFormat;
public:
	Graphics();
	~Graphics();
	void BeginDraw();
	void EndDraw();
	void ClearScreen(float r, float g, float b);
	void DrawPixel(float x, float y, float r, float g, float b);
	void DrawRect(float x, float y, float width, float hight, float r, float g, float b);
	void FillRect(float x, float y, float width, float hight, float r, float g, float b);
	void DrawCircle(float x, float y, float radius, float r, float g, float b);
	void DrawString(float x, float y, float width, float hight, const WCHAR *text, float fontsize, bool centered = false, float r = 1.0, float g = 1.0, float b = 1.0);
	bool Init(HWND windowHandler);
	ID2D1HwndRenderTarget *getRenderTarget() { return render; }
};

int stringlenght(const WCHAR *str);