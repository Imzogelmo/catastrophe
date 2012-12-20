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


class Tile : public Animation
{
public:
	enum TileFlags
	{
		FlipHorizontal	= 1,
		FlipVertical	= 2
	};

	Tileset*	parent;
	size_t		id;
	int			flags;

	Tile( Tileset* parent = 0, size_t id = 0, int flags = 0 ) :
		parent(parent), id(id), flags(flags)
	{}

	void SetTileset( Tileset* tilset ) { parent = tilset; }
	void SetIndex(size_t index) { id = index; }
	void SetFlags(size_t index) { id = index; }

	Tileset* GetTileset() const { return parent; }
	size_t GetIndex() { return id; }
	int GetFlags() { return flags; }

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

};

