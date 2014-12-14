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

#include <Catastrophe/Math/PackedRect.h>
#include <Catastrophe/Math/Rectf.h>

#include "RpgCommon.h"
#include "TileProperties.h"


/*
 * Tile (animated tile)
 */
class RPG_API Tile
{
public:
	enum TileFlags
	{
		FlipHorizontal	= 1,
		FlipVertical	= 2
	};

	Tile( Tileset* parent = null );

	void SetTileset( Tileset* parent ) { m_parent = parent; }
	void SetCurrentFrame( u16 frame );
	void SetAnimationSpeed( u16 frameDelay );
	void SetSourceRect( const PackedRect& sourceRectangle );

	void Create( const PackedRect& sourceRectangle, int numberOfFrames = 1 );
	void Update();

	const PackedRect& GetSourceRect() const { return m_sourceRect; }
	const Rectf& GetUVRect() const { return m_uv; }

	u16 GetCurrentFrame() const { return frame; }
	u16 GetAnimationSpeed() const { return animSpeed; }
	u16 GetFlags() const { return flags; }
	u16 NumFrames() const { return numFrames; }
	bool IsAnimated() const { return numFrames > 1; }

	Tileset* GetTileset() const { return m_parent; }
	Texture* GetParentTexture() const;

	void SetIndex( u32 index ) { m_tilesetIndex = index; }
	u32 GetIndex() const { return m_tilesetIndex; }

	NO_INLINE void Serialize( AttributeWriter* f );
	void Serialize( Serializer* f );
	NO_INLINE void Deserialize( AttributeReader* f );
	void Deserialize( Deserializer* f );

public:
	u16 counter;
	u16 frame;
	u16 animSpeed;
	u16 numFrames;

	//todo: flags..
	u16 flags;
	//16 bit align....

protected:
	Tileset*	m_parent;
	PackedRect	m_sourceRect; // w,h are always tilesize?!
	//PackedRect	m_sourceRect;
	//Vector		m_sCoord;
	//float		m_tCoord
	Rectf		m_uv;
	u32			m_tilesetIndex;

};

