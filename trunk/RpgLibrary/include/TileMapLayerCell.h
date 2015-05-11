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

#include "Catastrophe/Core/Containers/String.h"
#include "Catastrophe/Core/Containers/Array2D.h"
#include <Catastrophe/Core/Math/Color.h>
#include <Catastrophe/Graphics/BlendMode.h>

#include "Tile.h"

/*
 * @TileMapLayerCell
 * represents an instance of a tile as it 
 * exists inside a layer of a map.
 */
struct TileMapLayerCell
{
	enum Flags
	{
		FlipX = 1,
		FlipY = 2,
		RotateLeft = 4,
		RotateRight = 8
	};

	Tile* tile;
	u16	encounter;
	u8 flags;

	TileMapLayerCell() : tile(0), encounter(0), flags(0)
	{}

	inline operator bool() const { return tile != 0; }
	inline bool Empty() const { return tile == 0; }
	inline void Clear()
	{
		tile = 0;
		flags = 0;
	}

	bool GetFlipX() const { return (flags & FlipX) != 0; }
	bool GetFlipY() const { return (flags & FlipY) != 0; }
	bool GetRotatedLeft() const { return (flags & RotateLeft) != 0; }
	bool GetRotatedRight() const { return (flags & RotateRight) != 0; }

};
