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


#include <Catastrophe/IO/XmlWriter.h>
#include <Catastrophe/IO/XmlReader.h>
#include "SpriteList.h"
#include "Util/Serialization.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                SpriteList
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool SpriteList::SerializeXml( const fc::string& filename )
{
	XmlWriter xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	xml.BeginNode("SpriteList");
	xml.SetUInt("count", m_items.size());

	for( size_t i(0); i < m_items.size(); ++i )
	{
		xml.BeginNode("Sprite");
		Util::SerializeSprite(&xml, m_items[i]);
		xml.EndNode();
	}

	xml.EndNode();
	xml.Close();

	return true;
}


bool SpriteList::DeserializeXml( const fc::string& filename )
{
	XmlReader xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	if( xml.GetCurrentNodeName() == "SpriteList" )
	{
		size_t n = xml.GetUInt("count");
		m_items.clear();
		m_items.reserve(n);

		while( xml.NextChild("Sprite") )
		{
			m_items.push_back();
			Util::DeserializeSprite(&xml, m_items.back());
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


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//             AnimatedSpriteList
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool AnimatedSpriteList::SerializeXml( const fc::string& filename )
{
	XmlWriter xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	xml.BeginNode("AnimatedSpriteList");
	xml.SetUInt("count", m_items.size());

	for( size_t i(0); i < m_items.size(); ++i )
	{
		xml.BeginNode("AnimatedSprite");
		Util::SerializeAnimatedSprite(&xml, m_items[i]);
		xml.EndNode();
	}

	xml.EndNode();
	xml.Close();

	return true;
}


bool AnimatedSpriteList::DeserializeXml( const fc::string& filename )
{
	XmlReader xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	if( xml.GetCurrentNodeName() == "AnimatedSpriteList" )
	{
		size_t n = xml.GetUInt("count");
		m_items.clear();
		m_items.reserve(n);

		while( xml.NextChild("AnimatedSprite") )
		{
			m_items.push_back();
			Util::DeserializeAnimatedSprite(&xml, m_items.back());
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



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//             AnimationSetList
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool AnimationSetList::SerializeXml( const fc::string& filename )
{
	XmlWriter xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	xml.BeginNode("AnimationSetList");
	xml.SetUInt("count", m_items.size());

	for( size_t i(0); i < m_items.size(); ++i )
	{
		xml.BeginNode("AnimationSet");
		Util::SerializeAnimationSet(&xml, m_items[i]);
		xml.EndNode();
	}

	xml.EndNode();
	xml.Close();

	return true;
}


bool AnimationSetList::DeserializeXml( const fc::string& filename )
{
	XmlReader xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	if( xml.GetCurrentNodeName() == "AnimationSetList" )
	{
		size_t n = xml.GetUInt("count");
		m_items.clear();
		m_items.reserve(n);

		while( xml.NextChild("AnimationSet") )
		{
			m_items.push_back();
			Util::DeserializeAnimationSet(&xml, m_items.back());
			xml.SetToParent();
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