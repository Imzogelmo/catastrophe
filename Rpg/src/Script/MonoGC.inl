
#include <mono/metadata/object.h>
#include <mono/metadata/mono-gc.h>

#include "MonoGC.h"


MonoGC::MonoGC()
{
}


int MonoGC::GetMaxGeneration()
{
	return mono_gc_max_generation();
}


int MonoGC::GetHeapSize()
{
	return (int)mono_gc_get_heap_size();
}


void MonoGC::Collect( int generation )
{
	if( generation < 0 )
		generation = GetMaxGeneration();

	mono_gc_collect(generation);
}

