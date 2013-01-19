//////////////////////////////////////////////////////////////////////////
// This program is free software: you can redistribute it and/or modify //
// it under the terms of the GNU General Public License as published by //
// the Free Software Foundation, either version 3 of the License, or    //
// (at your option) any later version.                                  //
//                                                                      //
// This program is distributed in the hope that it will be useful,      //
// but WITHOUT ANY WARRANTY; without even the implied warranty of       //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        //
// GNU General Public License for more details.                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "MapLayer.h"
#include "CollisionLayer.h"

#include <fc/vector.h>



class Map
{
public:
	static const uint DefaultLayerCapacity = 4;
	static const uint MaxLayers = 16;
	static const uint MaxDimension = MapLayer::MaxDimension;


	typedef fc::vector<MapLayer> vec_type;
	typedef vec_type ::iterator vec_type_iter;

	Map();
	Map( const wxString& mapName, uint mapWidth, uint mapHeight, uint numLayers );


	uint Width() const { return m_width; }
	uint Height() const { return m_height; }
	uint NumLayers() const { return m_layers.size(); }

	bool IsLayerVisible( uint layer ) const;
	void SetLayerVisibility( uint layer, bool isVisible );

	void Clear();
	void ClearLayer();
	void ClearLayer( uint layer );
	void AddLayer();
	void AddDuplicateLayer( uint layer );
	void RemoveLayer();
	void RemoveLayer( uint layer );
	void Resize( uint w, uint h );
	void Resize( uint w, uint h, uint numLayers );
	void Rename( const wxString& mapName ) { m_name = mapName; }
	void ClampIndexRectToMapSize( wxRect& rect );

	//void Replace();
	void MoveLayerUp();
	void MoveLayerDown();
	void SwapLayer( uint first, uint second );
	void FlipHorizontally( uint startingLayer = 0, uint numLayers = MaxLayers, uint x = 0, uint y = 0, uint width = MaxDimension, uint height = MaxDimension );
	void FlipVertically( uint startingLayer = 0, uint numLayers = MaxLayers, uint x = 0, uint y = 0, uint width = MaxDimension, uint height = MaxDimension );
	void VerifySelectedLayer();



	// getters, setters
	void		SetActiveLayer( uint layer );
	uint		GetActiveLayerIndex() const { return m_selectedLayer; }

	MapLayer*			GetLayer( uint layer );
	const MapLayer*		GetLayer( uint layer ) const;
	MapLayer*			GetActiveLayer();
	const MapLayer*		GetActiveLayer() const;
	wxString&		GetName() { return m_name; }
	const wxString&	GetName() const { return m_name; }

	void Render( SpriteBatch* spriteBatch, wxRect viewRect, uint tileSize );

public:
	wxString		m_name;
	vec_type		m_layers;
	uint			m_selectedLayer;
	CollisionLayer	collisionLayer;
	uint			m_width;
	uint			m_height;

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


inline void Map::SetActiveLayer( uint layer )
{
	if( layer >= m_layers.size() )
		return;

	m_selectedLayer = layer;
}


inline MapLayer *Map::GetLayer( uint layer )
{
	if( layer >= m_layers.size() )
		return 0;

	return &m_layers[ layer ];
}


inline const MapLayer *Map::GetLayer( uint layer ) const
{
	if( layer >= m_layers.size() )
		return 0;

	return &m_layers[ layer ];
}



