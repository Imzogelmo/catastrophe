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

#include "TileMapManager.h"
#include "TileMap.h"



TileMapManager::TileMapManager()
{
	m_resourceCache.SetManager(this);
	m_resourceCache.SetResourceUsage(4);
}


TileMapManager::~TileMapManager()
{
	m_resourceCache.DeleteResources();
}


void TileMapManager::DisposeResource( void* p )
{
	delete p;
}


TileMap* TileMapManager::Load( const String& filename, int* id  )
{
	TileMap* tilemap = GetResource(filename, id);
	if( tilemap )
		return tilemap;

	tilemap = new TileMap();

	String path = g_resourceDirectory->GetMapDirectory();
	if( !tilemap->Load(path, filename) )
	{
		LogError("Failed to load tilemap (%s)", (path + filename).c_str());
		SAFE_DELETE(tilemap);
	}
	else
	{
		tilemap->SetFileName(filename);
		AddResource(tilemap, filename, id);
	}

	return tilemap;
}





