#pragma once
#include "framework.h"
#include "Define.h"
#include <vector>
using namespace std;

enum class KEY_STATE
{
	NONE,	// 안눌림
	TAB,	// 처음 누른 경우
	HOLD,	// 누르고 있는 경우
	AWAY,	// 뗀 경우
};

enum class KEY
{
	SPACE,
	LBUTTON,
	RBUTTON,
	W,
	A,
	S,
	D,
	MAX,
};

typedef struct _KeyInfo {
	KEY_STATE	KeyState; // 해당 키의 현재 상태
	bool		PrevPush; // 이전에 눌렸는지 여부
}KeyInfo;

class CKeyManager
{
	SINGLE(CKeyManager);

private:
	vector<KeyInfo> KeyInfoArr;
	POINT			MousePos;

public:
	void Init();
	void Update(float InDeltaTime);

	KEY_STATE GetKeyState(KEY InKey);
	POINT GetMousePos() { return MousePos; }
};

