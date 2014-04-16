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

#pragma once

#include <Catastrophe/Common.h>
#include "../Common.h"


class MonoBinding
{
public:

	static void SetNamespace( const char* name );
	static void AddInternalCall( const char* name, const void* method );

protected:
	static char sCurrentMonoBindingNamespaceString[128];
	static int sCurrentMonoBindingNamespaceLength;

};



#define SAFE_CALL(object, function) \
	if(object){ \
		object->function; \
	} else { \
		Log("SAFE_CALL error: trying to reference a null " #object " pointer!\n"); \
	}

#define SAFE_CALL_RETURN(object, function, retval) \
	if(object){ \
		return object->function; \
	} else { \
		Log("SAFE_CALL error: trying to reference a null " #object " pointer!\n"); \
	} \
	return retval

