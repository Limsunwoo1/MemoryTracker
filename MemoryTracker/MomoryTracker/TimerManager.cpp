#include "TimerManager.h"
#include "MainGame.h"

CTimerManager::CTimerManager()
: DeltaTime(0.f)
, AccDeltaTime(0.f)
, CallCount(0)
, FramePerSecond(0)
{

}

CTimerManager::~CTimerManager()
{
	
}

void CTimerManager::Init()
{
	QueryPerformanceCounter(&CurTickCount);
	QueryPerformanceCounter(&PrevTickCount);
	QueryPerformanceFrequency(&Frequency);
}

void CTimerManager::Update()
{
	QueryPerformanceCounter(&CurTickCount);

	DeltaTime = (double)(CurTickCount.QuadPart - PrevTickCount.QuadPart) / (double)Frequency.QuadPart;

	PrevTickCount = CurTickCount;

	++CallCount;
	AccDeltaTime += DeltaTime;
	if (AccDeltaTime > 1.f)
	{
		FramePerSecond = CallCount;
		CallCount = 0;
		AccDeltaTime = 0.f;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %lf", FramePerSecond, DeltaTime);
		SetWindowText(CMainGame::GetInstance()->GetHwnd(), szBuffer);
	}
}