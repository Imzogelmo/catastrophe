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

#include <Catastrophe/IO/XmlReader.h>
#include <Catastrophe/Math/Point.h>
#include <Catastrophe/Math/Rect.h>
#include <Catastrophe/Graphics/SpriteAnimation.h>
#include <Catastrophe/Graphics/AnimatedSpriteSet.h>
#include <Catastrophe/Graphics/Sprite.h>
#include <fc/math.h>

#include "Serialization.h"
#include "TextureManager.h"




template <class T>
void DeserializeObject( const char* nodeName, XmlReader* xml, T& val )
{
	if( xml->NextChild(nodeName) )
	{
		DeserializeObject<T>(xml, val);
		xml->SetToParent();
	}
}


template <>
void DeserializeObject<Point>( XmlReader* xml, Point& val )
{
	val.x = xml->GetInt("x", 0);
	val.y = xml->GetInt("y", 0);
}


template <>
void DeserializeObject<Rect>( XmlReader* xml, Rect& val )
{
	val.pos.x = xml->GetInt("x", 0);
	val.pos.y = xml->GetInt("y", 0);
	val.size.x = xml->GetInt("w", 0);
	val.size.y = xml->GetInt("h", 0);
}


template <>
void DeserializeObject<SpriteBase>( XmlReader* xml, SpriteBase& s )
{
	//if( xml->NextChild("SpriteBase") )
	{
		s.size.x = (float)xml->GetInt("width");
		s.size.y = (float)xml->GetInt("height");
		s.scale.x = xml->GetFloat("scale_x", 1.f);
		s.scale.y = xml->GetFloat("scale_y", 1.f);
		s.angle = xml->GetFloat("angle");
		s.color.packed_value = xml->GetUInt("color", Color::White().packed_value);
		s.blendmode.value = xml->GetUInt("blendmode", BlendMode::Alpha.value);

	//	xml->SetToParent();
	}
}


template <>
void DeserializeObject<SpriteAnimation>( XmlReader* xml, SpriteAnimation& a )
{
	//if( xml->NextChild("SpriteAnimation") )
	{
		Rect sourceRect = Rect::Zero;
		DeserializeObject<Rect>(xml, sourceRect);
		int numFrames = xml->GetInt("frames", 1);
		int offsetX = xml->GetInt("offset_x");
		int offsetY = xml->GetInt("offset_y");
		float animSpeed = xml->GetFloat("speed", 16.f);
		int flags = xml->GetInt("flags");

		a.Create( sourceRect, animSpeed, numFrames, offsetX, offsetY );
	//	xml->SetToParent();
	}
}


template <>
void DeserializeObject<AnimatedSpriteSet>( XmlReader* xml, AnimatedSpriteSet& s )
{
	fc::string str = xml->GetString("texture");
	size_t count = xml->GetUInt("num_animations");
	DeserializeObject<SpriteBase>(xml, s);
	s.Resize(count);

	Texture* texture = g_textureManager->Load(str);
	s.SetTexture(texture);

	bool hasAnim = false;
	for( size_t i(0); i < count; ++i )
	{
		if( xml->NextChild("SpriteAnimation") )
		{
			DeserializeObject<SpriteAnimation>(xml, s[i]);
			hasAnim = true;
		}
	}

	if( hasAnim )
		xml->SetToParent();
}


/*
void RpgSerializer::DeserializeSprite( XmlReader* xml, Sprite& s )
{
	DeserializeSpriteBase(xml, s);

	Texture* texture = 0;
	fc::string textureName = xml->GetString("texture");

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


void RpgSerializer::DeserializeAnimatedSprite( XmlReader* xml, AnimatedSprite& a )
{
	DeserializeSpriteBase(xml, a);

	if( xml->NextChild("Animation") )
	{
		DeserializeAnimation(xml, a);
		xml->SetToParent();
	}
}


void RpgSerializer::DeserializeAnimationSet( XmlReader* xml, AnimationSet& a )
{
	DeserializeSpriteBase(xml, a);
	size_t n = xml->GetUInt("count");
	a.Reserve(n);

	Animation emptyAnimation;
	while( xml->NextChild("Animation") )
	{
		a.AddAnimation(emptyAnimation);
		DeserializeAnimation(xml, a[a.NumAnimations() - 1]);
	}
}


void RpgSerializer::DeserializeAnimation( XmlReader* xml, Animation& a )
{
	float speed = xml->GetFloat("speed");
	bool loop = xml->GetBool("loop");
	bool paused = xml->GetBool("paused");

	a.SetAnimationSpeed(speed);
	a.SetLooping(loop);
	a.SetPaused(paused);

	Rect sourceRect = Rect::Zero;
	Point offset = Point::Zero;

	Texture* texture = 0;
	fc::string textureName = xml->GetString("texture");
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

		if( xml->NextChild("Frame") )
		{
			int numFrames = xml->GetInt("num_frames");
			DeserializeRect(xml, sourceRect);
			offset.x = xml->GetInt("offset_x");
			offset.y = xml->GetInt("offset_y");
			a.SetFrameData( sourceRect, numFrames, offset.x, offset.y );
		}
	}

	xml->SetToParent();
}
*/






template <class T> 
void DeserializeStringArray( XmlReader* xml, const char* node, T* stringArray, int n )
{
	if( xml->NextChild(node) )
	{
		int i = 0;
		int amount = xml->GetInt("count");
		amount = (amount < n) ? amount : n;

		while( i < amount && xml->NextChild("String") )
		{
			stringArray[i] = xml->GetString("s");
			++i;
		}

		xml->SetToParent();
	}
}



