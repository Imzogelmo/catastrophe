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

#include <Catastrophe/IO/AttributeWriter.h>
#include <Catastrophe/IO/AttributeReader.h>
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


void AnimatedSpriteAsset::SerializeXml( AttributeWriter* f )
{
	//f->BeginNode("AnimatedSprite");

	TextureAsset::SerializeXml(f);
	SerializeObject<SpriteBase>("SpriteBase", f, *this);
	SerializeObject<SpriteAnimation>("SpriteAnimation", f, *this);

	//f->EndNode();
}


void AnimatedSpriteAsset::DeserializeXml( AttributeReader* f )
{
	//if( f->GetNextNode("AnimatedSprite") )
	{
		TextureAsset::DeserializeXml(f);
		DeserializeObject<SpriteBase>("SpriteBase", f, *this);
		DeserializeObject<SpriteAnimation>("SpriteAnimation", f, *this);
	//	f->SetToParent();
	}

}

