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
#include <Catastrophe/Graphics/AnimatedSpriteSet.h>

#include "RpgCommon.h"
#include "TextureAsset.h"


class RPG_API AnimatedSpriteSetAsset : public AnimatedSpriteSet, public TextureAsset
{
public:
	AnimatedSpriteSetAsset();

	bool LoadAnimatedSpriteSet( AnimatedSpriteSet& animatedSpriteSetRef );
	void ReleaseAnimatedSpriteSet();

	void SerializeXml( AttributeWriter* f );
	void DeserializeXml( AttributeReader* f );

};




