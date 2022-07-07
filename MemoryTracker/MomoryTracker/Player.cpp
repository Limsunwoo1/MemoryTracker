#include "Player.h"
#include "KeyManager.h"
#include "CSceneManager.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "CTexture.h"

CPlayer::CPlayer() : CObject(Vector2D{ 100, 100 }, Vector2D{ 50, 50 })
{

}

CPlayer::CPlayer(Vector2D InVector, Vector2D InScale) : CObject(Vector2D{ InVector.x , InVector.y }, Vector2D{ InScale.x, InScale.y })
{

}

CPlayer::~CPlayer()
{

}

void CPlayer::Update(float InDeltaTime)
{
	CObject::Update(InDeltaTime);

	int SPEED = 1000;
	if (KEY_STATE(KEY::A) == KEY_STATE::HOLD)
	{
		Vector2D position = Position;
		position.x -= SPEED * InDeltaTime;

		if (position.x < 20)
		{
			position.x = 20;
		}

		Position = position;
	}

	if (KEY_STATE(KEY::D) == KEY_STATE::HOLD)
	{
		Vector2D position = Position;
		position.x += SPEED * InDeltaTime;

		if (position.x > 940)
		{
			position.x = 940;
		}

		Position = position;
	}
}

void CPlayer::Collision(const CObject* InOtherObject)
{
	CObject::Collision(InOtherObject);

	/*EventInfo eventInfo;
	eventInfo.Type = EVENT_TYPE::DELETE_OBJECT;
	eventInfo.Parameter = new OBJ_LAYER(ObjLayer);
	eventInfo.Parameter2 = this;
	CEventManager::GetInstance()->AddEvent(eventInfo);*/
}

void CPlayer::Render(HDC InHdc)
{
	// 알파값 == 투명값
	// 투명하게 띄우는거, 반투명하게 띄우는거를 알파블렌딩 이라고 한다
	// 색상을 섞는다는 블렌딩의 의미

	// bmp 파일은 보통 색상이 24비트짜리
	// R : 8비트
	// G : 8비트
	// B : 8비트 0 ~ 255 값
	// 32 비트는 여기에 A : 8 비트가 추가된 값 ( 알파값 )

	if (Texture)
	{
		// 32비트 bmp 는 bf.AlphaFormat = AC_SRC_ALPHA
		// 24비트 bmp 는 bf.AlphaFormat = 0

		BLENDFUNCTION bf = {};
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = 0;
		bf.SourceConstantAlpha = 255;

		AlphaBlend(InHdc,
			(int)(Position.x - (Texture->GetWidth() * 0.5f)),
			(int)(Position.y - (Texture->GetHeight() * 0.5f)),
			Texture->GetWidth(),
			Texture->GetHeight(),
			Texture->GetHdc(),
			0,
			0,
			Texture->GetWidth(),
			Texture->GetHeight(),
			bf);
	}
	else
	{
		Rectangle(InHdc,
			(int)(Position.x - (Scale.x * 0.5f)),
			(int)(Position.y - (Scale.y * 0.5f)),
			(int)(Position.x + (Scale.x * 0.5f)),
			(int)(Position.y + (Scale.y * 0.5f)));
	}
}