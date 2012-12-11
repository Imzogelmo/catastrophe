
#pragma once

#include "MapLayer.h"

#include <fc/vector.h>



class TileMap
{
public:
	enum : size_t
	{
		MaxLayers = 16,
		MaxDimension = MapLayer::MaxDimension
	};

	typedef fc::vector<MapLayer*> vec_type;


	TileMap();
	TileMap( const fc::string& mapName, size_t numLayers, size_t mapWidth, size_t mapHeight );

	size_t Size() const { return m_width * m_height; }
	size_t Width() const { return m_width; }
	size_t Height() const { return m_height; }
	size_t NumLayers() const { return m_layers.size(); }

	void Clear();
	void AddLayer( MapLayer* layer );
	void InsertLayer( MapLayer* layer, size_t index );
	void RemoveLayer( MapLayer* layer );
	void RemoveLayer( size_t index = size_t(-1) );
	void Resize( size_t w, size_t h );
	void Resize( size_t w, size_t h, size_t numLayers );

	void SwapLayer( size_t first, size_t second );

	MapLayer* GetLayer( size_t layer ) const;

	fc::string&	GetName() { return m_name; }
	const fc::string& GetName() const { return m_name; }

	void Render( SpriteBatch* spriteBatch, wxRect viewRect, size_t tileSize );

public:
	fc::string		m_name;
	vec_type		m_layers;
	//size_t			m_selectedLayer;
	//CollisionLayer	collisionLayer;
	size_t			m_width;
	size_t			m_height;

};



inline MapLayer* Map::GetActiveLayer()
{
	VerifySelectedLayer();
	return &m_layers[m_selectedLayer];
}


inline const MapLayer* Map::GetActiveLayer() const
{
	if( m_selectedLayer >= m_layers.size() )
		return 0;

	return &m_layers[m_selectedLayer];
}


inline void Map::SetActiveLayer( size_t layer )
{
	if( layer >= m_layers.size() )
		return;

	m_selectedLayer = layer;
}


inline MapLayer *Map::GetLayer( size_t layer )
{
	if( layer >= m_layers.size() )
		return 0;

	return &m_layers[ layer ];
}


inline const MapLayer *Map::GetLayer( size_t layer ) const
{
	if( layer >= m_layers.size() )
		return 0;

	return &m_layers[ layer ];
}
