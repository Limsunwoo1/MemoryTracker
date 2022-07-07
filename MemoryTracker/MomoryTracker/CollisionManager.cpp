#include "CollisionManager.h"
#include "Object.h"
#include "CSceneManager.h"
#include "CScene.h"
#include <vector>


CCollisionManager::CCollisionManager()
{

}

CCollisionManager::~CCollisionManager()
{
}

void CCollisionManager::Init()
{

}

void CCollisionManager::Update(float InDeltaTime)
{
	CScene* curScene = CSceneManager::GetInstance()->GetCurScene();
	const CScene::CollisionLayerInfo& checkCollisionLayer = curScene->GetCollisionLayer();

	// std::map<OBJ_LAYER, std::vector<OBJ_LAYER>> CollisionLayerInfo
	// std::pair<OBJ_LAYER, std::vector<OBJ_LAYER>> CollisionLayerPair
	for (const CScene::CollisionLayerPair& collisionLayerPair : checkCollisionLayer)
	{
		for (CObject* object : curScene->Get_Object(collisionLayerPair.first))
		{
			for (OBJ_LAYER otherLayer : collisionLayerPair.second)
			{
				for (CObject* otherObject : curScene->Get_Object(otherLayer))
				{
					if (!CheckCollision(object, otherObject))
						continue;

					object->Collision(otherObject);
					otherObject->Collision(object);
				}
			}
		}
	}
}

bool CCollisionManager::CheckCollision(CObject* InObject, CObject* InOtherObject)
{
	Vector2D position1 = InObject->GetPosition();
	Vector2D scale1 = InObject->GetCollisionScale();

	Vector2D position2 = InOtherObject->GetPosition();
	Vector2D scale2 = InOtherObject->GetCollisionScale();

	if (position1.x + (scale1.x * 0.5) < position2.x - (scale2.x * 0.5) ||
		position1.x - (scale1.x * 0.5) > position2.x + (scale2.x * 0.5))
		return false;

	if (position1.y + (scale1.y * 0.5) < position2.y - (scale2.y * 0.5) ||
		position1.y - (scale1.y * 0.5) > position2.y + (scale2.y * 0.5))
		return false;

	return true;
}