#pragma once
#include "Define.h"
#include <windows.h>
#include <string>
#include <map>
using namespace std;

class CTexture;

class CResourceManager
{
	SINGLE(CResourceManager);
private:
	HDC			Hdc;
	HINSTANCE	HInstance;
	map<string, CTexture*> TextureList;
public:
	void Init(HINSTANCE InHInst, HDC InHdc);

	CTexture* LoadTexture(const string& InName, const wstring& InFilePath);
	CTexture* FindTexture(const string& InName);
};

