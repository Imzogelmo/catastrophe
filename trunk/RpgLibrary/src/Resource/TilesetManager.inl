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

#include <Catastrophe/Graphics/Texture.h>
#include "TextureManager.h"
#include "TilesetManager.h"
#include "Tileset.h"



TilesetManager::TilesetManager()
{
	m_resourceCache.SetManager(this);
	m_resourceCache.SetResourceUsage(64);
}


TilesetManager::~TilesetManager()
{
	m_resourceCache.DeleteResources();
}


void TilesetManager::DisposeResource( void* p )
{
	Tileset* tileset = (Tileset*)p;
	if( tileset )
	{
		Texture* texture = tileset->GetTexture();
		if( texture )
		{
			g_textureManager->Unload(texture);
		}

		LogDebug("Tileset (%s) unloaded", tileset->GetName().c_str());
		delete tileset;
	}
}


Tileset* TilesetManager::LoadXml( const String& filename, int* id  )
{
	Tileset* tileset = GetResource(filename, id);
	if( tileset )
		return tileset;

	String directory = g_resourceDirectory->GetTilesetDirectory();

	tileset = new Tileset();
	if( !tileset->Deserialize(directory, filename) )
	{
		LogError("Failed to load tileset (%s)", (directory, filename).c_str());
		SAFE_DELETE(tileset);
	}
	else
	{
		LogDebug("Tileset (%s) successfully loaded", (directory, filename).c_str());
		AddResource(tileset, filename, id);
	}

	return tileset;
}





