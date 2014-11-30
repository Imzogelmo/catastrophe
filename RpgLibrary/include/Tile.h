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

#include <Catastrophe/Math/Rect.h>
#include <Catastrophe/Math/Rectf.h>

#include "RpgCommon.h"


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

	Tile( Tileset* parent = 0 );

	void SetTileset( Tileset* parent ) { m_parent = parent; } //make protected
	void SetCurrentFrame( s16 frame );
	void SetAnimationSpeed( s16 frameDelay );
	void SetSourceRect( const Rect& sourceRectangle );

	void Create( const Rect& sourceRectangle, int numberOfFrames = 1 );
	void Update();

	inline const Rect& GetSourceRect() const { return m_sourceRect; }
	inline s16 GetCurrentFrame() const { return frame; }
	inline s16 GetAnimationSpeed() const { return animSpeed; }
	inline s16 GetFlags() const { return flags; }
	inline s16 NumFrames() const { return numFrames; }
	inline bool IsAnimated() const { return numFrames > 1; }

	inline Tileset*	GetTileset() const { return m_parent; }
	inline const Rectf&	GetUVRect() const { return m_uv; }

	Texture* GetParentTexture() const;

	inline void SetIndex( u32 index ) { m_tilesetIndex = index; }
	inline u32 GetIndex() const { return m_tilesetIndex; }

	NO_INLINE void Serialize( AttributeWriter* f );
	NO_INLINE void Deserialize( AttributeReader* f );

public:
	s16 counter;
	s16 frame;
	s16 animSpeed;
	s16 numFrames;

	//todo: flags..
	s16 flags;
	//16 bit align....

protected:
	Tileset*	m_parent;
	Rect		m_sourceRect; // w,h are always tilesize?!
	//PackedRect	m_sourceRect;
	//Vector		m_sCoord;
	//float		m_tCoord
	Rectf		m_uv;
	u32			m_tilesetIndex;

};

