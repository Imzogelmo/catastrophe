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

#include <Catastrophe/Graphics/SpriteBatch.h>
#include "TextEntity.h"


TextEntity::TextEntity( const Vector2& position, const fc::string& text, Font* font, TextAlignment alignment ) :
	Entity(EntityType_TextEntity),
	m_text(text),
	m_font(font),
	m_color(Color::White()),
	m_textAlignment(alignment)
{
	pos = position;
	//todo: set hitbox
}


void TextEntity::Render( SpriteBatch* spriteBatch )
{
	spriteBatch->DrawString(m_font, m_text, pos, m_color, m_textAlignment);
}





