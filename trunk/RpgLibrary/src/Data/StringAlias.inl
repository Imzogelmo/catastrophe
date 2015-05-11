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

#include <Catastrophe/Core/IO/XmlReader.h>
#include <Catastrophe/Core/IO/XmlWriter.h>
#include "StringAlias.h"


StringAlias::StringAlias( const String& name, const String& alias ) :
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
	xml->GetString("name", name);
	xml->GetString("alias", alias);
}



// StringAliasList

void StringAliasList::AddStringAlias( const String& name, const String& alias )
{
	m_aliasList.Add( StringAlias(name, alias) );
}

bool StringAliasList::ContainsName( const String& name ) const
{
	for( vec_type::ConstIterator it = m_aliasList.begin(); it != m_aliasList.end(); ++it )
		if( it->name == name )
			return true;

	return false;
}

bool StringAliasList::ContainsAlias( const String& alias ) const
{
	for( vec_type::ConstIterator it = m_aliasList.begin(); it != m_aliasList.end(); ++it )
		if( it->alias == alias )
			return true;

	return false;
}

bool StringAliasList::GetAlias( const String& name, String& outAlias ) const
{
	for( vec_type::ConstIterator it = m_aliasList.begin(); it != m_aliasList.end(); ++it )
	{
		if( it->name == name )
		{
			outAlias = it->alias;
			return true;
		}
	}

	return false;
}

bool StringAliasList::GetName( const String& alias, String& outName ) const
{
	for( vec_type::ConstIterator it = m_aliasList.begin(); it != m_aliasList.end(); ++it )
	{
		if( it->alias == alias )
		{
			outName = it->name;
			return true;
		}
	}

	return false;
}

bool StringAliasList::SerializeXml( const String& filename )
{
	XmlWriter xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	xml.BeginNode("StringAliasList");
	xml.SetAttribute("count", m_aliasList.Size());

	for( size_t i(0); i < m_aliasList.Size(); ++i )
	{
		xml.BeginNode("String");
		m_aliasList[i].SerializeXml(&xml);
		xml.EndNode();
	}

	xml.EndNode();
	xml.Close();

	return true;
}


bool StringAliasList::DeserializeXml( const String& filename )
{
	XmlReader xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	if( xml.GetCurrentNodeName() == "StringAliasList" )
	{
		size_t n = 0;
		xml.GetAttribute("count", n);
		m_aliasList.Clear();
		m_aliasList.Reserve(n);

		while( xml.NextChild("String") )
		{
			m_aliasList.Add();
			m_aliasList.Back().DeserializeXml(&xml);
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

