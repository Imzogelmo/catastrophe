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

#include <Catastrophe/IO/XmlReader.h>
#include <Catastrophe/IO/XmlWriter.h>
#include "StringAlias.h"


StringAlias::StringAlias( const fc::string& name, const fc::string& alias ) :
	name(name),
	alias(alias)
{
}


void StringAlias::SerializeXml( XmlWriter* xml )
{
	xml->SetString("name", name);
	xml->SetString("alias", alias);
}


void StringAlias::DeserializeXml( XmlReader* xml )
{
	name = xml->GetString("name");
	alias = xml->GetString("alias");
}



// StringAliasList

void StringAliasList::AddStringAlias( const fc::string& name, const fc::string& alias )
{
	m_aliasList.push_back( StringAlias(name, alias) );
}

bool StringAliasList::ContainsName( const fc::string& name ) const
{
	for( vec_type::const_iterator it = m_aliasList.begin(); it != m_aliasList.end(); ++it )
		if( it->name == name )
			return true;

	return false;
}

bool StringAliasList::ContainsAlias( const fc::string& alias ) const
{
	for( vec_type::const_iterator it = m_aliasList.begin(); it != m_aliasList.end(); ++it )
		if( it->alias == alias )
			return true;

	return false;
}

bool StringAliasList::GetAlias( const fc::string& name, fc::string& outAlias ) const
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

bool StringAliasList::GetName( const fc::string& alias, fc::string& outName ) const
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

bool StringAliasList::SerializeXml( const fc::string& filename )
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


bool StringAliasList::DeserializeXml( const fc::string& filename )
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

