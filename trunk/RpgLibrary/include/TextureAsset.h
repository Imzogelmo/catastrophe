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
#include "RpgCommon.h"


class RPG_API TextureAsset
{
public:
	int id;

	TextureAsset();
	~TextureAsset();

	void SetFilename( const String& filename ) { m_textureFilename = filename; }
	const String& GetFilename() const { return m_textureFilename; }

	Texture* LoadTexture();
	void ReleaseTexture();

	void SetPreload( bool enable = true ) { m_preload = enable; }
	int GetPreload() const { return m_preload; }

	// this is called automatically.
	void Reset();
	int GetRefCount() const { return m_refCount; }

	void Serialize( AttributeWriter* f );
	void Deserialize( AttributeReader* f );

	int GetMemoryUsage() const;

protected:
	String			m_textureFilename;
	int					m_textureResourceId;
	int					m_refCount;
	bool				m_preload; //todo
};

