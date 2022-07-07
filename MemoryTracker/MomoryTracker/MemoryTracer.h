#pragma once
#include "CallStackTracer.h"
#include "Define.h"
#include "Typedef.h"
#include "UtilLog.h"
#include "Loger.h"
#include <stdlib.h>
#include <unordered_map>

class CMemoryTracer
{
private:
	class MemoryBlock 
	{
	public:
		int64			Id;
		size_t			Size;
		CallStackPtr	CallStack;
	};

	typedef std::unordered_map<const void*, MemoryBlock*> FMemoryBlockMap;

private:
	FMemoryBlockMap		MemoryBlockMap;
	std::thread::id		ThreadId;
	SymbolLookup		Lookup;

private:
	CMemoryTracer();
	~CMemoryTracer();

	static CMemoryTracer* Instance;

public:
	static CMemoryTracer* GetInstance();

	static bool IsVaild();

	static void DestroyInstance();

	void Init();

	void OnAllocated(void* InAddress, size_t InSize);

	void OnDeallocated(void* InAddress);

	void PrintMemoryBlockAll();

private:
	void _PrintMemoryBlock(const MemoryBlock* InMemoryBlock);
};