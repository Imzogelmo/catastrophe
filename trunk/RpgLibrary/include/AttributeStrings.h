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

#include <fc/string.h>

#include "RpgCommon.h"
#include "Attributes.h"


/*
 * AttributeStrings
 * stores strings for all Attribute indices.
 * (For use by editing tools)
 */
class AttributeStrings
{
public:
	String maxParams[MAX_PARAMS];
	String stats[MAX_STATS];
	String elements[MAX_ELEMENTS];
	String status[MAX_STATUS];
	String misc[MAX_MISC];


	// index lookup by name
	bool GetMaxParamIndex( const String& name, u32& index )
	{
		return InternalGetIndex(maxParams, MAX_PARAMS, name, index);
	}

	bool GetStatIndex( const String& name, u32& index )
	{
		return InternalGetIndex(stats, MAX_STATS, name, index);
	}

	bool GetElementIndex( const String& name, u32& index )
	{
		return InternalGetIndex(elements, MAX_ELEMENTS, name, index);
	}

	bool GetStatusIndex( const String& name, u32& index )
	{
		return InternalGetIndex(status, MAX_STATUS, name, index);
	}

	bool GetMiscIndex( const String& name, u32& index )
	{
		return InternalGetIndex(misc, MAX_MISC, name, index);
	}

protected:
	bool InternalGetIndex( const String* ptr, u32 n, const String& name, u32& index )
	{
		for( u32 i(0); i < n; ++i )
		{
			if( name == ptr[i] )
			{
				index = i;
				return true;
			}
		}

		return false;
	}

};
