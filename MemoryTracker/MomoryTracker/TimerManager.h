#pragma once
#include "Define.h"
#include <windows.h>

class CTimerManager
{
	SINGLE(CTimerManager);
private:
// -9,223,372,036,854,775,808 ~ 9,223,372,036,854,775,807
	LARGE_INTEGER CurTickCount;
	LARGE_INTEGER PrevTickCount;
	LARGE_INTEGER Frequency;

	double DeltaTime;		// 시간 변화량
	// Acc : 누적이라는 의미로 프로그래밍에서 사용
	double AccDeltaTime;		// 누적 델타 타임
	int CallCount;			// 함수 호출 횟수
	int FramePerSecond;		// 초당 프레임 횟수

public:
	void Init();
	void Update();

	float GetDeltaTime() {return (float)DeltaTime;}
};

