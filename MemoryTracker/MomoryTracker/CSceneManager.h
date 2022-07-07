#pragma once
#include "Define.h"
#include "Object.h"
#include <vector>

class CScene;

class CSceneManager
{
	SINGLE(CSceneManager);
private:
	CScene*	 CurScene;

public:
	void Init();
	void Update(float InDeltaTime);
	void LateUpdate(float InDeltaTime);
    void Render(HDC InHdc);

	void SetCurScene(CScene* InNewScene);
	CScene* GetCurScene() {return CurScene;}

	void AddObject(OBJ_LAYER InLayer, CObject* InObject);
	void DeleteObject(OBJ_LAYER InLayer, CObject* InObject);

    const std::vector<CObject*>& Get_Object(OBJ_LAYER InLayer);
};

