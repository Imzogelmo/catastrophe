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

#include <fc/string.h>
#include <Catastrophe/IO/AttributeWriter.h>
#include <Catastrophe/IO/AttributeReader.h>

#include "FontAsset.h"
#include "TextureManager.h"


// todo: NOTE* This is just a copy/past of TextureAsset for now.

FontAsset::FontAsset() :
	id(0),
	m_fontFilename(),
	m_fontResourceId(-1),
	m_refCount(0),
	m_preload(false)
{
}


FontAsset::~FontAsset()
{
	if( m_refCount != 0 )
	{
		// ref count should be 0.
		// if not, the program did not interface this class correctly.
		LogError("FontAsset Error: File (%s) : Destructor called with ref count (%i)",
			m_fontFilename.c_str(), m_refCount);
	}
}


Font* FontAsset::LoadFont()
{
	Font* font = 0;
	if( m_fontResourceId < 0 )
	{
		// retrieve by filename
		font = g_fontManager->Load(m_fontFilename, &m_fontResourceId);
	}
	else
	{
		// retrieve by index without increasing count.
		Resource* resource = g_fontManager->GetResourceCache()->GetResource(m_fontResourceId);
		if( resource )
		{
			font = (Font*)resource->ptr;
		}
	}

	if( !font )
	{
		// wtf error.
		LogError("FontAsset::LoadTexture Error: File (%s) : ref count (%i) : null resource!",
			m_fontFilename.c_str(), m_refCount);
		m_refCount--;
	}

	m_refCount++;
	return font;
}


void FontAsset::ReleaseFont()
{
	ASSERT(m_refCount > 0);

	m_refCount--;
	if( m_refCount < 1 )
	{
		m_fontResourceId = -1;
		g_fontManager->Unload(m_fontResourceId);
	}
}


void FontAsset::Reset()
{
	m_refCount = 0;
	m_fontResourceId = -1;
}


void FontAsset::Serialize( AttributeWriter* f )
{
	f->BeginNode("Asset");
	f->SetString("font", m_fontFilename.c_str());
	f->SetBool("preload", m_preload);
	f->EndNode();
}


void FontAsset::Deserialize( AttributeReader* f )
{
	if( f->NextChild("Asset") )
	{
		m_fontFilename = f->GetString("font");
		m_preload = f->GetBool("preload");
		f->SetToParent();
	}

	Reset();
}


int FontAsset::GetMemoryUsage() const
{
	return (int)(m_fontFilename.capacity());
}
