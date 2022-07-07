#pragma once
#include "Define.h"
#include <list>

enum class EVENT_TYPE : short {
	NONE,
	ADD_OBJECT,
	DELETE_OBJECT,
};

// ADD_OBJECT
// Parameter = OBJ_LAYER
// Parameter2 = CObject

// DELETE_OBJECT
// Parameter = OBJ_LAYER
// Parameter2 = CObject

typedef struct EventInfo {
	EVENT_TYPE	Type;
	void*		Parameter;
	void*		Parameter2;
	void*		Parameter3;

	EventInfo() : Type(EVENT_TYPE::NONE), Parameter(nullptr), Parameter2(nullptr), Parameter3(nullptr) {}
	EventInfo(EVENT_TYPE InType, void* InParameter) : Type(InType), Parameter(InParameter), Parameter2(nullptr), Parameter3(nullptr) {}
	EventInfo(EVENT_TYPE InType, void* InParameter, void* InParameter2) : Type(InType), Parameter(InParameter), Parameter2(InParameter2), Parameter3(nullptr) {}
	EventInfo(EVENT_TYPE InType, void* InParameter, void* InParameter2, void* InParameter3) : Type(InType), Parameter(InParameter), Parameter2(InParameter2), Parameter3(InParameter3) {}
}EventInfo;

class CEventManager
{
	SINGLE(CEventManager);
private:
	// 선입 선출 되는 자료구조가 더 좋음
	std::list<EventInfo> EventList;

public:
	void Init();
	void Clear();
	void Update(float InDeltaTime);
	void AddEvent(const EventInfo& InEventInfo);
};

