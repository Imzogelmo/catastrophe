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

#include <Catastrophe/IO/AttributeReader.h>
#include <Catastrophe/Math/Point.h>
#include <Catastrophe/Math/Rect.h>
#include <Catastrophe/Graphics/SpriteAnimation.h>
#include <Catastrophe/Graphics/AnimatedSpriteSet.h>
#include <Catastrophe/Graphics/Sprite.h>
#include <fc/math.h>

#include "Serialization.h"
#include "TextureManager.h"




template <class T>
void DeserializeObject( const char* nodeName, AttributeReader* f, T& val )
{
	if( f->NextChild(nodeName) )
	{
		DeserializeObject<T>(f, val);
		f->SetToParent();
	}
}


template <>
void DeserializeObject<Point>( AttributeReader* f, Point& val )
{
	val.x = f->GetInt("x", 0);
	val.y = f->GetInt("y", 0);
}


template <>
void DeserializeObject<Rect>( AttributeReader* f, Rect& val )
{
	val.pos.x = f->GetInt("x", 0);
	val.pos.y = f->GetInt("y", 0);
	val.size.x = f->GetInt("w", 0);
	val.size.y = f->GetInt("h", 0);
}


template <>
void DeserializeObject<SpriteBase>( AttributeReader* f, SpriteBase& s )
{
	//if( f->NextChild("SpriteBase") )
	{
		s.size.x = (float)f->GetInt("width");
		s.size.y = (float)f->GetInt("height");
		s.scale.x = f->GetFloat("scale_x", 1.f);
		s.scale.y = f->GetFloat("scale_y", 1.f);
		s.angle = f->GetFloat("angle");
		s.color.packed_value = f->GetUInt("color", Color::White().packed_value);
		s.blendmode.value = f->GetUInt("blendmode", BlendMode::Alpha.value);

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
		int numFrames = f->GetInt("frames", 1);
		int offsetX = f->GetInt("offset_x");
		int offsetY = f->GetInt("offset_y");
		float animSpeed = f->GetFloat("speed", 16.f);
		int flags = f->GetInt("flags");

		a.Create( sourceRect, animSpeed, numFrames, offsetX, offsetY );
	//	f->SetToParent();
	}
}


template <>
void DeserializeObject<AnimatedSpriteSet>( AttributeReader* f, AnimatedSpriteSet& s )
{
	fc::string str = f->GetString("texture");
	size_t count = f->GetUInt("num_animations");
	DeserializeObject<SpriteBase>(f, s);
	s.Resize(count);

	Texture* texture = g_textureManager->Load(str);
	s.SetTexture(texture);

	bool hasAnim = false;
	for( size_t i(0); i < count; ++i )
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
	fc::string textureName = f->GetString("texture");

	if( !textureName.empty() )
	{
		ASSERT(g_textureManager != 0);
		texture = g_textureManager->Load(textureName.c_str());
	}

	if( !texture )
	{
		LogError("Error: Texture (%s) not found. Could not load Sprite.", textureName.c_str());
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
	size_t n = f->GetUInt("count");
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
	fc::string textureName = f->GetString("texture");
	if( !textureName.empty() )
	{
		ASSERT(g_textureManager != 0);

		texture = g_textureManager->GetResource(textureName);
		if( !texture )
		{
			texture = g_textureManager->Load(textureName.c_str());
		}
	}

	if( !texture )
	{
		//TODO set default texture to sprite...
		// ..better yet, initialize sprites to default texture when created... 
		// (this would save a lot of extra crap in the long run)..

		//it's not a fatal error, but it's not good either.
		LogError("Error: Texture (%s) not found. Could not load Animation.", textureName.c_str());
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
		int amount = f->GetInt("count");
		amount = (amount < n) ? amount : n;

		while( i < amount && f->NextChild("String") )
		{
			stringArray[i] = f->GetString("s");
			++i;
		}

		f->SetToParent();
	}
}



