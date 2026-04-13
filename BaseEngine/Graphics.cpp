#include "Graphics.h"
#include <assert.h>
#include "vld.h"
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"Dwrite.lib")
Graphics::Graphics()
{
	factory = NULL;
	render = NULL;
	br = NULL;
	dwriteFactory = NULL;
	textFormat = NULL;
}

Graphics::~Graphics()
{
	if (factory)
	{
		factory->Release();
	}
	if (render)
	{
		render->Release();
	}
	if (br)
	{
		br->Release();
	}
	if (dwriteFactory)
	{
		dwriteFactory->Release();
	}
}

void Graphics::BeginDraw()
{
	render->BeginDraw();
}

void Graphics::EndDraw()
{
	render->EndDraw();
}

void Graphics::ClearScreen(float r, float g, float b)
{
	render->Clear({ r,g,b });
}

void Graphics::DrawPixel(float x, float y, float r, float g, float b)
{
	if (x >= SCREEN_WIDTH)
	{
		return;
	}
	if (y >= SCREEN_HEIGHT)
	{
		return;
	}
	if (x < 0)
	{
		return;
	}
	if (y < 0)
	{
		return;
	}
	br->SetColor({r,g,b,1});
	render->DrawLine(D2D1::Point2F(x, y), D2D1::Point2F(x+1, y),br);
}

void Graphics::DrawRect(float x, float y, float width, float hight, float r, float g, float b)
{
	if (x >= SCREEN_WIDTH)
	{
		return;
	}
	if (y >= SCREEN_HEIGHT)
	{
		return;
	}
	if (x < 0)
	{
		if (-x > width)
			return;
		x = 0;
	}
	if (y < 0)
	{
		if (-y > hight)
			return;
		y = 0;
	}
	if (x + width > SCREEN_WIDTH)
	{
		width = SCREEN_WIDTH - x;
	}
	if (y + hight > SCREEN_HEIGHT)
	{
		hight = SCREEN_HEIGHT - y;
	}
	br->SetColor({ r,g,b,1 });
	render->DrawRectangle(D2D1::RectF(x, y, x + width, y + hight), br);
}

void Graphics::FillRect(float x, float y, float width, float hight, float r, float g, float b)
{
	if (x >= SCREEN_WIDTH)
	{
		return;
	}
	if (y >= SCREEN_HEIGHT)
	{
		return;
	}
	if (x < 0)
	{
		if (-x > width)
			return;
		x = 0;
	}
	if (y < 0)
	{
		if (-y > hight)
			return;
		y = 0;
	}
	if (x + width > SCREEN_WIDTH)
	{
		width = SCREEN_WIDTH - x;
	}
	if (y + hight > SCREEN_HEIGHT)
	{
		hight = SCREEN_HEIGHT - y;
	}
	br->SetColor({ r,g,b,1 });
	render->FillRectangle(D2D1::RectF(x, y, x + width, y + hight), br);
}

void Graphics::DrawCircle(float x, float y, float radius, float r, float g, float b)
{
	br->SetColor({ r,g,b,1 });
	render->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), br);
}

void Graphics::DrawString(float x, float y, float width, float hight, const WCHAR *text, float fontsize, bool centered, float r, float g, float b)
{
	int lenght = stringlenght(text)+1;
	br->SetColor({ r,g,b,1 });
	dwriteFactory->CreateTextFormat(
		L"Gabriola",
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		fontsize,
		L"en-us",
		&textFormat);
	float centerizedX = 0;
	if(fontsize<60)
		centerizedX = centered*(width - (fontsize*lenght /3)) / 2;
	else
		centerizedX = centered*(width - (fontsize*(lenght)*2 / 5) ) / 2;
	float centerizedY = centered*(hight - (fontsize * 2)) / 2;
	render->DrawTextA(text, lenght, textFormat, D2D1::RectF(x + centerizedX, y + centerizedY, x + width - centerizedX, y + hight - centerizedY), br);
	textFormat->Release();
}

bool Graphics::Init(HWND windowHandler)
{
	HRESULT result = S_OK;
	result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (result != S_OK)
	{
		assert("could not create factory");
		return false;
	}
	RECT rc;
	GetClientRect(windowHandler, &rc);
	result = factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(windowHandler,D2D1::SizeU(rc.right,rc.bottom) ),
		&render
	);
	if (result != S_OK)
	{
		assert("could not create Render Target");
		return false;
	}
	result = render->CreateSolidColorBrush({ 0,0,0,1.0 }, &br);
	if (result != S_OK)
	{
		assert("could not create Brush");
		return false;
	}
	result = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&dwriteFactory)
	);
	if (result != S_OK)
	{
		assert("could not create DWriteFactory");
		return false;
	}
	return true;
}
int stringlenght(const WCHAR * str)
{
	int len = 0;
	while (str[len]) len++;
	return len;
}
