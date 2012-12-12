
#include "Map.h"



//Map::Map() : m_name(), m_layers(), m_width(0), m_height(0)
//{
//}

Map::Map( const fc::string& mapName, size_t numLayers, size_t mapWidth, size_t mapHeight ) :
	m_name(),
	m_layers(),
	m_width(0),
	m_height(0)
{
}


Map::~Map()
{
	Dispose();
}


void Map::Dispose()
{
	for( vec_type::iterator it = m_layers.begin(); it != m_layers.end(); ++it )
	{
		delete *it;
	}

	m_layers.clear();
}


void Map::Clear()
{
	for( vec_type::iterator it = m_layers.begin(); it != m_layers.end(); ++it )
	{
		(*it)->Clear();
	}
}


void Map::Resize( size_t w, size_t h, size_t numLayers )
{
	if( numLayers = size_t(-1) )
		numLayers = m_layers.size();

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

	m_width = w;
	m_height = h;
	for( vec_type::iterator it = m_layers.begin(); it != m_layers.end(); ++it )
	{
		(*it)->Resize(w, h);
	}
}



bool Map::AddLayer( MapLayer* layer )
{
	if( NumLayers() >= MaxLayers )
	{
		Log("Map: Unable to add layer.");
		return false;
	}

	if( !layer )
	{
		layer = new MapLayer(this);
	}
	else
	{
		for( vec_type::iterator it = m_layers.begin(); it != m_layers.end(); ++it )
		{
			//if it already exists deep copy it.
			if( layer == *it )
			{
				layer = new MapLayer(*(*it));
				//*layer = *(*it);
				break;
			}
		}
	}

	layer->Resize(Width(), Height());
	m_layers.push_back(layer);
	return true;
}


void Map::RemoveLayer( size_t index )
{
	if( index >= NumLayers() )
		return;

	delete m_layers[index];
	m_layers.erase_at(index);
}


void Map::RemoveLayer( MapLayer* layer )
{
	for( vec_type::iterator it = m_layers.begin(); it != m_layers.end(); ++it )
	{
		if( layer == *it )
		{
			RemoveLayer( size_t(it - m_layers.begin()) );
			break;
		}
	}
}


void Map::SwapLayer( size_t first, size_t second )
{
	if( first == second || first >= NumLayers() || second >= NumLayers() )
		return;

	fc::swap( m_layers[first], m_layers[second] );
}


