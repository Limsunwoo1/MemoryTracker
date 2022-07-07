#pragma once
#include "UI.h"
#include <string>
using namespace std;

// 0 ~ 255 까지만 사용할거라 short 사이즈만큼만 할당하도록
// 상황에 따라서 마우스가 버튼 위를 지나가고있을때 호출하는 경우도 있을수도 있다 ( 타입 추가 필요 )
enum class BUTTON_STATE : short {
    
    LBUTTON_PRESS,
    LBUTTON_RELEASE,
    RBUTTON_PRESS,
    RBUTTON_RELEASE,
    MAX,
};
class CButton :
    public CUI
{
private:
    string ButtonText;

    void (*ButtonFuncPtr[(int)BUTTON_STATE::MAX])();

public:
    CButton(Vector2D InPosition, Vector2D InScale);
    virtual ~CButton();

    virtual void Render(HDC InHdc) override;

    virtual void MouseFirstOn() override;
    virtual void MouseOn() override;
    virtual void MouseFirstOff() override;

    virtual void MouseLButtonPress() override;
    virtual void MouseLButtonRelease() override;
    virtual void MouseRButtonPress() override;
    virtual void MouseRButtonRelease() override;

public:
    void SetButtonText(const string& InButtonText) { ButtonText = InButtonText; }

    void SetButtonFunc(BUTTON_STATE InState, void (*InFunctionPtr)() ) {ButtonFuncPtr[(int)InState] = InFunctionPtr; }
};

