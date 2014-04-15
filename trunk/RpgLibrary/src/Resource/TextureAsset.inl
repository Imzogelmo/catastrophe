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

#include "TextureAsset.h"
#include "TextureManager.h"



TextureAsset::TextureAsset() :
	id(0),
	m_textureFilename(),
	m_textureResourceId(-1),
	m_refCount(0),
	m_preload(false)
{
}


TextureAsset::~TextureAsset()
{
	if( m_refCount != 0 )
	{
		// ref count should be 0.
		// if not, the program did not interface this class correctly.
		LogError("TextureAsset Error: File (%s) : Destructor called with ref count (%i)",
			m_textureFilename.c_str(), m_refCount);
	}
}


Texture* TextureAsset::LoadTexture()
{
	Texture* texture = 0;
	if( m_textureResourceId < 0 )
	{
		// retrieve by filename
		texture = g_textureManager->Load(m_textureFilename, &m_textureResourceId);
	}
	else
	{
		// retrieve by index without increasing count.
		Resource* resource = g_textureManager->GetResourceCache()->GetResource(m_textureResourceId);
		if( resource )
		{
			texture = (Texture*)resource->ptr;
		}
	}

	if( !texture )
	{
		// wtf error.
		LogError("TextureAsset::LoadTexture Error: File (%s) : ref count (%i) : null resource!",
			m_textureFilename.c_str(), m_refCount);
		m_refCount--;
	}

	m_refCount++;
	return texture;
}


void TextureAsset::ReleaseTexture()
{
	ASSERT(m_refCount > 0);

	m_refCount--;
	if( m_refCount < 1 )
	{
		m_textureResourceId = -1;
		g_textureManager->Unload(m_textureResourceId);
	}
}


void TextureAsset::Reset()
{
	m_refCount = 0;
	m_textureResourceId = -1;
}


void TextureAsset::SerializeXml( AttributeWriter* f )
{
	f->BeginNode("Asset");
	f->SetString("texture", m_textureFilename.c_str());
	f->SetBool("preload", m_preload);
	f->EndNode();
}


void TextureAsset::DeserializeXml( AttributeReader* f )
{
	if( f->NextChild("Asset") )
	{
		m_textureFilename = f->GetString("texture");
		m_preload = f->GetBool("preload");
		f->SetToParent();
	}

	Reset();
}


int TextureAsset::GetMemoryUsage() const
{
	return (int)(m_textureFilename.capacity());
}
