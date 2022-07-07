#include "EventManager.h"
#include "CSceneManager.h"

CEventManager::CEventManager()
{

}

CEventManager::~CEventManager()
{
	EventList.clear();
}

void CEventManager::Init()
{

}

// 이벤트 정보의 DELETE_OBJECT 타입은 딜리트는 절대 안된다
// DELETE_OBJECT 인 경우 실제 오브젝트는 씬에서 들고있기 때문에 여기서 날리면 안됨
// ADD_OBJECT 는 이벤트 매니저만 들고있는 추가 대기 오브젝트로 Delete 해줘야 한다
// 신규 추가되는 이벤트도 이 점 유의하고 Clear 추가할 것
void CEventManager::Clear()
{
	for (const EventInfo& eventInfo : EventList)
	{
		if(eventInfo.Type != EVENT_TYPE::ADD_OBJECT)
			continue;

		if(eventInfo.Parameter)
			delete eventInfo.Parameter;

		if (eventInfo.Parameter2)
			delete eventInfo.Parameter2;

		if (eventInfo.Parameter3)
			delete eventInfo.Parameter3;
	}
	EventList.clear();
}

void CEventManager::Update(float InDeltaTime)
{
	for (const EventInfo& eventInfo : EventList)
	{
		switch (eventInfo.Type)
		{
			case EVENT_TYPE::ADD_OBJECT:
				CSceneManager::GetInstance()->AddObject(
					*((OBJ_LAYER*)eventInfo.Parameter),
					((CObject*)eventInfo.Parameter2));

				//delete eventInfo.Parameter;
			break;
			case EVENT_TYPE::DELETE_OBJECT:
				CSceneManager::GetInstance()->DeleteObject(
					*((OBJ_LAYER*)eventInfo.Parameter),
					((CObject*)eventInfo.Parameter2));

				//delete eventInfo.Parameter;
			break;
		}
	}
	EventList.clear();
}

void CEventManager::AddEvent(const EventInfo& InEventInfo)
{
	EventList.push_back(InEventInfo);
}