#pragma once
#include "framework.h"
#include "Object.h"
#include "Define.h"
#include <random>

class CMainGame
{
	SINGLE(CMainGame);
private:
	HDC Hdc;
	HDC BackHdc;

	HBITMAP BitMap;
	HBITMAP BackBitMap;

	HWND Hwnd;
	HINSTANCE HInstance;

	
public:
	void Init(HWND InHwnd, HINSTANCE InHInstance);
	void Logic();

	virtual void Update(float InDeltaTime);
	void Render();
	void Clear();

	HWND GetHwnd() {return Hwnd;}
};
