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

#include "MapManager.h"
#include "TileMap.h"



MapManager::MapManager()
{
	m_resourceCache.SetManager(this);
	m_resourceCache.SetResourceUsage(4);
}


void MapManager::DisposeResource( void* p )
{
	delete p;
}


TileMap* MapManager::Load( const String& filename, int* id  )
{
	TileMap* map = GetResource(filename, id);
	if( map )
		return map;

	//todo
	map = new TileMap();

	return map;
}





