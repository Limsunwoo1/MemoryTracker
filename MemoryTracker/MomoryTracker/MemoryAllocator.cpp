#include "MemoryAllocator.h"

#ifdef USE_MEMORY_TRACE

extern IMemoryAllocator* GMemoryAllocator = new DefaultMemoryAllocator();

extern IMemoryAllocator* GDefaultMemoryAllocator = GMemoryAllocator;
extern IMemoryAllocator* GCustomMemoryAllocator = new CustomMemoryAllocator();

void SetDefaultMemoryAllocator()
{
	GMemoryAllocator = GDefaultMemoryAllocator;
}

void SetCustomMemoryAllocator()
{
	GMemoryAllocator = GCustomMemoryAllocator;
}

void DestoryMemoryAllocator()
{
	SetDefaultMemoryAllocator();

	if (GCustomMemoryAllocator)
		delete GCustomMemoryAllocator;

	if (GDefaultMemoryAllocator)
		delete GDefaultMemoryAllocator;

	GMemoryAllocator = GDefaultMemoryAllocator = GCustomMemoryAllocator = nullptr;
}

#endif