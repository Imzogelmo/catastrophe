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

#include <Catastrophe/Core/IO/File.h>
#include <Catastrophe/Core/IO/MemoryFile.h>
#include <Catastrophe/Core/IO/Compression.h>

#include "Tileset.h"
#include "TextureManager.h"



Tileset::Tileset() :
	m_texture(0),
	m_name(),
	m_tileSize(16),
	m_tiles(),
	m_pAnimatedTiles()
{
}


Tileset::~Tileset()
{
	//Clear();
}


void Tileset::Clear()
{
	m_tiles.Resize(0, 0);
	m_pAnimatedTiles.Clear();
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


void Tileset::Resize( u32 width, u32 height )
{
	m_tiles.Resize(height, width);

	ValidateTiles();
	ReconfigureAnimatedTileList();
}


void Tileset::Update()
{
	// we only need to update the animated tiles, not the whole kit 'n kaboodle.
	for( Vector<Tile*>::Iterator it = m_pAnimatedTiles.begin(); it != m_pAnimatedTiles.end(); ++it )
	{
		(*it)->Update();
	}
}


void Tileset::ReconfigureAnimatedTileList()
{
	m_pAnimatedTiles.Clear();
	for( ArrayType::Iterator it = m_tiles.begin(); it != m_tiles.end(); ++it )
	{
		if( it->NumFrames() > 1 )
			m_pAnimatedTiles.Add(it);
	}
}


void Tileset::ResetAnimations()
{
	for( Vector<Tile*>::Iterator it = m_pAnimatedTiles.begin(); it != m_pAnimatedTiles.end(); ++it )
	{
		(*it)->SetCurrentFrame(0);
	}
}


void Tileset::ValidateTiles()
{
	//make sure all tile data is correct.
	//since we do no runtime checks on these later 
	//it's possible to get undefined behavior otherwise.

	u32 size = m_tiles.Size();
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
	if( index < m_tiles.Size() )
		return const_cast<Tile*>(&m_tiles[index]);

	return 0;
}


Tile* Tileset::GetTile( u32 x, u32 y ) const
{
	if( x < m_tiles.Width() && y < m_tiles.Height() )
		return const_cast<Tile*>(&m_tiles(y, x));

	return 0;
}


bool Tileset::Save( const String& path )
{
	if( m_filename.Empty() )
	{
		LogError("Cannot save tileset without a valid filename.");
		return false;
	}

	String filename = path + m_filename;

	File file(filename, FileWrite);
	if( !file.IsOpen() )
		return false;

	String textureFilename;
	if( !m_texture )
		Log("Tileset::Serialize: (%s) texture is null.", filename.CString());
	else
		textureFilename = m_texture->GetResourceName();

	file.WriteFileID(TILESET_FILE_ID, FILE_ID_LENGTH);
	file.WriteChar(0); // version info
	file.WriteChar(0);

	MemoryFile f;
	f.Reserve(m_tiles.Size() * sizeof(Tile));

	f.WriteString(m_name);
	f.WriteString(textureFilename);
	f.WriteUShort((u16)m_tileSize);
	f.WriteUShort((u16)m_tiles.Width());
	f.WriteUShort((u16)m_tiles.Height());

	//f.WriteInt(0); //reserved for future use
	//f.WriteInt(0); //reserved for future use

	for( u32 i(0); i < m_tiles.Size(); ++i )
	{
		m_tiles[i].Serialize(&f);
	}

	if( !CompressFromMemoryFile(&file, &f) )
		return false;

	file.Close();

	return true;
}


bool Tileset::Load( const String& directory, const String& filename )
{
	Clear();

	File file(directory + filename, FileRead);
	if( !file.IsOpen() )
		return false;

	if( file.ReadFileID(FILE_ID_LENGTH) != TILESET_FILE_ID )
	{
		Log("Could not load file. (%s) is not a valid tileset", filename);
		return false;
	}
	
	file.ReadByte(); // version info
	file.ReadByte();

	m_filename = filename;

	String textureFilename;
	u16 w = 0;
	u16 h = 0;
	u16 tileSize = 16;

	MemoryFile f;
	if( !DecompressToMemoryFile(&f, &file) )
		return false;

	file.Close();

	//f.ReadInt(); //reserved for future use
	//f.ReadInt(); //reserved for future use

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
		m_texture = GetTextureManager()->Load("", textureFilename);

	if( m_texture == null )
	{
		// There's nothing we can do here; just log it.
		Log("Tileset (%s), could not load texture (%s).", filename.CString(), textureFilename.CString());
	}

	m_tiles.Resize((u32)h, (u32)w);
	ValidateTiles();

	for( ArrayType::Iterator it = m_tiles.begin(); it != m_tiles.end(); ++it )
	{
		it->Deserialize(&f);
	}

	//ValidateTiles();
	ReconfigureAnimatedTileList();
	ResetAnimations();

	return true;
}
