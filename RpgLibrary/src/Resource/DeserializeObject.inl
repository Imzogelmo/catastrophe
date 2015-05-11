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

#include <Catastrophe/Core/IO/AttributeReader.h>
#include <Catastrophe/Core/Math/Point.h>
#include <Catastrophe/Core/Math/Rect.h>
#include <Catastrophe/Graphics/SpriteAnimation.h>
#include <Catastrophe/Graphics/AnimatedSpriteSet.h>
#include <Catastrophe/Graphics/Sprite.h>

#include "Serialization.h"
#include "TextureManager.h"




template <class T>
void DeserializeObject( const char* nodeName, AttributeReader* f, T& value )
{
	if( f->NextChild(nodeName) )
	{
		DeserializeObject<T>(f, value);
		f->SetToParent();
	}
}


template <>
void DeserializeObject<Point>( AttributeReader* f, Point& value )
{
	f->GetAttribute("x", value.x);
	f->GetAttribute("y", value.y);
}


template <>
void DeserializeObject<Rect>( AttributeReader* f, Rect& value )
{
	f->GetAttribute("x", value.position.x);
	f->GetAttribute("y", value.position.y);
	f->GetAttribute("w", value.size.x);
	f->GetAttribute("h", value.size.y);
}


template <>
void DeserializeObject<SpriteBase>( AttributeReader* f, SpriteBase& s )
{
	//if( f->NextChild("SpriteBase") )
	{
		f->GetAttribute("width", s.size.x);
		f->GetAttribute("height", s.size.y);
		f->GetAttribute("scale_x", s.scale.x);
		f->GetAttribute("scale_y", s.scale.y);
		f->GetAttribute("angle", s.angle);
		f->GetAttribute("color", s.color.packed_value);
		f->GetAttribute("blendmode", s.blendmode.value);

	//	f->SetToParent();
	}
}


template <>
void DeserializeObject<SpriteAnimation>( AttributeReader* f, SpriteAnimation& a )
{
	//if( f->NextChild("SpriteAnimation") )
	{
		Rect sourceRect = Rect::Zero;
		DeserializeObject<Rect>(f, sourceRect);
		int numFrames = 1;
		int offsetX = 0;
		int offsetY = 0;
		int flags = 0;
		float animSpeed = 16.f;

		f->GetAttribute("frames", numFrames);
		f->GetAttribute("offset_x", offsetX);
		f->GetAttribute("offset_y", offsetY);
		f->GetAttribute("speed", animSpeed);
		f->GetAttribute("flags", flags);

		a.Create( sourceRect, animSpeed, numFrames, offsetX, offsetY );
	//	f->SetToParent();
	}
}


template <>
void DeserializeObject<AnimatedSpriteSet>( AttributeReader* f, AnimatedSpriteSet& s )
{
	String textureName;
	u32 count = 0;

	f->GetString("texture", textureName);
	f->GetAttribute("num_animations", count);
	DeserializeObject<SpriteBase>(f, s);
	s.Resize(count);

	Texture* texture = GetTextureManager()->Load(textureName);
	s.SetTexture(texture);

	bool hasAnim = false;
	for( u32 i(0); i < count; ++i )
	{
		if( f->NextChild("SpriteAnimation") )
		{
			DeserializeObject<SpriteAnimation>(f, s[i]);
			hasAnim = true;
		}
	}

	if( hasAnim )
		f->SetToParent();
}


/*
void RpgSerializer::DeserializeSprite( AttributeReader* f, Sprite& s )
{
	DeserializeSpriteBase(xml, s);

	Texture* texture = 0;
	String textureName = f->GetString("texture");

	if( !textureName.empty() )
	{
		ASSERT(g_textureManager != 0);
		texture = g_textureManager->Load(textureName.CString());
	}

	if( !texture )
	{
		LogError("Error: Texture (%s) not found. Could not load Sprite.", textureName.CString());
	}
	else
	{
		Rect sourceRect = Rect::Zero;
		DeserializeRect(xml, sourceRect);
		s.SetTexture(texture);
		s.SetSourceRect(sourceRect);
	}
}


void RpgSerializer::DeserializeAnimatedSprite( AttributeReader* f, AnimatedSprite& a )
{
	DeserializeSpriteBase(xml, a);

	if( f->NextChild("Animation") )
	{
		DeserializeAnimation(xml, a);
		f->SetToParent();
	}
}


void RpgSerializer::DeserializeAnimationSet( AttributeReader* f, AnimationSet& a )
{
	DeserializeSpriteBase(xml, a);
	u32 n = f->GetUInt("count");
	a.Reserve(n);

	Animation emptyAnimation;
	while( f->NextChild("Animation") )
	{
		a.AddAnimation(emptyAnimation);
		DeserializeAnimation(xml, a[a.NumAnimations() - 1]);
	}
}


void RpgSerializer::DeserializeAnimation( AttributeReader* f, Animation& a )
{
	float speed = f->GetFloat("speed");
	bool loop = f->GetBool("loop");
	bool paused = f->GetBool("paused");

	a.SetAnimationSpeed(speed);
	a.SetLooping(loop);
	a.SetPaused(paused);

	Rect sourceRect = Rect::Zero;
	Point offset = Point::Zero;

	Texture* texture = 0;
	String textureName = f->GetString("texture");
	if( !textureName.empty() )
	{
		ASSERT(g_textureManager != 0);

		texture = g_textureManager->GetResource(textureName);
		if( !texture )
		{
			texture = g_textureManager->Load(textureName.CString());
		}
	}

	if( !texture )
	{
		//TODO set default texture to sprite...
		// ..better yet, initialize sprites to default texture when created... 
		// (this would save a lot of extra crap in the long run)..

		//it's not a fatal error, but it's not good either.
		LogError("Error: Texture (%s) not found. Could not load Animation.", textureName.CString());
	}
	else
	{
		a.SetTexture(texture);

		if( f->NextChild("Frame") )
		{
			int numFrames = f->GetInt("num_frames");
			DeserializeRect(xml, sourceRect);
			offset.x = f->GetInt("offset_x");
			offset.y = f->GetInt("offset_y");
			a.SetFrameData( sourceRect, numFrames, offset.x, offset.y );
		}
	}

	f->SetToParent();
}
*/






template <class T> 
void DeserializeStringArray( AttributeReader* f, const char* node, T* stringArray, int n )
{
	if( f->NextChild(node) )
	{
		int i = 0;
		int amount = f->GetAttribute("count");
		amount = (amount < n) ? amount : n;

		while( i < amount && f->NextChild("String") )
		{
			f->GetString("s", stringArray[i]);
			++i;
		}

		f->SetToParent();
	}
}



