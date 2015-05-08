//////////////////////////////////////
// Fast Container Library           //
// MIT License - Copyright (c) 2012 //
//////////////////////////////////////

#pragma once

#include <string.h>

CE_NAMESPACE_BEGIN


namespace Memory
{

	FORCEINLINE void* Memset( void* dest, u8 value, u32 nBytes )
	{
		return ::memset(dest, value, nBytes);
	}

	FORCEINLINE void* Memcpy( void* dest, const void* source, u32 nBytes )
	{
		return ::memcpy(dest, source, nBytes);
	}

	FORCEINLINE void* Memmove( void* dest, const void* source, u32 nBytes )
	{
		return ::memmove(dest, source, nBytes);
	}

	FORCEINLINE int Memcmp( const void* p1, const void* p2, u32 nBytes )
	{
		return ::memcmp(p1, p2, nBytes);
	}

	FORCEINLINE int Memcmp( const void* p1, u32 nBytes1, const void* p2, u32 nBytes2 )
	{
		int returnValue = ::memcmp(p1, p2, (u32)(nBytes1 < nBytes2 ? nBytes1 : nBytes2));
		if( returnValue == 0 && nBytes1 != nBytes2 )
			returnValue = (nBytes1 < nBytes2 ? -1 : 1);

		return returnValue;
	}

	FORCEINLINE int Memcmp( const void* first1, const void* last1, const void* first2, const void* last2 )
	{
		CE_ASSERT(first1 <= last1 && first2 <= last2);

		const int distance1 = int((const char*)last1 - (const char*)first1);
		const int distance2 = int((const char*)last2 - (const char*)first2);

		int returnValue = ::memcmp( first1, first2, (u32)(distance1 < distance2 ? distance1 : distance2) );
		if( returnValue == 0 && distance1 != distance2 )
			returnValue = (distance1 < distance2 ? -1 : 1);

		return returnValue;
	}

	FORCEINLINE const void* Memchr( const void* p, u8 value, u32 nBytes )
	{
		return ::memchr(p, (int)value, nBytes);
	}

	FORCEINLINE const void* Memchr( const void* first, const void* last, u8 value )
	{
		return ::memchr(first, (int)value, (const char*)last - (const char*)first);
	}


	// align

	FORCEINLINE u32 Align( u32 size, u32 alignment = CE_DEFAULT_ALIGN )
	{
		return (alignment > 1) ? ((size + (alignment - 1)) & ~(alignment - 1)) : size;
	}

	FORCEINLINE void* Align( void* p, u32 alignment = CE_DEFAULT_ALIGN )
	{
		return (alignment > 1) ? (void*)(((u32)p + (alignment - 1)) & ~(alignment - 1)) : p;
	}

	FORCEINLINE bool IsAligned( const void* p, u32 alignment = sizeof(void*) )
	{
		return (ptrdiff_t(p) & (alignment - 1)) == 0;
	}

	FORCEINLINE bool IsAligned( u32 value, u32 alignment = sizeof(void*) )
	{
		return (value & (alignment - 1)) == 0;
	}


	// allocation

	extern int allocationCount;
	extern int deallocationCount;

	FORCEINLINE int GetTotalAllocationCount()
	{
		return allocationCount;
	}

	FORCEINLINE int GetTotalDeallocationCount()
	{
		return deallocationCount;
	}

	void* Allocate( u32 nBytes, int alignment = 0 );

	void Deallocate( void* p, u32 nBytes = 0 );

	void* AllocateTemporary( u32 nBytes, int alignment = 0 );

	void DeallocateTemporary( void* p, u32 nBytes = 0 );

	void* AllocateString( u32 nBytes, int flags = 0 );

	void DeallocateString( void* p, u32 nBytes = 0 );

} //Memory



/// Global operator new and delete overrides.

#include <new>

inline void* operator new(size_t size)
{
	return Memory::Allocate((u32)size);
}

inline void operator delete(void* p)
{
	return Memory::Deallocate(p);
}

inline void* operator new[](size_t size)
{
	return Memory::Allocate((u32)size);
}

inline void operator delete[](void* p)
{
	return Memory::Deallocate(p);
}


CE_NAMESPACE_END
