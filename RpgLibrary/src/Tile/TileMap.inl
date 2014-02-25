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
#include "TileMap.h"



TileMap::TileMap() :
	m_name(),
	m_layers(),
	m_width(0),
	m_height(0)
{
}


TileMap::TileMap( const fc::string& mapName, size_t numLayers, size_t mapWidth, size_t mapHeight ) :
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


void TileMap::Resize( size_t w, size_t h, size_t numLayers )
{
	m_width = w;
	m_height = h;

	if( numLayers == size_t(-1) )
	{
		numLayers = m_layers.size();
	}

	if( numLayers < m_layers.size() )
	{
		for( size_t i(numLayers); i < m_layers.size(); ++i )
			RemoveLayer(i);
	}
	else if( numLayers > m_layers.size() )
	{
		for( size_t i(m_layers.size()); i < numLayers; ++i )
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


void TileMap::RemoveLayer( size_t index )
{
	if( index >= NumLayers() )
		return;

	delete m_layers[index];
	m_layers.erase_at(index);

}


void TileMap::SwapLayer( size_t first, size_t second )
{
	if( first == second || first >= NumLayers() || second >= NumLayers() )
		return;

	fc::swap( m_layers[first], m_layers[second] );
}


TileMapLayer* TileMap::GetLayer( size_t index ) const
{
	if( index < m_layers.size() )
		return m_layers[index];

	return 0;
}


bool TileMap::SerializeXml( const fc::string& filename )
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

	for( size_t i(0); i < m_layers.size(); ++i )
	{
		xml.BeginNode("Layer");
		m_layers[i]->SerializeXml(&xml);
		xml.EndNode();
	}

	xml.EndNode();
	xml.Close();

	return true;
}


bool TileMap::DeserializeXml( const fc::string& filename )
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
		size_t n = xml.GetUInt("num_layers");
		m_width = xml.GetUInt("width");
		m_height = xml.GetUInt("height");

		DeleteLayers();
		m_layers.reserve( fc::clamp<size_t>(n, 0, MaxLayers) );

		while( xml.NextChild("Layer") )
		{
			if( AddLayer() )
			{
				//only deserialize if the layer was added.
				m_layers.back()->DeserializeXml(&xml);
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


