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
#include "AnimatedSpriteAsset.h"
#include "Serialization.h"



AnimatedSpriteAsset::AnimatedSpriteAsset() :
	AnimatedSprite(),
	TextureAsset()
{
}


bool AnimatedSpriteAsset::LoadAnimatedSprite( AnimatedSprite& animatedSpriteRef )
{
	Texture* texture = TextureAsset::LoadTexture();
	AnimatedSprite::SetTexture(texture);
	if( !texture )
		return false;

	animatedSpriteRef = *this;
	return true;
}


void AnimatedSpriteAsset::ReleaseAnimatedSprite()
{
	TextureAsset::ReleaseTexture();
	if( GetRefCount() < 1 )
	{
		AnimatedSprite::SetTexture(0);
	}
}


void AnimatedSpriteAsset::SerializeXml( XmlWriter* xml )
{
	//xml->BeginNode("AnimatedSprite");

	TextureAsset::SerializeXml(xml);
	SerializeObject<SpriteBase>("SpriteBase", xml, *this);
	SerializeObject<SpriteAnimation>("SpriteAnimation", xml, *this);

	//xml->EndNode();
}


void AnimatedSpriteAsset::DeserializeXml( XmlReader* xml )
{
	//if( xml->GetNextNode("AnimatedSprite") )
	{
		TextureAsset::DeserializeXml(xml);
		DeserializeObject<SpriteBase>("SpriteBase", xml, *this);
		DeserializeObject<SpriteAnimation>("SpriteAnimation", xml, *this);
	//	xml->SetToParent();
	}

}

