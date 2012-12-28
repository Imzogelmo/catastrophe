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
#include "Common.h"


class RenderEngine
{
public:
	RenderEngine();



protected:
	//todo implement camera class.
	void DrawMap( const Map* map, const Vector2& pos, const Rect& viewRect );
	void DrawMapLayer( SpriteBatch* spriteBatch, const MapLayer* layer, const Vector2& tilePos, const Rect& viewRect );

};

