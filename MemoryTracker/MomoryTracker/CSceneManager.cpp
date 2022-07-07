#include "CSceneManager.h"
#include "CScene.h"
#include "CTitleScene.h"
#include "Func.h"
#include "EventManager.h"
#include <random>

//random_device rd;
//mt19937 gen(rd());
//uniform_int_distribution<int> dis(0, 980);
//uniform_int_distribution<int> Dis(50, 150);


CSceneManager::CSceneManager()
: CurScene(nullptr)
{

}

CSceneManager::~CSceneManager()
{
	CurScene->Clear();
	delete CurScene;
	CurScene = nullptr;
}

void CSceneManager::Init()
{
	CurScene = new CTitleScene();
	CurScene->Init();
}

void CSceneManager::Update(float InDeltaTime)
{
	CurScene->Update(InDeltaTime);
}

void CSceneManager::LateUpdate(float InDeltaTime)
{
	CurScene->LateUpdate(InDeltaTime);
}

void CSceneManager::Render(HDC InHdc)
{
	CurScene->Render(InHdc);
}

void CSceneManager::SetCurScene(CScene* InNewScene)
{
	CurScene->Clear();
	CEventManager::GetInstance()->Clear();
	CurScene = InNewScene;
	CurScene->Init();
}

void CSceneManager::AddObject(OBJ_LAYER InLayer, CObject* InObject)
{
	CurScene->AddObject(InLayer, InObject);
}

void CSceneManager::DeleteObject(OBJ_LAYER InLayer, CObject* InObject)
{
	CurScene->DeleteObject(InLayer, InObject);
}

const std::vector<CObject*>& CSceneManager::Get_Object(OBJ_LAYER InLayer)
{
	return CurScene->Get_Object(InLayer);
}
