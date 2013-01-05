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
#include <fc/vector.h>
#include "Common.h"


class Dialogue
{
public:
	typedef fc::vector<fc::string>	vec_type;

	void AddText( const fc::string& text );
	size_t NumTexts() const { return m_texts.size(); }

	fc::string& GetText( size_t index ) { return m_texts.at(index); }
	const fc::string& GetText( size_t index ) const { return m_texts.at(index); }

protected:
	vec_type	m_texts;
	size_t		m_currentText;
};

