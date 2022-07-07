#pragma once
#include "framework.h"
#include "Base.h"

class CTexture;

enum class OBJ_LAYER : short {
	BACKGROUND =	0,
	RING =			5,
	BLOCK1 =		12,
	BLOCK2 =		15,
	BLOCK3 =		18,
	REDBALL	=		21,
	BLUEBALL =		24,
	UI =			30,
	MAX =			32,
};

class CObject : public CBase
{
	PROTECT_MEMBER(Vector2D, Position)

		PROTECT_MEMBER(Vector2D, Scale)

		PROTECT_MEMBER(Vector2D, CollisionScale)

		PROTECT_MEMBER(OBJ_LAYER, ObjectLayer)

private:
	static unsigned int Id;
	unsigned int ObjectId;

protected:
	CTexture* Texture;

	bool PrevCollision;
	bool CurCollision;
public:
	CObject();
	CObject(Vector2D InPosition, Vector2D InScale);
	virtual ~CObject();

	virtual void Update(float InDeltaTime);
	virtual void LateUpdate(float InDeltaTime); // Render 되기 전 마지막 업데이트
	virtual void Render(HDC InHdc);

	virtual void Collision(const CObject* InOtherObject);

public:
	void SetTexture(CTexture* InTexture);

	unsigned int GetId() const { return ObjectId; }
};

