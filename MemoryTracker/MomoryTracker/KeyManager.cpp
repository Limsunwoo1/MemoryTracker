#include "KeyManager.h"
#include "MainGame.h"
#include <windows.h>
#include <iostream>

int KeyArr[(int)KEY::MAX] =
{
	VK_SPACE,
	VK_LBUTTON,
	VK_RBUTTON,
	'W',
	'A',
	'S',
	'D'
};

CKeyManager::CKeyManager()
{

}

CKeyManager::~CKeyManager()
{
	KeyInfoArr.clear();
}

void CKeyManager::Init()
{
	for (int i = 0; i < (int)KEY::MAX; ++i)
	{
		KeyInfoArr.push_back(KeyInfo{KEY_STATE::NONE, false});
	}

}

void CKeyManager::Update(float InDeltaTime)
{
	for (int i = 0; i < (int)KEY::MAX; ++i)
	{
		if (GetAsyncKeyState(KeyArr[i]) & 0x8000)
		{
			if (KeyInfoArr[i].PrevPush)
			{
				KeyInfoArr[i].KeyState = KEY_STATE::HOLD;
			}
			else
			{
				KeyInfoArr[i].KeyState = KEY_STATE::TAB;
			}

			KeyInfoArr[i].PrevPush = true;
		}
		else
		{
			if (KeyInfoArr[i].PrevPush)
			{
				KeyInfoArr[i].KeyState = KEY_STATE::AWAY;
			}
			else
			{
				KeyInfoArr[i].KeyState = KEY_STATE::NONE;
			}

			KeyInfoArr[i].PrevPush = false;
		}
	}

	GetCursorPos(&MousePos);
	ScreenToClient(CMainGame::GetInstance()->GetHwnd(), &MousePos);
}

KEY_STATE CKeyManager::GetKeyState(KEY InKey)
{
	return KeyInfoArr[(int)InKey].KeyState;
}