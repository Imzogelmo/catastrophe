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
#include <Catastrophe/IO/File.h>
#include <Catastrophe/IO/FileBuffer.h>
#include <Catastrophe/IO/LZ4.h>
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
	for( vec_type::iterator it = m_layers.begin(); it != m_layers.end(); ++it )
	{
		delete *it;
	}

	m_layers.clear();
}


void TileMap::Clear()
{
	for( vec_type::iterator it = m_layers.begin(); it != m_layers.end(); ++it )
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

	for( vec_type::iterator it = m_layers.begin(); it != m_layers.end(); ++it )
	{
		(*it)->Resize(w, h);
	}
}



bool TileMap::AddLayer( TileMapLayer* layer )
{
	if( NumLayers() >= MaxLayers )
	{
		Log("TileMap: Unable to add layer.");
		return false;
	}

	if( !layer )
	{
		layer = new TileMapLayer();
	}
	else
	{
		for( vec_type::iterator it = m_layers.begin(); it != m_layers.end(); ++it )
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
	m_layers.push_back(layer);
	return true;
}


void TileMap::RemoveLayer( u32 index )
{
	if( index >= NumLayers() )
		return;

	delete m_layers[index];
	m_layers.erase_at(index);

}


void TileMap::SwapLayer( u32 first, u32 second )
{
	if( first == second || first >= NumLayers() || second >= NumLayers() )
		return;

	fc::swap( m_layers[first], m_layers[second] );
}


TileMapLayer* TileMap::GetLayer( u32 index ) const
{
	if( index < m_layers.size() )
		return m_layers[index];

	return 0;
}


void TileMap::Render( SpriteBatch* spriteBatch, const Rect& viewRect, bool mapWraparound )
{
	for( vec_type::iterator it = m_layers.begin(); it != m_layers.end(); ++it )
	{
		if( (*it)->IsVisible() )
			(*it)->Render(spriteBatch, viewRect, mapWraparound);
	}
}

/*
bool TileMap::Serialize( const String& filename )
{
	XmlWriter xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	xml.BeginNode("TileMap");
	xml.SetString("name", m_name.c_str());
	xml.SetUInt("num_layers", m_layers.size());
	xml.SetUInt("width", m_width);
	xml.SetUInt("height", m_height);

	for( u32 i(0); i < m_layers.size(); ++i )
	{
		xml.BeginNode("Layer");
		m_layers[i]->Serialize(&xml);
		xml.EndNode();
	}

	xml.EndNode();
	xml.Close();

	return true;
}
*/

bool TileMap::Save( const String& path )
{
	// We write directly to memory so we can compress the data
	// with our own custom header.
	FileBuffer fileBuffer;

	File f(path + m_filename, FileWrite);
	if( !f.IsOpen() )
	{
		Log("Could not open file (%s)", (path + m_filename).c_str());
		return false;
	}

	fileBuffer.WriteInt(0); //reserved for future use
	fileBuffer.WriteInt(0); //reserved for future use

	fileBuffer.WriteString(m_name);
	fileBuffer.WriteUInt(m_layers.size());
	fileBuffer.WriteUInt(m_width);
	fileBuffer.WriteUInt(m_height);

	for( u32 i(0); i < m_layers.size(); ++i )
		m_layers[i]->Serialize(&fileBuffer);

	u8* p = new u8[ fileBuffer.Size() ];
	u32 compressedSize = LZ4::CompressData(p, fileBuffer.GetData(), fileBuffer.Size()); 

	f.WriteInt(fileBuffer.Size());
	f.WriteInt(compressedSize);
	f.Write(p, compressedSize);
	f.Close();

	return true;
}



bool TileMap::Load( const String& path, const String& filename )
{
	XmlReader xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	if( xml.GetCurrentNodeName() == "TileMap" )
	{
		m_name = xml.GetString("name");
		u32 n = xml.GetUInt("num_layers");
		m_width = xml.GetUInt("width");
		m_height = xml.GetUInt("height");

		DeleteLayers();
		m_layers.reserve( fc::clamp<u32>(n, 0, MaxLayers) );

		while( xml.NextChild("Layer") )
		{
			if( AddLayer() )
			{
				//only deserialize if the layer was added.
				m_layers.back()->Deserialize(&xml);
			}
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


