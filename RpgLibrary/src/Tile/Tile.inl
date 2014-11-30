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
#include <Catastrophe/IO/AttributeWriter.h>
#include <Catastrophe/IO/AttributeReader.h>

#include "Serialization.h"
#include "Tile.h"
#include "Tileset.h"



Tile::Tile( Tileset* parent ) :
	counter(0),
	frame(0),
	animSpeed(128),
	numFrames(1),
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
	numFrames = (s16)(numberOfFrames > 0 ? numberOfFrames : 1);
	SetSourceRect(sourceRectangle);
}


void Tile::SetSourceRect( const Rect& sourceRectangle )
{
	m_sourceRect = sourceRectangle;
	Texture* texture = GetParentTexture();
	if( texture )
	{
		float h = texture->Heightf();
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


void Tile::SetCurrentFrame( s16 index )
{
	if( index < numFrames )
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
			float texHeightf = texture->Heightf();
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


void Tile::SetAnimationSpeed( s16 frameDelay )
{
	animSpeed = fc::clamp<s16>(frameDelay, 16, 32767);
}


void Tile::Update()
{
	// Animation speed is fixed point 16 : 1. this means
	// that one second (60 frames) is equal to 960 fixed point.
	// Therefore, the longest animation delay we can have is
	// 34 seconds (2167 - 16 = 2151 frames).

	/*
	counter += 16;
	if( counter >= animSpeed )
	{
		counter -= animSpeed;
		if( ++frame >= numFrames )
			frame -= numFrames;

		SetCurrentFrame(frame);
	}
	*/

	counter += 16;
	if( counter >= animSpeed )
	{
		counter -= animSpeed;

		// Animation Loop
		if( (flags & TileFlag_AnimationPingPong) == 0 )
			frame = (frame + 1) % numFrames;

		// Animation PingPong
		else if( numFrames > 1 )
		{
			// Backwards
			if( (flags & TileFlag_InternalReverseDirection) != 0 )
			{
				if( frame == 0 )
				{
					++frame;
					flags ^= TileFlag_InternalReverseDirection;
				}
				else
					--frame;
			}

			// Forwards
			else
			{
				if( frame == numFrames - 1 )
				{
					--frame;
					flags ^= TileFlag_InternalReverseDirection;
				}
				else
					++frame;

			}
		}

		SetCurrentFrame(frame);
	}
}


void Tile::Serialize( AttributeWriter* f )
{
	//set it just in case.
	f->SetUInt("id", m_tilesetIndex);

	f->SetUInt("numFrames", numFrames);
	f->SetShort("speed", animSpeed);
	f->SetShort("flags", flags);

	//Todo: fix this
	SerializeObject<Rect>("SouceRect", f, m_sourceRect);
}


void Tile::Deserialize( AttributeReader* f )
{
	numFrames = f->GetShort("numFrames", 1);
	animSpeed = f->GetShort("speed", 16);
	flags = f->GetShort("flags", 0);

	DeserializeObject<Rect>("SouceRect", f, m_sourceRect);

	//todo: should have tileset create..?
	Create(m_sourceRect, numFrames);
}

