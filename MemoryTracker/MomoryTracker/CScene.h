#pragma once
#include "Base.h"
#include "Object.h"
#include <vector>
#include <map>

class CScene : public CBase
{
public:
	typedef std::map<OBJ_LAYER, std::vector<OBJ_LAYER>> CollisionLayerInfo;
	typedef std::pair<OBJ_LAYER, std::vector<OBJ_LAYER>> CollisionLayerPair;

protected:
	std::vector<CObject*> OBJvector[(int)OBJ_LAYER::MAX];

	CollisionLayerInfo CheckCollisionLayer;
public:
	CScene();
	virtual ~CScene();

	virtual void Init();	// 씬에서 필요한 오브젝트같은 객체들을 생성해서 세팅한다
	virtual void Clear();   // 현재 씬의 정보를 전부 소멸시킨다

	virtual void Update(float InDeltaTime);
	virtual void LateUpdate(float InDeltaTime);

	void AddObject(OBJ_LAYER InLayer, CObject* InObject);
	void DeleteObject(OBJ_LAYER InLayer, CObject* InObject);

	const std::vector<CObject*>& Get_Object(OBJ_LAYER InLayer) const;

	const CollisionLayerInfo& GetCollisionLayer() {return CheckCollisionLayer;}

	void Render(HDC InHdc);
	void ClearObject();
};

