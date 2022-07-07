#pragma once
#include "Define.h"

class CObject;

class CCollisionManager
{
	SINGLE(CCollisionManager);
private:

public:
	void Init();
	void Update(float InDeltaTime);

	bool CheckCollision(CObject* InObject, CObject* InOtherObject);
};

