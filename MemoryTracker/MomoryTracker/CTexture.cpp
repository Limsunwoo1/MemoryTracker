#include "CTexture.h"
CTexture::CTexture()
{

}
CTexture::~CTexture()
{
	SelectObject(Hdc, OldTextureHandle);

	DeleteObject(TextureHandle);

	DeleteDC(Hdc);
}


bool CTexture::LoadTexture(const string& InName, HINSTANCE InHInst, HDC InHdc, const wstring& InFilePath)
{
	Name = InName;
	FilePath = InFilePath;

	TextureHandle = (HBITMAP)LoadImageW(InHInst, InFilePath.c_str(),    //Load 함수 모르겠음
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);     // 아래 디파인 모르겠음

	Hdc = CreateCompatibleDC(InHdc);
	
	OldTextureHandle = (HBITMAP)SelectObject(Hdc, TextureHandle);

	GetObject(TextureHandle, sizeof(TextureInfo), &TextureInfo);

	return true;
}
