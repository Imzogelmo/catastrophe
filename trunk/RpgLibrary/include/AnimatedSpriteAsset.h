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
#include <Catastrophe/Graphics/Sprite.h>

#include "RpgCommon.h"
#include "TextureAsset.h"


class RPG_API AnimatedSpriteAsset : public AnimatedSprite, public TextureAsset
{
public:
	AnimatedSpriteAsset();

	bool LoadAnimatedSprite( AnimatedSprite& animatedSpriteRef );
	void ReleaseAnimatedSprite();

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

};



