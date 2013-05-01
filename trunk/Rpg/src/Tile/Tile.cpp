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


#include <Catastrophe/IO/XmlWriter.h>
#include <Catastrophe/IO/XmlReader.h>
#include "../Util/Serialization.h"
#include "Tile.h"
#include "Tileset.h"


int Tile::m_tileSize = 16;


Tile::Tile( Tileset* parent, size_t id ) :
	counter(0),
	frame(0),
	anim_speed(16),
	flags(0),
	m_parent(parent),
	m_uv(Rectf::Zero)
{
}


Texture* Tile::GetTexture() const
{
	return m_parent->GetTexture();
}


gluint Tile::GetTextureID() const
{
	return m_parent->GetTexture()->GetTextureID();
}


void Tile::Create( Rect sourceRect, int numberOfFrames )
{
	ASSERT(numberOfFrames > 0);
	ASSERT(m_parent != 0);

	Texture* texture = m_parent->GetTexture();
	ASSERT(texture != 0);

	//todo:
}


void Tile::SetCurrentFrame( short index )
{
	if( (size_t)index < m_uv.size() )
		frame = index;
}


void Tile::SetAnimationSpeed( short frameDelay )
{
	anim_speed = fc::clamp<short>(frameDelay, 16, 32767);
}


void Tile::Update()
{
	// animation speed is fixed point 16 : 1. this means
	// that one second (60 frames) is equal to 960 fixed point.
	// therefore the longest animation delay we can have is
	// 34 seconds (2167 - 16 = 2151 frames).
	counter += 16;
	if( counter >= anim_speed )
	{
		counter -= anim_speed;
		if( ++frame >= num_frames )
		{
			frame -= num_frames;
		}
	}
}


void Tile::SerializeXml( XmlWriter* xml )
{
	//set it just in case.
	xml->SetUInt("id", m_tilesetIndex);

	xml->SetUInt("num_frames", num_frames);
	xml->SetShort("speed", anim_speed);
	xml->SetShort("flags", flags);

	Util::SerializeRect("SouceRect", xml, m_sourceRect);
}


void Tile::DeserializeXml( XmlReader* xml )
{
	num_frames = xml->GetInt("num_frames", 1);
	anim_speed = xml->GetShort("speed", 16);
	flags = xml->GetShort("flags", 0);

	Util::DeserializeRect("SouceRect", xml, m_sourceRect);

	//todo: should have tileset create..?
	Create(m_sourceRect, num_frames);
}

