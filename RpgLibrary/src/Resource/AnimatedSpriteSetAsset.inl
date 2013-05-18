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

/*
void AnimatedSpriteSetAsset::DeserializeXml( XmlReader* xml )
{
	m_preload = true;
	AnimatedSpriteSet::Resize(1);

	xml->NextChild("AnimatedSprite");
		size.x = (float)xml->GetInt("width");
		size.y = (float)xml->GetInt("height");
		scale.x = xml->GetFloat("scale_x", 1.f);
		scale.y = xml->GetFloat("scale_y", 1.f);
		angle = xml->GetFloat("angle");
		color.packed_value = xml->GetUInt("color", Color::White().packed_value);
		blendmode.value = xml->GetUInt("blendmode", BlendMode::Alpha.value);

		xml->NextChild("Animation");
			TextureAsset::m_textureFilename = xml->GetString("texture");
			xml->NextChild("Frame");
				Rect r;
				r.pos.x = xml->GetInt("x");
				r.pos.y = xml->GetInt("y");
				int w = xml->GetInt("w");
				int h = xml->GetInt("h");

				if(w < 32) w = 32;
				else if(w > 32 && w < 48) w = 48;
				if(h < 32) h = 32;
				else if(h > 32 && h < 48) h = 48;

				size.x = w;
				size.y = h;

				r.size.x = w;
				r.size.y = h;

			AnimatedSpriteSet::operator[](0).Create(r);

			xml->SetToParent();
		xml->SetToParent();
	xml->SetToParent();



	Reset();
}
*/

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

