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
#include <Catastrophe/IO/XmlWriter.h>
#include <Catastrophe/IO/XmlReader.h>

#include "Serialization.h"
#include "Tile.h"
#include "Tileset.h"


int Tile::m_tileSize = 16;


Tile::Tile( Tileset* parent ) :
	counter(0),
	frame(0),
	anim_speed(128),
	flags(0),
	m_parent(parent),
	m_sourceRect(Rect::Zero),
	m_uv(Rectf::Zero)
{
}


Texture* Tile::GetParentTexture() const
{
	return (m_parent ? m_parent->GetTexture() : 0);
}


void Tile::Create( const Rect& sourceRectangle, int numberOfFrames )
{
	num_frames = (short)(numberOfFrames > 0 ? numberOfFrames : 1);
	SetSourceRect(sourceRectangle);
}


void Tile::SetSourceRect( const Rect& sourceRectangle )
{
	m_sourceRect = sourceRectangle;
	Texture* texture = GetParentTexture();
	if( texture )
	{
		float h = (float)texture->Height();
		m_uv.min.y = (float)sourceRectangle.Top() / h;
		m_uv.max.y = (float)sourceRectangle.Bottom() / h;

		if( flags & FlipVertical )
			fc::swap(m_uv.min.y, m_uv.max.y);

		if( frame > 0 )
		{
			SetCurrentFrame(frame);
		}
		else
		{
			float w = (float)texture->Width();
			m_uv.min.x = (float)sourceRectangle.Left() / w;
			m_uv.max.x = (float)sourceRectangle.Right() / w;

			if( flags & FlipHorizontal )
				fc::swap(m_uv.min.x, m_uv.max.x);
		}
	}
}


void Tile::SetCurrentFrame( short index )
{
	if( index < num_frames )
	{
		frame = index;

		Texture* texture = GetParentTexture();
		if( !texture )
			return;

		int w = m_sourceRect.Width();
		int x = m_sourceRect.pos.x + (w * (int)frame);
		int yOffset = x / texture->Width();
		if( yOffset > 0 )
		{
			x %= texture->Width();

			int h = m_sourceRect.Height();
			int y = m_sourceRect.pos.y + (h * yOffset);
			float texHeightf = (float)texture->Height();
			m_uv.min.y = y / texHeightf;
			m_uv.max.y = (y + h) / texHeightf;

			if( flags & FlipVertical )
				fc::swap(m_uv.min.y, m_uv.max.y);
		}

		float texWidthf = (float)texture->Width();
		m_uv.min.x = x / texWidthf;
		m_uv.max.x = (x + w) / texWidthf;

		if( flags & FlipHorizontal )
			fc::swap(m_uv.min.x, m_uv.max.x);
	}
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

		SetCurrentFrame(frame);
	}
}


void Tile::SerializeXml( XmlWriter* xml )
{
	//set it just in case.
	xml->SetUInt("id", m_tilesetIndex);

	xml->SetUInt("num_frames", num_frames);
	xml->SetShort("speed", anim_speed);
	xml->SetShort("flags", flags);

	SerializeObject<Rect>("SouceRect", xml, m_sourceRect);
}


void Tile::DeserializeXml( XmlReader* xml )
{
	num_frames = xml->GetShort("num_frames", 1);
	anim_speed = xml->GetShort("speed", 16);
	flags = xml->GetShort("flags", 0);

	DeserializeObject<Rect>("SouceRect", xml, m_sourceRect);

	//todo: should have tileset create..?
	Create(m_sourceRect, num_frames);
}

