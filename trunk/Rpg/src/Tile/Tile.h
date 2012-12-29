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

#include <fc/fixed_vector.h>

#include "../Common.h"
#include <Catastrophe/Graphics/Animation.h>
#include <Catastrophe/Math/Rectf.h>
#include <Catastrophe/Util/Indexable.h>


/*
 * @Tile (animated tile)
 * 48 bytes + 16 bytes per frame of animation.
 * these are optimized heavily for both cases, and
 * non-animated tiles will never allocate memory.
 */
class RPG_API Tile : public Indexable<> //todo; ..I think index can be safely removed...
{
public:
	typedef fc::fixed_vector<Rectf, 1>	vec_type;
	enum TileFlags
	{
		FlipHorizontal	= 1,
		FlipVertical	= 2
	};

	Tile( Tileset* parent = 0, size_t id = 0 );

	void SetTileset( Tileset* parent ) { m_parent = parent; }
	void SetFrameData( Rect sourceRect, int numberOfFrames = 1 );
	void SetTileSize( int size ) { m_tileSize = size; }
	void SetCurrentFrame( short frame );
	void SetAnimationSpeed( short frameDelay );
	void Update();

	short		GetCurrentFrame() const { return frame; }
	short		GetAnimationSpeed() const { return anim_speed; }
	short		GetFlags() const { return flags; }
	int			GetTileSize() const { return m_tileSize; }
	inline bool IsAnimated() const { return m_uv.has_overflowed(); }
	inline size_t NumFrames() const { return m_uv.size(); }

	inline Tileset*	GetTileset() const { return m_parent; }
	Texture* GetTexture() const;
	gluint GetTextureID() const;
	inline const Rectf&	GetUVRect() const { return m_uv[frame]; }

	NO_INLINE void SerializeXml( XmlWriter* xml );
	NO_INLINE void DeserializeXml( XmlReader* xml );

public:
	short counter;
	short frame;
	short anim_speed;
	short flags;

protected:
	Tileset*	m_parent;
	vec_type	m_uv;

private:
	//This value should never change.
	static int m_tileSize;
};

