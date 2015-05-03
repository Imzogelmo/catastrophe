//////////////////////////////////////
// Fast Container Library           //
// MIT License - Copyright (c) 2012 //
//////////////////////////////////////

#pragma once

#include "Catastrophe/Core/Common.h"
#include "Catastrophe/Core/Memory.h"

CE_NAMESPACE_BEGIN



class StackAllocator
{
public:
	StackAllocator();
	StackAllocator( void* ptrMemory, u32 nBytes );

	void InitializeMemory( void* ptrMemory, u32 nBytes );

	/// Request memory from the top of the internal memory stack.
	///
	/// @param  nBytes - The requested of bytes of memory
	/// @param  alignment - The additional alignment requirements of the memory, if any
	/// @return A pointer to raw block of memory, or null if there is not enough memory (May assert)
	///
	void* Allocate( u32 nBytes, u32 alignment = 0 );

	/// Check whether this stack can handle an allocation request of nBytes bytes.
	/// @return false if this stack is out-of-memory.
	bool CanAllocate( u32 nBytes ) const;

	/// Returns the total size in bytes of this stack.
	u32 Capacity() const { return u32(m_end - m_begin); }

	/// Gets the pointer to the current top of the stack.
	const void* GetCurrentPosition() const
	{
		return m_current;
	}

	/// Unwind the stack ptr to a previos position aquired by GetCurrentPosition().
	/// Note: Unwinding the stack must be done in the reverse order in which they are allocated.
	void Unwind(const void* ptrStackPosition);

protected:
	u8* m_begin;
	u8* m_end;
	u8* m_current;

};



CE_NAMESPACE_END

