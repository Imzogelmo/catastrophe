//////////////////////////////////////
// Fast Container Library           //
// MIT License - Copyright (c) 2012 //
//////////////////////////////////////

#pragma once

#include "Catastrophe/Core/Common.h"

CE_NAMESPACE_BEGIN


/// Allocator
///
/// Simple virtual base Allocator that redirects all Allocate, Deallocate
/// calls to the equivalent global Allocate, Deallocate functions.

class Allocator
{
public:

	/// Allocates raw memory from this allocator.
	///
	/// @param  nBytes - The requested of bytes of memory
	/// @param  alignment - The additional alignment requirements of the memory, if any
	/// @return A pointer to raw block of memory
	///
	virtual void* Allocate( u32 nBytes, u32 alignment = 0 );

	
	/// Allows the allocator reclaim memory that was allocated by this allocator.
	///
	/// @param  ptr - pointer to block of memory
	/// @param  size - the number of bytes of the memory block
	///
	virtual void Deallocate( void* ptr, u32 size = 0 );

	// by default, all allocators are created equal.
	virtual bool operator ==( const Allocator& ) const { return true; }

	/// Allows the allocator pointer to propagate to other containers when copy-constructed.
	virtual bool AllowPropagation() const { return false; }
};



CE_NAMESPACE_END


