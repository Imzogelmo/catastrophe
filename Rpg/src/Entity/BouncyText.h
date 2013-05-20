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

#include "TextEntity.h"


class BouncyText : public TextEntity
{
public:
	BouncyText( int lifetime = 120, int bounceHeight = 32, bool stagger = false );

	void Update();
	void Render( SpriteBatch* spriteBatch );

protected:
	int		m_lifetime;
	int		m_age;
	int		m_bounceHeight;
	bool	m_stagger;
	
};



