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
#include "Tileset.h"
#include "TextureManager.h"



Tileset::Tileset() :
	m_parent(0),
	m_texture(0),
	m_name(),
	m_id(-1),
	m_tiles(),
	m_ptr_animated_tiles()
{
}


Tileset::Tileset( TilesetManager* parent, const fc::string& name ) :
	m_parent(parent),
	m_texture(0),
	m_name(name),
	m_id(-1),
	m_tiles(),
	m_ptr_animated_tiles()
{
}


Tileset::~Tileset()
{
	//Clear();
}


void Tileset::Clear()
{
	m_tiles.resize(0, 0);
	m_ptr_animated_tiles.clear();
}


void Tileset::SetTexture( Texture* texture )
{
	//todo: if texture is ref counted
	m_texture = texture;
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

	size_t size = m_tiles.size();
	for( size_t i(0); i < size; ++i )
	{
		Tile &tile = m_tiles[i];
		tile.SetTileset(this);
		tile.SetIndex(i);
	}
}


gluint Tileset::GetTextureId() const
{
	return m_texture ? m_texture->GetTextureID() : 0;
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


bool Tileset::CreateFromTexture( Texture* texture )
{
	ASSERT(texture != 0);

	const size_t image_w = texture->Width();
	const size_t image_h = texture->Height();
	const size_t tileSize = 16;

	if( image_w < tileSize || image_h < tileSize )
		return false;

	const size_t tw = image_w / tileSize;
	const size_t th = image_h / tileSize;

	SetTexture(texture);
	Resize(tw, th);

	for( size_t y(0); y < th; ++y )
	{
		for( size_t x(0); x < tw; ++x )
		{
			Tile &t = m_tiles(y, x);

	//		t.SetColor(Color::White());
	//		t.animation.SetTexture( image->GetTexture() );

			Rect rect(x * tileSize, y * tileSize, tileSize, tileSize);

			t.Create(rect, 1);
			//t.SetSourceRect(rect);
			//t.animation.AddFrame( image->GetUVRect(rect) );
		}
	}

	return true;
}


bool Tileset::SerializeXml( const fc::string& directory )
{
	fc::string filename = directory + m_filename;
	XmlWriter xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	fc::string textureFilename;
	if( !m_texture )
	{
		//shouldn't really happen.
		Log("Tileset::SerializeXml: (%s) texture is null.", filename.c_str());
	}
	else
	{
		//textureFilename = m_texture->GetFilename(); //todo:
		textureFilename = m_texture->GetName();
	}


	xml.BeginNode("Tileset");
	xml.SetString("name", m_name.c_str());
	xml.SetString("texture", textureFilename.c_str());
	xml.SetUInt("width", m_tiles.x());
	xml.SetUInt("height", m_tiles.y());

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


bool Tileset::DeserializeXml( const fc::string& directory, const fc::string& filename )
{
	Clear();

	//m_name = 
	m_filename = filename;

	fc::string filepath = directory + filename;
	XmlReader xml(filepath);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	if( xml.GetCurrentNodeName() == "Tileset" )
	{
		fc::string textureFilename;

		m_name = xml.GetString("name");
		textureFilename = xml.GetString("texture");
		size_t w = xml.GetUInt("width");
		size_t h = xml.GetUInt("height");

		//we don't handle this in any good way.
		if( textureFilename.empty() )
		{
			Log("Tileset::DeserializeXml: unknown texture");
		}
		else
		{
			SetTexture(0);
			m_texture = g_textureManager->Load(textureFilename);
			if( !m_texture )
			{
				Log("Tileset::DeserializeXml: (%s) texture is null.", filename.c_str());
			}
		}

		m_tiles.resize(h, w);
		ValidateTiles();

		for( array_type::iterator it = m_tiles.begin(); it != m_tiles.end(); ++it )
		{
			if( xml.NextChild("Tile") )
			{
				it->DeserializeXml(&xml);
			}
			else
			{
				break;
			}
		}

		//ValidateTiles();
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

