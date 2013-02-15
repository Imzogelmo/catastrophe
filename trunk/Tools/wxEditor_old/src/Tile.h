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

#pragma once


#include "Animation.h"


class Tileset;

class Tile
{
public:
	static const uint TileSize = 16;


	Tile();
	Tile( Tileset* parent );
	Tile( Tileset* parent, const Animation &a, const Color &tint, const Rect& source );
	Tile( const Tile &t );
	~Tile();

	Tile &operator = ( const Tile &t );


	void Draw( SpriteBatch *spriteBatch, const Vector2& pos ) const;
	void Draw( SpriteBatch *spriteBatch, const Rectf& destRect ) const;
	void DrawTransparent( SpriteBatch *spriteBatch, const Vector2& pos, float alphaMul = 0.5f ) const;
	void DrawTransparent( SpriteBatch *spriteBatch, const Rectf& destRect, float alphaMul = 0.5f ) const;


	void SetAnimation( const Animation &a ) { animation = a; }
	void SetTint( const Color &_tint )	{ tint = _tint; }
	void SetSourceRect( const Rect &source ) { sourceRect = source; }


	uint GetThisIndexInTileset() const { return m_index; }
	GLuint GetTexture() const { return animation.GetTexture(); }

	Tileset* GetParentTileset() { return m_parent; }
	const Tileset* GetParentTileset() const { return m_parent; }

protected:
	friend class Tileset;

	void _Draw( SpriteBatch *spriteBatch, const Rectf& destRect, const Color& color ) const;

	Tileset*	m_parent;	// For backwards look-up
	uint		m_index;	// index in the tileset where this tile resides

public:
	Animation	animation;
	Color		tint;
	Rect		sourceRect; // Origin in image. (For tile saving and loading)
};




