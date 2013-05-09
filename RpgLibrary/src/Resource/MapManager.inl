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
#include "Map.h"



MapManager::MapManager()
{
	m_resourceCache.SetManager(this);
	m_resourceCache.SetResourceUsage(4);
}


void MapManager::DisposeResource( void* p )
{
	delete p;
}


Map* MapManager::Load( const fc::string& filename, int* id  )
{
	Map* map = GetResource(filename, id);
	if( map )
		return map;

	//todo
	map = new Map();

	return map;
}





