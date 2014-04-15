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


void AnimatedSpriteSetAsset::SerializeXml( AttributeWriter* f )
{
	//f->BeginNode("AnimatedSpriteSet");

	size_t count = AnimatedSpriteSet::GetNumAnimations();
	f->SetUInt("num_animations", count);

	TextureAsset::SerializeXml(f);
	SerializeObject<SpriteBase>("SpriteBase", f, *this);

	for( size_t i(0); i < count; ++i )
	{
		SerializeObject<SpriteAnimation>("SpriteAnimation", f, AnimatedSpriteSet::GetAnimation(i));
	}

	//f->EndNode();
}

/*
void AnimatedSpriteSetAsset::DeserializeXml( AttributeReader* f )
{
	m_preload = true;
	AnimatedSpriteSet::Resize(1);

	f->NextChild("AnimatedSprite");
		size.x = (float)f->GetInt("width");
		size.y = (float)f->GetInt("height");
		scale.x = f->GetFloat("scale_x", 1.f);
		scale.y = f->GetFloat("scale_y", 1.f);
		angle = f->GetFloat("angle");
		color.packed_value = f->GetUInt("color", Color::White().packed_value);
		blendmode.value = f->GetUInt("blendmode", BlendMode::Alpha.value);

		f->NextChild("Animation");
			TextureAsset::m_textureFilename = f->GetString("texture");
			f->NextChild("Frame");
				Rect r;
				r.pos.x = f->GetInt("x");
				r.pos.y = f->GetInt("y");
				int w = f->GetInt("w");
				int h = f->GetInt("h");

				if(w < 32) w = 32;
				else if(w > 32 && w < 48) w = 48;
				if(h < 32) h = 32;
				else if(h > 32 && h < 48) h = 48;

				size.x = w;
				size.y = h;

				r.size.x = w;
				r.size.y = h;

			AnimatedSpriteSet::operator[](0).Create(r);

			f->SetToParent();
		f->SetToParent();
	f->SetToParent();



	Reset();
}
*/

void AnimatedSpriteSetAsset::DeserializeXml( AttributeReader* f )
{
	size_t count = f->GetUInt("num_animations");

	TextureAsset::DeserializeXml(f);
	DeserializeObject<SpriteBase>("SpriteBase", f, *this);
	AnimatedSpriteSet::Resize(count);

	bool nested = false;
	for( size_t i(0); i < count; ++i )
	{
		if( f->NextChild("SpriteAnimation") )
		{
			DeserializeObject<SpriteAnimation>(f, AnimatedSpriteSet::GetAnimation(i));
			nested = true;
		}
	}

	if( nested )
		f->SetToParent();

	Reset();
}


int AnimatedSpriteSetAsset::GetMemoryUsage() const
{
	return (int)(TextureAsset::GetMemoryUsage() +
		AnimatedSpriteSet::GetAnimationsVector().capacity() * sizeof(SpriteAnimation));
}

