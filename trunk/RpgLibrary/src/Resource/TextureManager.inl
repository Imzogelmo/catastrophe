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



TextureManager::TextureManager()
{
	m_resourceCache.SetResourceUsage(256);
}


void TextureManager::DisposeResource( void* p )
{
	Texture* texture = (Texture*)p;
	if( texture )
	{
		texture->Dispose();
		delete texture;
	}
}


Texture* TextureManager::Load( const fc::string& filename, int* id  )
{
	Texture* texture = GetResource(filename, id);
	if( texture )
		return (Texture*)texture;

	// else create a new resource.
	texture = new Texture();

	fc::string fn = g_resourceDirectory->GetTextureDirectory();
	fn += filename;
	if( !texture->LoadFromFile(fn) )
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





