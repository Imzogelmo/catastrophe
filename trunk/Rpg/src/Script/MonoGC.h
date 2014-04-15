
#pragma once

#include "MonoUtils.h"


/// @MonoGC
///
/// Class that encapsulates mono garbage collection routines and
/// handles gc collection cycles.

class MonoGC
{
public:
	MonoGC();

	int GetMaxGeneration();
	int GetHeapSize();

	void Collect( int generation = -1 );

};

