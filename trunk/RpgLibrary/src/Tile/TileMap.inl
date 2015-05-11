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

#include <Catastrophe/Core/IO/XmlWriter.h>
#include <Catastrophe/Core/IO/XmlReader.h>
#include <Catastrophe/Core/IO/File.h>
#include <Catastrophe/Core/IO/MemoryFile.h>
#include <Catastrophe/Core/IO/Compression.h>

#include "TileMap.h"



TileMap::TileMap() :
	m_name(),
	m_layers(),
	m_width(0),
	m_height(0)
{
}


TileMap::TileMap( const String& mapName, u32 numLayers, u32 mapWidth, u32 mapHeight ) :
	m_name(mapName),
	m_layers(),
	m_width(0),
	m_height(0)
{
	Resize(mapWidth, mapHeight, numLayers);
}


TileMap::~TileMap()
{
	DeleteLayers();
}


void TileMap::DeleteLayers()
{
	for( vec_type::Iterator it = m_layers.begin(); it != m_layers.end(); ++it )
	{
		delete *it;
	}

	m_layers.Clear();
}


void TileMap::Clear()
{
	for( vec_type::Iterator it = m_layers.begin(); it != m_layers.end(); ++it )
	{
		(*it)->Clear();
	}
}


void TileMap::Resize( u32 w, u32 h, u32 numLayers )
{
	m_width = w;
	m_height = h;

	if( numLayers == u32(-1) )
	{
		numLayers = m_layers.size();
	}

	if( numLayers < m_layers.size() )
	{
		for( u32 i(numLayers); i < m_layers.size(); ++i )
			RemoveLayer(i);
	}
	else if( numLayers > m_layers.size() )
	{
		for( u32 i(m_layers.size()); i < numLayers; ++i )
			AddLayer();
	}

	for( vec_type::Iterator it = m_layers.begin(); it != m_layers.end(); ++it )
	{
		(*it)->Resize(w, h);
	}
}



TileMapLayer* TileMap::AddLayer( TileMapLayer* layer )
{
	if( NumLayers() >= MaxLayers )
	{
		Log("TileMap: Unable to add layer.");
		return false;
	}

	if( layer == null )
	{
		layer = new TileMapLayer();
	}
	else
	{
		for( vec_type::Iterator it = m_layers.begin(); it != m_layers.end(); ++it )
		{
			//if it already exists deep copy it.
			if( layer == *it )
			{
				layer = new TileMapLayer(*(*it));
				break;
			}
		}
	}

	layer->Resize(Width(), Height());
	m_layers.Add(layer);

	return layer;
}


void TileMap::RemoveLayer( u32 index )
{
	if( index >= NumLayers() )
		return;

	delete m_layers[index];
	m_layers.EraseAt(index);

}


void TileMap::SwapLayer( u32 first, u32 second )
{
	if( first == second || first >= NumLayers() || second >= NumLayers() )
		return;

	Swap( m_layers[first], m_layers[second] );
}


TileMapLayer* TileMap::GetLayer( u32 index ) const
{
	if( index < m_layers.size() )
		return m_layers[index];

	return 0;
}


void TileMap::Render( SpriteBatch* spriteBatch, const Rect& viewRect, bool mapWraparound )
{
	for( vec_type::Iterator it = m_layers.begin(); it != m_layers.end(); ++it )
	{
		if( (*it)->IsVisible() )
			(*it)->Render(spriteBatch, viewRect, mapWraparound);
	}
}


bool TileMap::Save( const String& path )
{
	// Try and create the file handle first just in case.
	File file(path + m_filename, FileWrite);
	if( !file.IsOpen() )
	{
		Log("Could not open file (%s)", (path + m_filename).CString());
		return false;
	}

	file.WriteFileID(TILEMAP_FILE_ID, FILE_ID_LENGTH);
	file.WriteChar(0); // version info
	file.WriteChar(0);

	// We write directly to memory so we can compress the data
	// with our own custom header.
	MemoryFile f;
	f.Reserve(m_layers.size() * m_width * m_height * 32); // best guess

	f.WriteString(m_name);
	f.WriteUInt(m_layers.size());
	f.WriteUInt(m_width);
	f.WriteUInt(m_height);

	//f.WriteInt(0); //reserved for future use
	//f.WriteInt(0); //reserved for future use

	for( u32 i(0); i < m_layers.size(); ++i )
		m_layers[i]->Serialize(&f);

	// Now try to compress and close it
	if( !CompressFromMemoryFile(&file, &f) )
		return false;

	file.Close();

	return true;
}


bool TileMap::Load( const String& path, const String& filename )
{
	File file(path + filename);
	if( !file.IsOpen() )
		return false;

	SetResourceName(filename);

	return Load(&file);
}


bool TileMap::Load(Deserializer* deserializer)
{
	Deserializer& file = *deserializer;

	// Make sure the file is actually a tilemap.
	if( file.ReadFileID(FILE_ID_LENGTH) != TILEMAP_FILE_ID )
	{
		Log("Could not load file. (%s) is not a valid tilemap", filename);
		return false;
	}
	
	file.ReadByte(); // version info
	file.ReadByte();

	MemoryFile f;
	if( !DecompressToMemoryFile(&f, &file) )
		return false;

	u32 numLayers = 0;
	u32 mapWidth = 0;
	u32 mapHeight = 0;

	f.ReadString(m_name);
	f.ReadUInt(numLayers);
	f.ReadUInt(mapWidth);
	f.ReadUInt(mapHeight);

	//f.ReadInt(); //reserved for future use
	//f.ReadInt(); //reserved for future use

	// sanity check
	ASSERT(numLayers <= MaxLayers);
	ASSERT(mapWidth < 65536);
	ASSERT(mapHeight < 65536);

	DeleteLayers();
	m_layers.Reserve(numLayers);

	for( u32 i(0); i < numLayers; ++i )
	{
		TileMapLayer* tileMapLayer = AddLayer();
		tileMapLayer->Deserialize(&f);
	}

	return true;
}


