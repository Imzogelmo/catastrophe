
#include "Map.h"



//Map::Map() : m_name(), m_layers(), m_selectedLayer(0), m_width(0), m_height(0)
//{
//}

Map::Map( const fc::string& mapName, size_t numLayers, size_t mapWidth, size_t mapHeight ) :
	m_name(),
	m_layers(),
	m_width(0),
	m_height(0)
{
}


void Map::Clear()
{
	for( vec_type::iterator it = m_layers.begin(); it != m_layers.end(); ++it )
		(*it)->Clear();
}


void Map::Resize( size_t w, size_t h )
{
	m_width = w;
	m_height = h;
	for( vec_type::iterator it = m_layers.begin(); it != m_layers.end(); ++it )
	{
		(*it)->Resize(w, h);
	}
}


void Map::Resize( size_t w, size_t h, size_t numLayers )
{
	numLayers = fc::clamp( numLayers, 0, MaxLayers );

	//if new layer size is less, then we have to free memory.
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

	Resize(w, h);
}



void Map::AddLayer()
{
	if( NumLayers() >= MaxLayers )
		return;

	MapLayer* layer = new MapLayer(this);
	layer->Resize( Width(), Height() );
	m_layers.push_back(layer);
}


void Map::RemoveLayer( size_t layer )
{
	if( layer >= NumLayers() )
		return;

	delete m_layers[i];
	m_layers.erase_at(i);
}


void Map::SwapLayer( size_t first, size_t second )
{
	if( first == second || first >= NumLayers() || second >= NumLayers() )
		return;

	fc::swap( m_layers[first], m_layers[second] );
}


