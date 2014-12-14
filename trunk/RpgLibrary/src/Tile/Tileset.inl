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
#include <Catastrophe/IO/Serializer.h>
#include <Catastrophe/IO/Deserializer.h>
#include <Catastrophe/IO/FileBuffer.h>
#include <Catastrophe/IO/CompressedFile.h>

#include "Tileset.h"
#include "TextureManager.h"



Tileset::Tileset() :
	m_texture(0),
	m_name(),
	m_tileSize(16),
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


void Tileset::SetTileSize( u32 tileSize )
{
	if( tileSize != 0 )
		m_tileSize = tileSize;
}


void Tileset::Resize( u32 w, u32 h )
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

	u32 size = m_tiles.size();
	for( u32 i(0); i < size; ++i )
	{
		Tile &tile = m_tiles[i];
		tile.SetTileset(this);
		tile.SetIndex(i);
	}
}


u32 Tileset::GetTextureId() const
{
	return m_texture ? m_texture->GetTextureID() : 0;
}


Tile* Tileset::GetTile( u32 index ) const
{
	if( index < m_tiles.size() )
		return const_cast<Tile*>(&m_tiles[index]);

	return 0;
}


Tile* Tileset::GetTile( u32 x, u32 y ) const
{
	if( x < m_tiles.x() && y < m_tiles.y() )
		return const_cast<Tile*>(&m_tiles(y, x));

	return 0;
}

/*
bool Tileset::Serialize( const String& directory )
{
	String filename = directory + m_filename;
	XmlWriter xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	String textureFilename;
	if( !m_texture )
	{
		//shouldn't really happen.
		Log("Tileset::Serialize: (%s) texture is null.", filename.c_str());
	}
	else
	{
		//textureFilename = m_texture->GetFilename(); //todo:
		textureFilename = m_texture->GetResourceName();
	}


	xml.BeginNode("Tileset");
	xml.SetString("name", m_name.c_str());
	xml.SetString("texture", textureFilename.c_str());
	xml.SetUInt("width", m_tiles.x());
	xml.SetUInt("height", m_tiles.y());

	for( u32 i(0); i < m_tiles.size(); ++i )
	{
		xml.BeginNode("Tile");
		m_tiles[i].Serialize(&xml);
		xml.EndNode();
	}

	xml.EndNode();
	xml.Close();

	return true;
}
*/

bool Tileset::Save( const String& directory )
{
	if( m_filename.empty() )
	{
		LogError("Cannot save tileset without a valid filename.");
		return false;
	}

	String filename = directory + m_filename;

	FileBuffer f;
	f.Reserve(m_tiles.size() * sizeof(Tile));

	CompressedFile compressedFile(filename, FileWrite);
	if( !compressedFile.IsOpen() )
		return false;

	String textureFilename;
	if( !m_texture )
	{
		//shouldn't really happen.
		Log("Tileset::Serialize: (%s) texture is null.", filename.c_str());
	}
	else
	{
		//textureFilename = m_texture->GetFilename(); //todo:
		textureFilename = m_texture->GetResourceName();
	}

	f.WriteInt(0); //reserved for future use
	f.WriteInt(0); //reserved for future use

	f.WriteString(m_name);
	f.WriteString(textureFilename);
	f.WriteUShort((u16)m_tileSize);
	f.WriteUShort((u16)m_tiles.x());
	f.WriteUShort((u16)m_tiles.y());

	for( u32 i(0); i < m_tiles.size(); ++i )
	{
		m_tiles[i].Serialize(&f);
	}

	compressedFile.Write(f.GetData(), f.Size());
	compressedFile.Close();

	return true;
}


bool Tileset::Load( const String& directory, const String& filename )
{
	Clear();

	CompressedFile f(directory + filename, FileRead);
	if( !f.IsOpen() )
		return false;

	m_filename = filename;

	String textureFilename;
	u16 w = 0;
	u16 h = 0;
	u16 tileSize = 16;

	f.ReadInt(); //reserved for future use
	f.ReadInt(); //reserved for future use

	f.ReadString(m_name);
	f.ReadString(textureFilename);
	f.ReadUShort(tileSize);
	f.ReadUShort(w);
	f.ReadUShort(h);

	m_tileSize = tileSize;
	m_texture = GetTextureManager()->LoadTiles(textureFilename); //fixme:

	// TODO: find a better way to validate filename or path errors...
	// (Theres no issues as long as everything is nice and neatly stored in the root directory though)
	if( m_texture == null )
		GetTextureManager()->Load("", textureFilename);

	if( m_texture == null )
	{
		// There's nothing we can do here; just log it.
		Log("Tileset (%s), could not load texture (%s).", filename.c_str(), textureFilename.c_str());
	}

	m_tiles.resize(h, w);
	ValidateTiles();

	for( array_type::iterator it = m_tiles.begin(); it != m_tiles.end(); ++it )
	{
		it->Deserialize(&f);
	}

	//ValidateTiles();
	ReconfigureAnimatedTileList();
	ResetAnimations();

	return true;
}

/*
bool Tileset::Deserialize( const String& directory, const String& filename )
{
	Clear();

	//m_name = 
	m_filename = filename;

	String filepath = directory + filename;
	XmlReader xml(filepath);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	if( xml.GetCurrentNodeName() == "Tileset" )
	{
		String textureFilename;

		m_name = xml.GetString("name");
		textureFilename = xml.GetString("texture");
		u32 w = xml.GetUInt("width");
		u32 h = xml.GetUInt("height");

		//we don't handle this in any good way.
		if( textureFilename.empty() )
		{
			Log("Tileset::Deserialize: unknown texture");
		}
		else
		{
			SetTexture(0);
			m_texture = g_textureManager->Load(textureFilename);
			if( !m_texture )
			{
				Log("Tileset::Deserialize: (%s) texture is null.", filename.c_str());
			}
		}

		m_tiles.resize(h, w);
		ValidateTiles();

		for( array_type::iterator it = m_tiles.begin(); it != m_tiles.end(); ++it )
		{
			if( xml.NextChild("Tile") )
			{
				it->Deserialize(&xml);
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
*/
