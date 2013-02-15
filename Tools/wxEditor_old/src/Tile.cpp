//////////////////////////////////////////////////////////////////////////
// This program is free software: you can redistribute it and/or modify //
// it under the terms of the GNU General Public License as published by //
// the Free Software Foundation, either version 3 of the License, or    //
// (at your option) any later version.                                  //
//                                                                      //
// This program is distributed in the hope that it will be useful,      //
// but WITHOUT ANY WARRANTY; without even the implied warranty of       //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        //
// GNU General Public License for more details.                         //
//////////////////////////////////////////////////////////////////////////


#include "Precompiled.h"


#include "Tile.h"



Tile::Tile() : 
	animation(), tint(Color::White()), sourceRect(), m_parent(0)
{
}


Tile::Tile( Tileset* parent ) : 
	animation(), tint(Color::White()), sourceRect(), m_parent(parent)
{
}


Tile::Tile( Tileset* parent, const Animation &a, const Color &tint, const Rect& source ) : 
	animation(a), tint(tint), sourceRect(source), m_parent(parent)
{
}


Tile::Tile( const Tile &t ) :
	animation(t.animation), tint(t.tint), sourceRect(t.sourceRect), m_parent(t.m_parent)
{
}


Tile::~Tile()
{
}


Tile &Tile::operator = ( const Tile &t )
{
	animation	= t.animation;
	tint		= t.tint;
	sourceRect	= t.sourceRect;
	m_index		= t.m_index;
	m_parent	= t.m_parent;

	return *this;
}


void Tile::Draw( SpriteBatch *spriteBatch, const Vector2& pos ) const
{
	_Draw(spriteBatch, Rectf(pos, Vector2(float(Tile::TileSize))), tint);
}


void Tile::Draw( SpriteBatch *spriteBatch, const Rectf& destRect ) const
{
	_Draw(spriteBatch, destRect, tint);
}


void Tile::DrawTransparent( SpriteBatch *spriteBatch, const Vector2& pos, float alphaMul ) const
{
	Color transColor( tint.r, tint.g, tint.b, ubyte( float(tint.a) * alphaMul ) );
	_Draw(spriteBatch, Rectf(pos, Vector2(float(Tile::TileSize))), transColor);
}


void Tile::DrawTransparent( SpriteBatch *spriteBatch, const Rectf& destRect, float alphaMul ) const
{
	Color transColor( tint.r, tint.g, tint.b, ubyte( float(tint.a) * alphaMul ) );
	_Draw(spriteBatch, destRect, transColor);
}


__FORCE void Tile::_Draw( SpriteBatch *spriteBatch, const Rectf& destRect, const Color& color ) const
{
	spriteBatch->Draw(
		animation.GetTexture(),
		destRect,
		animation.GetFrameUVRect(),
		color
	);
}



