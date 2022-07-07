#pragma once

// 주석처리하면 충돌 사각형 안보임
//#define SHOW_COLLISION

#ifdef _DEBUG
#	define USE_MEMORY_TRACE 1
#	define USE_LOGER		1
#else
//#	define USE_MEMORY_TRACE
//#	define USE_LOGER
#endif


#define SINGLE(type) \
private: \
	type(); \
	~type(); \
public: \
	static type* GetInstance() \
	{ \
		static type* Instance; \
		if(Instance == nullptr) \
			Instance = new type(); \
		return Instance; \
	} \
	static void DestroyInstance() \
	{ \
		if(GetInstance()) \
			delete GetInstance(); \
	} \

#define KEY_STATE(InKey) CKeyManager::GetInstance()->GetKeyState(InKey)
#define MOUSE_POS CKeyManager::GetInstance()->GetMousePos();

#define MEMBER(type, name)									\
private:													\
	type name;												\
public:														\
	void Set##name(const type& InValue) {name = InValue;}	\
	type Get##name() {return name;}

#define PROTECT_MEMBER(type, name)							\
protected:													\
	type name;												\
public:														\
	void Set##name(const type& InValue) {name = InValue;}	\
	type Get##name() {return name;}