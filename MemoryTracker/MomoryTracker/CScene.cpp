#include "CScene.h"
#include <vector>
#include "Object.h"
#include "Func.h"
#include <random>
#include <iostream>
#include <algorithm>
using namespace std;

CScene::CScene()
{

}

CScene::~CScene()
{
	ClearObject();
}

void CScene::Init()
{

}

void CScene::Clear()
{
	ClearObject();
}

void CScene::Update(float InDeltaTime)
{
	for (int layer = (int)OBJ_LAYER::BACKGROUND; layer < (int)OBJ_LAYER::MAX; ++layer)
	{
		for (int i = 0; i < OBJvector[layer].size(); ++i)
		{
			OBJvector[layer][i]->Update(InDeltaTime);
		}
	}
}

void CScene::LateUpdate(float InDeltaTime)
{
	for (int layer = (int)OBJ_LAYER::BACKGROUND; layer < (int)OBJ_LAYER::MAX; ++layer)
	{
		for (int i = 0; i < OBJvector[layer].size(); ++i)
		{
			OBJvector[layer][i]->LateUpdate(InDeltaTime);
		}
	}
}

void CScene::AddObject(OBJ_LAYER InLayer, CObject* InObject)
{
	OBJvector[(int)InLayer].push_back(InObject);
}

void CScene::DeleteObject(OBJ_LAYER InLayer, CObject* InObject)
{
	auto iter = find_if( OBJvector[(int)InLayer].begin(), OBJvector[(int)InLayer].end(), 
		[InObject](const CObject* object) {
			if(InObject->GetId() == object->GetId())
				return true;

			return false;
	});

	if (iter != OBJvector[(int)InLayer].end())
	{
		delete *iter;
		OBJvector[(int)InLayer].erase(iter);
	}
}

const std::vector<CObject*>& CScene::Get_Object(OBJ_LAYER InLayer) const
{
	return OBJvector[(int)InLayer];
}

void CScene::Render(HDC InHdc)
{
	for (int layer = (int)OBJ_LAYER::BACKGROUND; layer < (int)OBJ_LAYER::MAX; ++layer)
	{
		for (int i = 0; i < OBJvector[layer].size(); ++i)
		{
			OBJvector[layer][i]->Render(InHdc);
		}
	}
 }

void CScene::ClearObject()
{
	vector<CObject*>::iterator iter;
	for (int layer = 0; layer < (int)OBJ_LAYER::MAX; ++layer)
	{
		for (iter = OBJvector[layer].begin();iter != OBJvector[layer].end();iter++)
		{
			delete *iter;
		}
		OBJvector[layer].clear();
	}

	CheckCollisionLayer.clear();
}