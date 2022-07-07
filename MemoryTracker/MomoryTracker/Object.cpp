#include "Object.h"
#include "CTexture.h"
#include "Define.h"

unsigned int CObject::Id = 100;

static HPEN Green_Pen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
static HPEN Red_Pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
static HPEN Black_Pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

static HBRUSH Null_Brush = (HBRUSH)GetStockObject(NULL_BRUSH);
static HBRUSH Default_Brush = CreateSolidBrush(RGB(255, 255, 255));

CObject::CObject()
	: Position()
	, Scale()
	, CollisionScale()
	, ObjectLayer(OBJ_LAYER::MAX)
	, Texture(nullptr)
{
	PrevCollision = false;
	CurCollision = false;
	ObjectId = Id++;
}
CObject::CObject(Vector2D InPosition, Vector2D InScale)
	: Position(InPosition)
	, Scale(InScale)
	, CollisionScale(InScale)
	, ObjectLayer(OBJ_LAYER::MAX)
	, Texture(nullptr)
{
	PrevCollision = false;
	CurCollision = false;
	ObjectId = Id++;
}

CObject::~CObject()
{

}

void CObject::SetTexture(CTexture* InTexture)
{
	Texture = InTexture;

	SetScale(Vector2D((int)Texture->GetWidth(), (int)Texture->GetHeight()));
	SetCollisionScale(Vector2D((int)Texture->GetWidth(), (int)Texture->GetHeight()));
}

void CObject::Update(float InDeltaTime)
{
	CurCollision = false;
}

void CObject::LateUpdate(float InDeltaTime)
{
	PrevCollision = CurCollision;
}

void CObject::Render(HDC InHdc)
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
		bf.AlphaFormat = AC_SRC_ALPHA;
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

		// 특정 영역의 색상을 아예 그리지 않는다
	/*	TransparentBlt(InHdc,
			Position.x - (Texture->GetWidth() * 0.5f),
			Position.y - (Texture->GetHeight() * 0.5f),
			Texture->GetWidth(),
			Texture->GetHeight(),
			Texture->GetHdc(),
			0,
			0,
			Texture->GetWidth(),
			Texture->GetHeight(),
			RGB(0, 0, 0));*/

			//BitBlt(InHdc,
			//	Position.x - (Texture->GetWidth() * 0.5f),
			//	Position.y - (Texture->GetHeight() * 0.5f),
			//	//Scale.x,
			//	//Scale.y,
			//	Texture->GetWidth(),
			//	Texture->GetHeight(),
			//	Texture->GetHdc(),
			//	0,
			//	0,
			//	SRCCOPY);
	}
	else
	{
		Rectangle(InHdc,
			(int)(Position.x - (Scale.x * 0.5f)),
			(int)(Position.y - (Scale.y * 0.5f)),
			(int)(Position.x + (Scale.x * 0.5f)),
			(int)(Position.y + (Scale.y * 0.5f)));
	}

#ifdef SHOW_COLLISION
	if (CurCollision)
		SelectObject(InHdc, Red_Pen);
	else
		SelectObject(InHdc, Green_Pen);
	SelectObject(InHdc, Null_Brush);

	Rectangle(InHdc,
		Position.x - (CollisionScale.x * 0.5f),
		Position.y - (CollisionScale.y * 0.5f),
		Position.x + (CollisionScale.x * 0.5f),
		Position.y + (CollisionScale.y * 0.5f));

	SelectObject(InHdc, Black_Pen);
	SelectObject(InHdc, Default_Brush);
#endif
}

void CObject::Collision(const CObject* InOtherObject)
{
	CurCollision = true;
}
