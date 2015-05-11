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

#include <Catastrophe/Core/Containers/String.h>
#include <Catastrophe/Core/Containers/Vector.h>
#include "RpgCommon.h"


/*
 * Helper classes for parsing or converting
 * strings from one name to another.
 */
class StringAlias
{
public:
	String name;
	String alias;

	StringAlias( const String& name = "", const String& alias = "" );

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

};



class StringAliasList
{
public:
	typedef Vector<StringAlias>		vec_type;

	vec_type& GetList() { return m_aliasList; }
	const vec_type& GetList() const { return m_aliasList; }

	void AddStringAlias( const String& name, const String& alias );

	bool ContainsName( const String& name ) const;
	bool ContainsAlias( const String& alias ) const;
	bool GetAlias( const String& name, String& outAlias ) const;
	bool GetName( const String& alias, String& outName ) const;

	NOINLINE bool SerializeXml( const String& filename );
	NOINLINE bool DeserializeXml( const String& filename );

protected:
	// keep this a simple vector since it's possible
	// to contain duplicates. this is only moderately slower than
	// multimap for reasonably sized lists anyway.
	vec_type m_aliasList;

};


