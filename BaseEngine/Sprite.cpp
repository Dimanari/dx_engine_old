#include "Sprite.h"
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib,"Windowscodecs.lib")
#if defined(CLSID_WICImagingFactory)
#undef CLSID_WICImagingFactory
#endif

Sprite::Sprite(wchar_t * filename)
{
	bmp = NULL;
	HRESULT hr;

	IWICImagingFactory *wicFactory = NULL;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicFactory);
	if (hr != S_OK)
	{
		fprintf(stderr, "Failed Creating WIC Factory");
	}

	IWICBitmapDecoder *wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
		filename, NULL,
		GENERIC_READ, WICDecodeMetadataCacheOnLoad,
		&wicDecoder);
	if (hr != S_OK)
	{
		fprintf(stderr, "could not create wicDecoder");
	}
	
	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame);
	if (hr != S_OK)
	{
		fprintf(stderr, "could not create wicFrame");
	}

	IWICFormatConverter* wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);
	if (hr != S_OK)
	{
		fprintf(stderr,"could not create wicConverter");
	}

	hr = wicConverter->Initialize(
		wicFrame, GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone, NULL, 0.0, WICBitmapPaletteTypeCustom);
	if (hr != S_OK)
	{
		fprintf(stderr,  "could not Initialize wicConverter");
	}
	hr = gfx->getRenderTarget()->CreateBitmapFromWicBitmap(wicConverter, NULL, &bmp);
	wicConverter->Release();
	wicFrame->Release();
	wicDecoder->Release();
	wicFactory->Release();

	width = bmp->GetSize().width;height = bmp->GetSize().height;
	across = 1;
}

Sprite::Sprite(wchar_t * filename, int SpriteWidth, int SpriteHeight)
{
	bmp = NULL;
	HRESULT hr;

	IWICImagingFactory *wicFactory = NULL;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicFactory);
	if (hr != S_OK)
	{
		fprintf(stderr, "Failed Creating WIC Factory");
	}

	IWICBitmapDecoder *wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
		filename, NULL,
		GENERIC_READ, WICDecodeMetadataCacheOnLoad,
		&wicDecoder);
	if (hr != S_OK)
	{
		fprintf(stderr, "could not create wicDecoder");
	}

	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame);
	if (hr != S_OK)
	{
		fprintf(stderr, "could not create wicFrame");
	}

	IWICFormatConverter* wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);
	if (hr != S_OK)
	{
		fprintf(stderr, "could not create wicConverter");
	}

	hr = wicConverter->Initialize(
		wicFrame, GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone, NULL, 0.0, WICBitmapPaletteTypeCustom);
	if (hr != S_OK)
	{
		fprintf(stderr, "could not Initialize wicConverter");
	}
	hr = gfx->getRenderTarget()->CreateBitmapFromWicBitmap(wicConverter, NULL, &bmp);
	wicConverter->Release();
	wicFrame->Release();
	wicDecoder->Release();
	wicFactory->Release();

	width = SpriteWidth; height = SpriteHeight;
	across = bmp->GetSize().width/SpriteWidth;
}

Sprite::~Sprite()
{
	if (bmp)
	{
		bmp->Release();
	}
}

void Sprite::Draw()
{
	gfx->getRenderTarget()->DrawBitmap(bmp, D2D1::RectF(100, 100, 600, 400), 0.7, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0, width, height));
}

void Sprite::Draw(int x, int y, int frame)
{
	float offsetXneg, offsetXpos, offsetYneg, offsetYpos;
	offsetXneg = offsetXpos = offsetYneg = offsetYpos = 0;

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
		offsetXneg = -x;
		x = 0;
	}
	if (y < 0)
	{
		if (-y > height)
			return;
		offsetYneg = -y;
		y = 0;
	}

	
	if (x + width > SCREEN_WIDTH)
	{
		offsetXpos = x + width - SCREEN_WIDTH;
	}
	if (y + height > SCREEN_HEIGHT)
	{
		offsetYneg = y + height - SCREEN_HEIGHT;
	}
	gfx->getRenderTarget()->DrawBitmap(bmp, D2D1::RectF(x, y, x+width - offsetXneg - offsetXpos, y+height - offsetYneg - offsetYpos), 0.7, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(width*(frame%across) + offsetXneg, height*(frame/across) + offsetYneg, width*(frame%across)+ width - offsetXpos, height*(frame / across)+ height - offsetYpos));
}
