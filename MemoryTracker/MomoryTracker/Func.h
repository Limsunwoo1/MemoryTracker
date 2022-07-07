#pragma once
#include <windows.h>


// 인라인 함수
// 함수의 선언과 동시에 몸체까지 구현하는 함수
inline bool CheckCollision(Vector2D InPosition1, Vector2D InScale1, Vector2D InPosition2, Vector2D InScale2)
{
	if (InPosition1.x + (InScale1.x * 0.5) < InPosition2.x - (InScale2.x * 0.5) ||
		InPosition1.x - (InScale1.x * 0.5) > InPosition2.x + (InScale2.x * 0.5))
		return false;

	if (InPosition1.y + (InScale1.y * 0.5) < InPosition2.y - (InScale2.y * 0.5) ||
		InPosition1.y - (InScale1.y * 0.5) > InPosition2.y + (InScale2.y * 0.5))
		return false;

	return true;
}