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

#include <Catastrophe/Graphics/Font.h>
#include "FontManager.h"



FontManager::FontManager()
{
	m_resourceCache.SetManager(this);
	m_resourceCache.SetResourceUsage(16);
}


FontManager::~FontManager()
{
	m_resourceCache.DeleteResources();
}


void FontManager::DisposeResource( void* p )
{
	Font* font = (Font*)p;
	if( font )
	{
		font->Dispose();
		delete font;
	}
}


Font* FontManager::Load( const String& filename, int* id  )
{
	Font* font = GetResource(filename, id);
	if( font )
		return (Font*)font;

	// else create a new resource.
	font = new Font();

	String path = g_resourceDirectory->GetFontDirectory();
	if( !font->LoadFromFile(path, filename) )
	{
		LogError("Failed to load font (%s)", (path + filename).c_str());
		SAFE_DELETE(font);
	}
	else
	{
		font->SetResourceName(filename);
		AddResource(font, filename, id);
	}

	return font;
}





