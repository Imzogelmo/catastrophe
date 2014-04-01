// catastrophe rpg engine
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

#include "Common.h"
#include <malloc.h>


//#include <fc/fixed_memory_pool.h>
//fc::fixed_memory_pool<509612> scriptMemPool;

size_t __total_mem = 0;
void* gScriptMemStack = 0;
int gScriptMemStackIndex = 0;


void* ScriptMemoryAlloc( size_t n )
{
	__total_mem += n;
	//LogInfo("---Info : Script Alloc : bytes (%i), total kbytes(%i).", n, (__total_mem / 1024));

	if( !gScriptMemStack )
	{
	//	gScriptMemStack = malloc(1024*1024*8);
	}

	//int u = gScriptMemStackIndex;
	//gScriptMemStackIndex = fc::align(gScriptMemStackIndex + n);
	//return (void*)((char*)gScriptMemStack + gScriptMemStackIndex);

	return malloc(n);

	//return scriptMemPool.allocate(n);
}


void ScriptMemoryFree( void* ptr )
{
	//LogInfo("---Info : Script Memory Free.");

	//scriptMemPool.deallocate(ptr);


	free(ptr);
}

