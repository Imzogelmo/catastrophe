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

#include <Catastrophe/IO/XmlWriter.h>
#include <Catastrophe/IO/XmlReader.h>
#include "SpriteAsset.h"
#include "Serialization.h"



SpriteAsset::SpriteAsset() :
	Sprite(),
	TextureAsset()
{
}


bool SpriteAsset::LoadSprite( Sprite& spriteRef )
{
	Texture* texture = TextureAsset::LoadTexture();
	Sprite::SetTexture(texture);
	if( !texture )
		return false;

	spriteRef = *this;
	return true;
}


void SpriteAsset::ReleaseSprite()
{
	TextureAsset::ReleaseTexture();
	if( GetRefCount() < 1 )
	{
		Sprite::SetTexture(0);
	}
}


void SpriteAsset::SerializeXml( XmlWriter* xml )
{
	TextureAsset::SerializeXml(xml);
	SerializeObject<SpriteBase>("SpriteBase", xml, *this);
}


void SpriteAsset::DeserializeXml( XmlReader* xml )
{
	TextureAsset::DeserializeXml(xml);
	DeserializeObject<SpriteBase>("SpriteBase", xml, *this);
}

