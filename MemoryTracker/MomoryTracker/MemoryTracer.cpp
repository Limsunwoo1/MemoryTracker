#include "MemoryTracer.h"
#include "MemoryAllocator.h"
#include "UtilLog.h"
#include "Loger.h"
#include <format>
#include <string>
#include <conio.h>

static int g_LastId = 0;
static int g_StartCallStackIndex = 3;
static int g_MaxCallStackIndex = 16;

CMemoryTracer* CMemoryTracer::Instance = nullptr;

CMemoryTracer::CMemoryTracer()
{

}

CMemoryTracer::~CMemoryTracer()
{
	PrintMemoryBlockAll();

	for (std::pair<const void*, MemoryBlock*> memoryBlockPair : MemoryBlockMap)
	{
		MemoryBlock* memoryBlock = memoryBlockPair.second;
		if(memoryBlock)
			delete memoryBlock;
	}

	MemoryBlockMap.clear();
}

CMemoryTracer* CMemoryTracer::GetInstance()
{
	if (!Instance)
	{
		Instance = new CMemoryTracer();
	}
	return Instance;
}

bool CMemoryTracer::IsVaild()
{
	return Instance ? true : false;
}

void CMemoryTracer::DestroyInstance()
{
	if (Instance)
	{
		delete Instance;
		Instance = nullptr;
	}
}

void CMemoryTracer::Init()
{
	ThreadId = std::this_thread::get_id();
}

void CMemoryTracer::OnAllocated(void* InAddress, size_t InSize)
{
	if(!InAddress || ThreadId != std::this_thread::get_id())
		return;

	SetDefaultMemoryAllocator();

	CallStack stack;

	MemoryBlock* memoryBlock = new MemoryBlock();
	memoryBlock->Size = InSize;
	memoryBlock->Id = g_LastId++;
	memoryBlock->CallStack = std::make_shared<CallStack>(stack);
	MemoryBlockMap[InAddress] = memoryBlock;

	SetCustomMemoryAllocator();
}

void CMemoryTracer::OnDeallocated(void* InAddress)
{
	if (ThreadId != std::this_thread::get_id())
		return;

	SetDefaultMemoryAllocator();

	auto iter = MemoryBlockMap.find(InAddress);
	if (iter != MemoryBlockMap.end())
	{
		MemoryBlock* memoryBlock = iter->second;

		if(memoryBlock)
			delete memoryBlock;

		MemoryBlockMap.erase(iter);
	}

	SetCustomMemoryAllocator();
}

void CMemoryTracer::PrintMemoryBlockAll()
{
	bool remainMemory = false;
	int index = 0;

	String logMessage = "Remain Memory : " + std::to_string(MemoryBlockMap.size()) + " !!! ============================";
	WARN_LOG(logMessage);
	for (const std::pair<const void*, MemoryBlock*>& memoryBlockPair : MemoryBlockMap)
	{
		String message = "Leak #" + std::to_string(index++);
		WARN_LOG(message);

		const MemoryBlock* memoryBlock = memoryBlockPair.second;
		_PrintMemoryBlock(memoryBlock);

		remainMemory = true;
	}
	WARN_LOG("End ==========================================");

#ifdef USE_LOGER
	if(remainMemory)
		_getch();
#endif
}

void CMemoryTracer::_PrintMemoryBlock(const MemoryBlock* InMemoryBlock)
{
	for (size_t i = g_StartCallStackIndex; i < InMemoryBlock->CallStack->GetCount(); ++i)
	{
		if(i > g_MaxCallStackIndex)
			break;;

		String message = Lookup.GetSymbolString((*InMemoryBlock->CallStack)[i]);
		if (!message.empty())
		{
			EMPTY_LOG("#" + std::to_string(i - g_StartCallStackIndex) + " : " + message);
		}
		else
		{
			EMPTY_LOG("#" + std::to_string(i - g_StartCallStackIndex) + " : 알수 없는 외부 코드");
		}
	}
	EMPTY_LOG("");
}
