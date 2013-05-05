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

#pragma once

#include "TextureManager.h"



TextureManager::TextureManager()
{
	m_resourceCache.SetResourceUsage(256);
}


void TextureManager::DisposeResource( void* p )
{
	delete p;
}


Texture* TextureManager::Load( const fc::string& filename, int* id  )
{
	Resource* resource = GetResource(filename, id);
	if( resource )
		return (Texture*)resource->ptr;

	// else create a new resource.
	Texture* texture = new Texture();

	fc::string fn = GetTextureDirectory(fn) + filename;
	if( !texture->Load(fn) )
	{
		LogError("Failed to load texture (%s)", fn.c_str());
		SAFE_DELETE(texture);
	}
	else
	{
		texture->SetName(filename);
		AddResource(texture, filename, id);
	}

	return texture;
}





