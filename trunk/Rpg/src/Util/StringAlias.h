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
#include <Catastrophe/IO/XmlReader.h>
#include <Catastrophe/IO/XmlWriter.h>
#include "../Common.h"


/*
 * Helper classes for parsing or converting
 * strings from one name to another.
 */
class StringAlias
{
public:
	fc::string name;
	fc::string alias;

	StringAlias( const fc::string& name = "", const fc::string& alias = "" )
		: name(name), alias(alias)
	{}

	void SerializeXml( XmlWriter* xml )
	{
		xml->SetString("name", name);
		xml->SetString("alias", alias);
	}

	void DeserializeXml( XmlReader* xml )
	{
		name = xml->GetString("name");
		alias = xml->GetString("alias");
	}
};



class StringAliasList
{
public:
	typedef fc::vector<StringAlias>		vec_type;

	vec_type& GetList() { return m_aliasList; }
	const vec_type& GetList() const { return m_aliasList; }

	void AddStringAlias( const fc::string& name, const fc::string& alias )
	{
		m_aliasList.push_back( StringAlias(name, alias) );
	}

	bool ContainsName( const fc::string& name ) const
	{
		for( vec_type::const_iterator it = m_aliasList.begin(); it != m_aliasList.end(); ++it )
			if( it->name == name )
				return true;

		return false;
	}

	bool ContainsAlias( const fc::string& alias ) const
	{
		for( vec_type::const_iterator it = m_aliasList.begin(); it != m_aliasList.end(); ++it )
			if( it->alias == alias )
				return true;

		return false;
	}

	bool GetAlias( const fc::string& name, fc::string& outAlias ) const
	{
		for( vec_type::const_iterator it = m_aliasList.begin(); it != m_aliasList.end(); ++it )
		{
			if( it->name == name )
			{
				outAlias = it->alias;
				return true;
			}
		}

		return false;
	}

	bool GetName( const fc::string& alias, fc::string& outName ) const
	{
		for( vec_type::const_iterator it = m_aliasList.begin(); it != m_aliasList.end(); ++it )
		{
			if( it->alias == alias )
			{
				outName = it->name;
				return true;
			}
		}

		return false;
	}

	bool SerializeXml( const fc::string& filename )
	{
		XmlWriter xml(filename);
		if( !xml.IsOpen() )
		{
			Log("Could not open file (%s)", filename.c_str());
			return false;
		}

		xml.BeginNode("StringAliasList");
		xml.SetUInt("count", m_aliasList.size());

		for( size_t i(0); i < m_aliasList.size(); ++i )
		{
			xml.BeginNode("String");
			m_aliasList[i].SerializeXml(&xml);
			xml.EndNode();
		}

		xml.EndNode();
		xml.Close();

		return true;
	}


	bool DeserializeXml( const fc::string& filename )
	{
		XmlReader xml(filename);
		if( !xml.IsOpen() )
		{
			Log("Could not open file (%s)", filename.c_str());
			return false;
		}

		if( xml.GetCurrentNodeName() == "StringAliasList" )
		{
			size_t n = xml.GetUInt("count");
			m_aliasList.clear();
			m_aliasList.reserve(n);

			while( xml.NextChild("String") )
			{
				m_aliasList.push_back();
				m_aliasList.back().DeserializeXml(&xml);
			}
		}
		else
		{
			Log("Error parsing (%s). Root item not found", filename.c_str());
			return false;
		}

		xml.Close();

		return true;
	}

protected:
	// keep this a simple vector since it's possible
	// to contain duplicates. this is only moderately slower than
	// multimap for reasonably sized lists anyway.
	vec_type m_aliasList;

};


