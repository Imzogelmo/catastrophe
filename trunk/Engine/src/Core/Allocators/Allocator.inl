//////////////////////////////////////
// Fast Container Library           //
// MIT License - Copyright (c) 2012 //
//////////////////////////////////////

#pragma once

#include "Core/PlatformMemory.h"
#include "Core/Allocators/Allocator.h"

CE_NAMESPACE_BEGIN


void* Allocator::Allocate(u32 nBytes, u32 alignment /*= 0 */)
{
	return Memory::Allocate(nBytes, alignment);
}


void Allocator::Deallocate(void* ptr, u32 size /*= 0 */)
{
	Memory::Deallocate(ptr, size);
}



CE_NAMESPACE_END


