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
#include "AnimatedSpriteSetAsset.h"
#include "Serialization.h"



AnimatedSpriteSetAsset::AnimatedSpriteSetAsset() :
	AnimatedSpriteSet(),
	TextureAsset()
{
}


bool AnimatedSpriteSetAsset::LoadAnimatedSpriteSet( AnimatedSpriteSet& animatedSpriteSetRef )
{
	Texture* texture = TextureAsset::LoadTexture();
	AnimatedSpriteSet::SetTexture(texture);
	if( !texture )
		return false;

	animatedSpriteSetRef = *this;
	return true;
}


void AnimatedSpriteSetAsset::ReleaseAnimatedSpriteSet()
{
	TextureAsset::ReleaseTexture();
	if( GetRefCount() < 1 )
	{
		AnimatedSpriteSet::SetTexture(0);
	}
}


void AnimatedSpriteSetAsset::SerializeXml( XmlWriter* xml )
{
	//xml->BeginNode("AnimatedSpriteSet");

	size_t count = AnimatedSpriteSet::GetNumAnimations();
	xml->SetUInt("num_animations", count);

	TextureAsset::SerializeXml(xml);
	SerializeObject<SpriteBase>("SpriteBase", xml, *this);

	for( size_t i(0); i < count; ++i )
	{
		SerializeObject<SpriteAnimation>("SpriteAnimation", xml, AnimatedSpriteSet::GetAnimation(i));
	}

	//xml->EndNode();
}


void AnimatedSpriteSetAsset::DeserializeXml( XmlReader* xml )
{
	size_t count = xml->GetUInt("num_animations");

	TextureAsset::DeserializeXml(xml);
	DeserializeObject<SpriteBase>("SpriteBase", xml, *this);
	AnimatedSpriteSet::Resize(count);

	bool nested = false;
	for( size_t i(0); i < count; ++i )
	{
		if( xml->NextChild("SpriteAnimation") )
		{
			DeserializeObject<SpriteAnimation>(xml, AnimatedSpriteSet::GetAnimation(i));
			nested = true;
		}
	}

	if( nested )
		xml->SetToParent();

	Reset();
}

