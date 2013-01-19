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

#include "Common.h"
#include "Attributes.h"


/*
 * AttributeStrings
 * stores strings for an Attribute object.
 */
class AttributeStrings
{
public:
	fc::string attributes[MAX_ATTRIBUTES];
	fc::string elements[MAX_ELEMENTS];
	fc::string status[MAX_STATUS];

	bool GetAttributeIndex( const fc::string& name, size_t& index )
	{
		return InternalGetIndex(attributes, MAX_ATTRIBUTES, name, index);
	}

	bool GetElementIndex( const fc::string& name, size_t& index )
	{
		return InternalGetIndex(elements, MAX_ELEMENTS, name, index);
	}

	bool GetStatusIndex( const fc::string& name, size_t& index )
	{
		return InternalGetIndex(status, MAX_STATUS, name, index);
	}

protected:
	bool InternalGetIndex( const fc::string* ptr, size_t n, const fc::string& name, size_t& index )
	{
		for( size_t i(0); i < n; ++i )
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
