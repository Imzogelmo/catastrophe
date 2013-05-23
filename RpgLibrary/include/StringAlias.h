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


/*
 * Helper classes for parsing or converting
 * strings from one name to another.
 */
class StringAlias
{
public:
	fc::string name;
	fc::string alias;

	StringAlias( const fc::string& name = "", const fc::string& alias = "" );

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

};



class StringAliasList
{
public:
	typedef fc::vector<StringAlias>		vec_type;

	vec_type& GetList() { return m_aliasList; }
	const vec_type& GetList() const { return m_aliasList; }

	void AddStringAlias( const fc::string& name, const fc::string& alias );

	bool ContainsName( const fc::string& name ) const;
	bool ContainsAlias( const fc::string& alias ) const;
	bool GetAlias( const fc::string& name, fc::string& outAlias ) const;
	bool GetName( const fc::string& alias, fc::string& outName ) const;

	NO_INLINE bool SerializeXml( const fc::string& filename );
	NO_INLINE bool DeserializeXml( const fc::string& filename );

protected:
	// keep this a simple vector since it's possible
	// to contain duplicates. this is only moderately slower than
	// multimap for reasonably sized lists anyway.
	vec_type m_aliasList;

};


