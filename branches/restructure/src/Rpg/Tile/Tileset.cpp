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

#include <Engine/IO/XmlWriter.h>
#include <Engine/IO/XmlReader.h>
#include "Tileset.h"



Tileset::Tileset( TilesetManager* parent, const fc::string& name ) :
	m_parent(parent),
	m_texture(0),
	m_name(name),
	m_id(-1),
	m_tiles(),
	m_ptr_animated_tiles()
{}


Tileset::~Tileset()
{
	//Clear();
}


void Tileset::Clear()
{
	m_tiles.resize(0, 0);
	m_ptr_animated_tiles.clear();
}


void Tileset::Resize( size_t w, size_t h )
{
	m_tiles.resize(h, w);
	ValidateTiles();
	ReconfigureAnimatedTileList();
}


void Tileset::Update()
{
	// we only need to update the animated tiles, not the whole kit 'n kaboodle.
	for( anim_vec_type::iterator it = m_ptr_animated_tiles.begin(); it != m_ptr_animated_tiles.end(); ++it )
	{
		(*it)->Update();
	}
}


void Tileset::ReconfigureAnimatedTileList()
{
	m_ptr_animated_tiles.clear();
	for( array_type::iterator it = m_tiles.begin(); it != m_tiles.end(); ++it )
	{
		if( it->NumFrames() > 1 )
			m_ptr_animated_tiles.push_back(it);
	}
}


void Tileset::ResetAnimations()
{
	for( anim_vec_type::iterator it = m_ptr_animated_tiles.begin(); it != m_ptr_animated_tiles.end(); ++it )
	{
		(*it)->SetCurrentFrame(0);
	}
}


void Tileset::ValidateTiles()
{
	//make sure all tile data is correct.
	//since we do no runtime checks on these later 
	//it's possible to get undefined behavior otherwise.
	for( size_t i(0); i < m_tiles.size(); ++i )
	{
		Tile &tile = m_tiles[i];
		tile.SetTileset(this);
		tile.SetIndex(i);
	}
}


Tile* Tileset::GetTile( size_t index )
{
	if( index < m_tiles.size() )
		return &m_tiles[index];

	return 0;
}


Tile* Tileset::GetTile( size_t x, size_t y )
{
	if( x < m_tiles.x() && y < m_tiles.y() )
		return &m_tiles(y, x);

	return 0;
}


bool Tileset::SerializeXml( const fc::string& directory )
{
	fc::string filename;
	filename.reserve(directory.size() + m_name.size() + 1);
	filename.append(directory).append(m_name);

	XmlWriter xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	//if the texture is null we certainly cannot proceed.
	ASSERT(m_texture);

	xml.BeginNode("Tileset");
	xml.SetString("name", m_name.c_str());
	xml.SetUInt("width", m_tiles.x());
	xml.SetUInt("height", m_tiles.y());
	//texture...

	for( size_t i(0); i < m_tiles.size(); ++i )
	{
		xml.BeginNode("Tile");
		m_tiles[i].SerializeXml(&xml);
		xml.EndNode();
	}

	xml.EndNode();
	xml.Close();

	return true;
}


bool Tileset::DeserializeXml( const fc::string& directory )
{
	fc::string filename;
	filename.reserve(directory.size() + m_name.size() + 1);
	filename.append(directory).append(m_name);

	XmlReader xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	if( xml.GetCurrentNodeName() == "Tileset" )
	{
		m_name = xml.GetString("name");
		size_t w = xml.GetUInt("width");
		size_t h = xml.GetUInt("height");
		//TODO get texture here...

		m_tiles.resize(h, w);
		for( int i(0); xml.NextChild("Tile"); ++i )
		{
			m_tiles[i].DeserializeXml(&xml);
		}

		ValidateTiles();
		ReconfigureAnimatedTileList();
		ResetAnimations();
	}
	else
	{
		Log("Error parsing (%s). Root item not found", filename.c_str());
		return false;
	}

	xml.Close();

	return true;
}

