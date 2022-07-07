#include "UI.h"
#include "Define.h"
#include "KeyManager.h"

CUI::CUI() 
: CObject()
{
}

CUI::CUI(Vector2D InPosition, Vector2D InScale) 
: CObject(InPosition, InScale)
{
}

CUI::~CUI()
{

}

void CUI::Update(float InDeltaTime)
{
	CObject::Update(InDeltaTime);

	POINT mousePos = MOUSE_POS;

	Vector2D UIPos = GetPosition();
	Vector2D UIScale = GetScale();

	CurCollision = CheckMouseCollision(this);

	if (CurCollision && !PrevCollision)
		MouseFirstOn();
	else if (CurCollision && PrevCollision)
		MouseOn();
	else if (!CurCollision && PrevCollision)
		MouseFirstOff();

	if (CurCollision)
	{
		if (KEY_STATE(KEY::LBUTTON) == KEY_STATE::HOLD)
			MouseLButtonPress();
		else if (KEY_STATE(KEY::LBUTTON) == KEY_STATE::AWAY)
			MouseLButtonRelease();
		if (KEY_STATE(KEY::RBUTTON) == KEY_STATE::HOLD)
			MouseRButtonPress();
		else if (KEY_STATE(KEY::RBUTTON) == KEY_STATE::AWAY)
			MouseRButtonRelease();
	}

	PrevCollision = CurCollision;
}

void CUI::Render(HDC InHdc)
{
	CObject::Render(InHdc);
}

bool CUI::CheckMouseCollision(CUI* InUI)
{
	POINT mousePos = MOUSE_POS;

	Vector2D UIPos = InUI->GetPosition();
	Vector2D UIScale = InUI->GetScale();

	if (mousePos.x < UIPos.x - (UIScale.x * 0.5f))
		return false;
	if (mousePos.x > UIPos.x + (UIScale.x * 0.5f))
		return false;
	if (mousePos.y < UIPos.y - (UIScale.y * 0.5f))
		return false;
	if (mousePos.y > UIPos.y + (UIScale.y * 0.5f))
		return false;

	return true;
}