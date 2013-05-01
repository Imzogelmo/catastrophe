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

	Tile( Tileset* parent = 0, size_t id = 0 );

	void SetTileset( Tileset* parent ) { m_parent = parent; } //make protected
	void SetCurrentFrame( short frame );
	void SetAnimationSpeed( short frameDelay );

	void Create( Rect sourceRect, int numberOfFrames = 1 );
	void Update();

	inline short GetCurrentFrame() const { return frame; }
	inline short GetAnimationSpeed() const { return anim_speed; }
	inline short GetFlags() const { return flags; }
	inline short NumFrames() const { return num_frames; }
	inline bool IsAnimated() const { return num_frames > 1; }

	inline Tileset*	GetTileset() const { return m_parent; }

	Texture* GetTexture() const; //depricated
	gluint GetTextureID() const; //depricated

	inline const Rectf&	GetUVRect() const { return m_uv; }

	inline void SetIndex( size_t index ) { m_tilesetIndex = index; }
	inline size_t GetIndex() const { return m_tilesetIndex; }

	NO_INLINE void SerializeXml( XmlWriter* xml );
	NO_INLINE void DeserializeXml( XmlReader* xml );

public:
	short counter;
	short frame;
	short anim_speed;
	short num_frames;

	//todo: flags..
	short flags;
	//16 bit align....

protected:
	Tileset*	m_parent;
	Rect		m_sourceRect;
	Rectf		m_uv;
	size_t		m_tilesetIndex;

private:
	//This value should never change.
	static int m_tileSize; //todo: depricated
};

