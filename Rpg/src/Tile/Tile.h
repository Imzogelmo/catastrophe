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

#include "../Common.h"
#include <Catastrophe/Graphics/Animation.h>


//Maybe split this into two tile classes: one for animated..? (memory vs performance cost?)
class Tile : public Animation
{
public:
	enum TileFlags
	{
		FlipHorizontal	= 1,
		FlipVertical	= 2
	};

	//Animation	animation;
	//Color	tint;
	int		flags;

	Tile( Tileset* parent = 0 ) :
		//tint(Color::White()),
		flags(0), m_id(0),
		m_parent(parent)
	{
	}

	//void Update() { animation.Update(); }
	void SetTileset(Tileset* parent) { m_parent = parent; }
	void SetIndex(size_t index) { m_id = index; }

	Tileset* GetTileset() const { return m_parent; }
	size_t GetIndex() { return m_id; }

protected:
	Tileset*	m_parent;
	size_t		m_id;

};

