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
#include "Entity.h"


class TextEntity : public Entity
{
public:
	TextEntity( EntityType derivedType = EntityType_TextEntity,
			const fc::string& text = "",
			Font* font = 0,
			TextAlignment alignment = AlignLeft
		);

	void SetFont( Font* font );
	void SetText( const fc::string& text );
	void SetColor( const Color& color ) { m_color = color; }
	void SetTextAlignment( TextAlignment alignment ) { m_textAlignment = alignment; }

	Font* GetFont() const { return m_font; }
	const Color& GetColor() { return m_color; }
	const fc::string& GetText() const { return m_text; }
	TextAlignment GetTextAlignment() const { return m_textAlignment; }

	virtual void Update() {}
	virtual void Render( SpriteBatch* spriteBatch );

protected:
	fc::string		m_text;
	Font*			m_font;
	Color			m_color;
	TextAlignment	m_textAlignment;
	
};



