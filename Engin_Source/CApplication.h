#pragma once
#include "CEngine.h"
#include "Graphics.h"
#include "CGraphicDevice_DX11.h"

class CApplication
{
public:
	CApplication();
	~CApplication();

	virtual void Initalize();
	// CPU Update
	virtual void Update();
	// GPU Update
	virtual void FixedUpdate();
	virtual void Render();
	virtual void Destroy();
	
	// Running main engine loop
	void Run();
	void Release();
	void Present();

	void SetWindow(HWND hwnd, UINT width, UINT height);

	void SetHwnd(HWND hwnd) { mHwnd = hwnd; }
	HWND GetHwnd() { return mHwnd; }
	UINT GetWidth() { return mWidth; }
	UINT GetHeight() { return mHeight; }

private:
	bool initalized = false;
	std::unique_ptr<graphics::CGraphicDevice_DX11> graphicDevice;

	HWND mHwnd; // 핸들값 - 윈도우에서 할당된 메모리에 접근할수있는 권한을 준다.
	HDC mHdc;
	UINT mHeight;
	UINT mWidth;
};