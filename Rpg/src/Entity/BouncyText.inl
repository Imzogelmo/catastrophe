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

#include "BouncyText.h"


BouncyText::BouncyText( int lifetime, int bounceHeight, bool stagger ) :
	TextEntity(EntityType_BouncyText),
	m_lifetime(lifetime),
	m_age(0),
	m_bounceHeight(bounceHeight),
	m_stagger(stagger)
{
}


void BouncyText::Update()
{
	if( ++m_age > m_lifetime )
		alive = false;
}


void BouncyText::Render()
{
	fc::string str;
	TextEntity::Render();



	/*
	float offset = m_font->GetWidth(m_text) / 2.f;
	for( int i(0); i < m_text.size(); ++i )
	{
		char c = m_text[i];
		int x = m_font->GetWidth( m_text.substr(0, i) ) + getX() - offset;
		float t = (m_lifetime - i * 2.f) * 0.15f;

		if( t > 0.f )
		{
			float f1 = 1 - sqr(t - 1);
			float f2 = 0.5f - sqr(t - 1.29289321f);
			float h = fc::max(0.f, f1) * 16;//fc::max(f1, f2)) * 16; //height - 12
			float y = pos.y - h;
			//m_font->DrawGlyph(dest, c, x, y);
		}
	}
	*/

}


