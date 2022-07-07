#include "Button.h"

CButton::CButton(Vector2D InPosition, Vector2D InScale)
	: CUI(InPosition, InScale)
	, ButtonText("GAME")
{
	for (int i = 0; i < (int)BUTTON_STATE::MAX; ++i)
	{
		ButtonFuncPtr[i] = nullptr;
	}
}

CButton::~CButton()
{
	for (int i = 0; i < (int)BUTTON_STATE::MAX; ++i)
	{
		ButtonFuncPtr[i] = nullptr;
	}
}

void CButton::Render(HDC InHdc)
{
	CObject::Render(InHdc);

	// c_str() : vector<char> 형태의 string 변수를 char const* 형태로 반환해줌
	TextOutA(InHdc, (int)(Position.x - (ButtonText.size() * 5.f)), (int)(Position.y), ButtonText.c_str(), (int)ButtonText.size());
	// 폰트마다 특징이 다른데 보통 영어는 알파벳마다 글씨의 길이가 다름
}

void CButton::MouseFirstOn()
{

}

void CButton::MouseOn()
{

}

void CButton::MouseFirstOff()
{

}

void CButton::MouseLButtonPress()
{
	if (ButtonFuncPtr[(int)BUTTON_STATE::LBUTTON_PRESS])
		ButtonFuncPtr[(int)BUTTON_STATE::LBUTTON_PRESS]();
}

void CButton::MouseLButtonRelease()
{
	if (ButtonFuncPtr[(int)BUTTON_STATE::LBUTTON_RELEASE])
		ButtonFuncPtr[(int)BUTTON_STATE::LBUTTON_RELEASE]();

	LOGER->AddCallStackLog();
}

void CButton::MouseRButtonPress()
{
	if (ButtonFuncPtr[(int)BUTTON_STATE::RBUTTON_PRESS])
		ButtonFuncPtr[(int)BUTTON_STATE::RBUTTON_PRESS]();
}

void CButton::MouseRButtonRelease()
{
	if (ButtonFuncPtr[(int)BUTTON_STATE::RBUTTON_RELEASE])
		ButtonFuncPtr[(int)BUTTON_STATE::RBUTTON_RELEASE]();
}