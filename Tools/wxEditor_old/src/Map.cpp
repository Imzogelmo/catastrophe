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


#include "Precompiled.h"


#include "Map.h"
#include "MapHelper.h"




Map::Map() : m_name(), m_layers(), m_selectedLayer(0), m_width(0), m_height(0)
	{
	}


Map::Map( const wxString& mapName, uint mapWidth, uint mapHeight, uint numLayers )
	: m_name(mapName), m_width(mapWidth), m_height(mapHeight)
	{
		m_selectedLayer = 0;
		//m_layers.reserve( DefaultLayerCapacity );
		m_layers.reserve( 1 );
		Resize( mapWidth, mapHeight, numLayers );
	}



void Map::Clear()
{
	for( vec_type_iter it = m_layers.begin(); it != m_layers.end(); ++it )
		(*it).Clear();
}


void Map::ClearLayer()
{
	ClearLayer( m_selectedLayer );
}


void Map::ClearLayer( uint layer )
{
	if( layer >= NumLayers() || NumLayers() == 1 )
		return;

	m_layers.at(layer).Clear();
}


void Map::Resize( uint w, uint h )
{
	m_width = w;
	m_height = h;
	for( vec_type_iter it = m_layers.begin(); it != m_layers.end(); ++it )
	{
		(*it).Resize(w, h);
	}
}


void Map::Resize( uint w, uint h, uint numLayers )
{
	numLayers = Math::Min( numLayers, MaxLayers );
	m_layers.resize( numLayers );

	Resize(w, h);
	VerifySelectedLayer();
}


void Map::AddLayer()
{
	if( NumLayers() >= MaxLayers )
		return;

	m_layers.push_back( MapLayer() );
	m_layers.back().Resize( Width(), Height() );
}


void Map::AddDuplicateLayer( uint layer )
{
	if( NumLayers() >= MaxLayers )
		return;

	m_layers.push_back( MapLayer() );
	m_layers.back() = m_layers.at(layer);
}


void Map::RemoveLayer()
{
	RemoveLayer( m_selectedLayer );
}


void Map::RemoveLayer( uint layer )
{
	if( layer >= NumLayers() || NumLayers() == 1 )
		return;

	m_layers.erase( m_layers.begin() + layer );
	VerifySelectedLayer();
}


bool Map::IsLayerVisible( uint layer ) const
{
	if( layer >= NumLayers() )
		return false;

	return m_layers[layer].IsVisible();
}


void Map::SetLayerVisibility( uint layer, bool isVisible )
{
	if( layer >= NumLayers() )
		return;

	m_layers[layer].SetVisible(isVisible);
}


void Map::MoveLayerUp()
{
	if( m_selectedLayer == 0 || NumLayers() < 2 )
		return;

	SwapLayer( m_selectedLayer - 1, m_selectedLayer );
	--m_selectedLayer;
}


void Map::MoveLayerDown()
{
	if( m_selectedLayer == NumLayers() - 1 || NumLayers() < 2 )
		return;

	SwapLayer( m_selectedLayer, m_selectedLayer + 1 );
	++m_selectedLayer;
}


void Map::SwapLayer( uint first, uint second )
{
	if( first == second || first >= NumLayers() || second >= NumLayers() )
		return;

	MapLayer::array_type &a = m_layers[first].GetTileArray();
	MapLayer::array_type &b = m_layers[second].GetTileArray();

	const uint size = a.size();
	for( uint i(0); i < size; ++i )
		std::swap( a[i], b[i] );
}


void Map::FlipHorizontally( uint startingLayer, uint numLayers, uint x, uint y, uint width, uint height )
{
	startingLayer	= Math::Min( startingLayer, NumLayers() );
	numLayers		= Math::Min( numLayers, NumLayers() - startingLayer );

	for( uint i(startingLayer); i < numLayers; ++i )
		m_layers[i].FlipHorizontally(x, y, width, height);
}


void Map::FlipVertically( uint startingLayer, uint numLayers, uint x, uint y, uint width, uint height )
{
	startingLayer	= Math::Min( startingLayer, NumLayers() );
	numLayers		= Math::Min( numLayers, NumLayers() - startingLayer );

	for( uint i(startingLayer); i < numLayers; ++i )
		m_layers[i].FlipVertically(x, y, width, height);
}


void Map::VerifySelectedLayer()
{
	assert( NumLayers() > 0 );
	if( m_selectedLayer >= NumLayers() )
		m_selectedLayer = NumLayers() - 1;
}


void Map::Render( SpriteBatch* spriteBatch, wxRect viewRect, uint tileSize )
{
	const int TileSize = int(tileSize);

	wxRect indexRect = MapHelper::SnapToGrid( viewRect, Tile::TileSize );
	indexRect.x /= TileSize;
	indexRect.y /= TileSize;
	indexRect.width /= TileSize;
	indexRect.height /= TileSize;

	ClampIndexRectToMapSize( indexRect );

	for( vec_type_iter it = m_layers.begin(); it != m_layers.end(); ++it )
		(*it).Render( spriteBatch, indexRect, tileSize );
}




void Map::ClampIndexRectToMapSize( wxRect& rect )
{
	const int iw = (int)m_width;
	const int ih = (int)m_height;
	const int maxX = rect.x + rect.width;
	const int maxY = rect.y + rect.height;

	if( rect.x >= iw ) rect.width = 0;
	if( rect.y >= ih ) rect.height = 0;
	
	int diffX = maxX - iw;
	int diffY = maxY - ih;

	if( diffX > 0 && rect.width > 0 )
	{
		rect.width -= diffX;
		if( rect.width < 0 )
			rect.width = 0;
	}
	if( diffY > 0 && rect.height > 0 )
	{
		rect.height -= diffY;
		if( rect.height < 0 )
			rect.height = 0;
	}
}


