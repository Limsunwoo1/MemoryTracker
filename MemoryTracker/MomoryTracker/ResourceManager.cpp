#include "ResourceManager.h"
#include "CTexture.h"

CResourceManager::CResourceManager()
{

}

CResourceManager::~CResourceManager()
{
	for (std::pair<string, CTexture*> textureInfo : TextureList)
		delete textureInfo.second;

	TextureList.clear();
}

void CResourceManager::Init(HINSTANCE InHInst, HDC InHdc)
{
	HInstance = InHInst;
	Hdc = InHdc;


	LoadTexture("PLAYER",L"Texture/UnBroken.bmp");
	LoadTexture("BULLET", L"Texture/BubbleBobblePart2Sheet12.bmp");
	LoadTexture("BLOCK", L"Texture/YellowBlock/YellowBlock_0.bmp");
	LoadTexture("BACKGRUOND", L"Texture/graveyard (2).bmp");
	LoadTexture("BLOCK2", L"Texture/YellowBlock/YellowBlock_1.bmp");
	LoadTexture("BLOCK1", L"Texture/YellowBlock/YellowBlock_2.bmp");
}

CTexture* CResourceManager::LoadTexture(const string& InName, const wstring& InFilePath)
{
	CTexture* texture = FindTexture(InName);
	if (texture)
		return texture;

	texture = new CTexture;
	if (!texture)
		return nullptr;

	if (texture->LoadTexture(InName, HInstance, Hdc, InFilePath))
	{
		TextureList.emplace(make_pair(InName, texture));
	}
	else
	{
		delete texture;
		texture = nullptr;
	}

	return texture;
}

CTexture* CResourceManager::FindTexture(const string& InName)
{
	//find 에 실패하면 iter에는 end() 값이 담긴다
	auto iter = TextureList.find(InName);
	if (iter == TextureList.end())
		return nullptr;

	return iter->second;
}
