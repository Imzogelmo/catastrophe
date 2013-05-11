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

#include <Catastrophe/IO/XmlWriter.h>
#include <Catastrophe/Math/Point.h>
#include <Catastrophe/Math/Rect.h>
#include <Catastrophe/Graphics/Texture.h>
#include <Catastrophe/Graphics/SpriteAnimation.h>
#include <Catastrophe/Graphics/AnimatedSpriteSet.h>
#include <Catastrophe/Graphics/Sprite.h>
#include <fc/math.h>

#include "Serialization.h"



template <class T>
void SerializeObject<T>( const char* nodeName, XmlWriter* xml, const T& val )
{
	xml->BeginNode(nodeName);
	SerializeObject<T>(xml, val);
	xml->EndNode();
}


template <>
void SerializeObject<Point>( XmlWriter* xml, const Point& val )
{
	xml->SetInt("x", val.x);
	xml->SetInt("y", val.y);
}


template <>
void SerializeObject<Rect>( XmlWriter* xml, const Rect& val )
{
	xml->SetInt("x", val.pos.x);
	xml->SetInt("y", val.pos.y);
	xml->SetInt("w", val.size.x);
	xml->SetInt("h", val.size.y);
}


template <>
void SerializeObject<SpriteBase>( XmlWriter* xml, const SpriteBase& s )
{
	xml->SetInt("width", fc::iround(s.size.x));
	xml->SetInt("height", fc::iround(s.size.y));
	xml->SetFloat("scale_x", s.scale.x);
	xml->SetFloat("scale_y", s.scale.y);
	xml->SetFloat("angle", s.angle);
	xml->SetUInt("color", s.color.packed_value);
	xml->SetUInt("blendmode", s.blendmode.value);
}


template <>
void SerializeObject<SpriteAnimation>( XmlWriter* xml, const SpriteAnimation& a )
{
	xml->BeginNode("SpriteAnimation");

	SerializeObject<Rect>(xml, a.GetSourceRect());
	xml->SetUInt("num_frames", a.GetNumFrames());
	xml->SetInt("offset_x", a.GetFrameOffsetX());
	xml->SetInt("offset_y", a.GetFrameOffsetY());
	xml->SetFloat("speed", a.GetAnimationSpeed());
	xml->SetInt("flags", a.GetFlags());

	xml->EndNode();
}


template <>
void SerializeObject<AnimatedSpriteSet>( XmlWriter* xml, const AnimatedSpriteSet& s )
{
	xml->BeginNode("AnimatedSpriteSet");

	Texture* texture = s.GetTexture();
	fc::string texStr = texture ? texture->GetName() : "";
	size_t count = s.GetNumAnimations();

	xml->SetString("texture", texStr.c_str());
	xml->SetUInt("num_animations", count);
	SerializeObject<SpriteBase>(xml, s);

	for( size_t i(0); i < count; ++i )
	{
		SerializeObject<SpriteAnimation>(xml, s.GetAnimation(i));
	}

	xml->EndNode();
}


/*
template <>
void SerializeObject<Sprite>( XmlWriter* xml, const Sprite& s )
{
	SerializeSpriteBase(xml, s);

	fc::string textureName;
	Rect sourceRect = Rect::Zero;

	const Texture* texture = s.GetTexture();
	if( !texture )
	{
		Log("SerializeObject<Sprite> Error: texture is null.");
	}
	else
	{
		sourceRect = texture->GetSourceRect(s.GetUVRect());
	}

	xml->SetString("texture", textureName.c_str());
	SerializeRect(xml, sourceRect);
}


void RpgSerializer::SerializeAnimatedSprite( XmlWriter* xml, const AnimatedSprite& a )
{
	SerializeSpriteBase(xml, a);

	xml->BeginNode("Animation");
	SerializeAnimation(xml, a);
	xml->EndNode();
}


void RpgSerializer::SerializeAnimationSet( XmlWriter* xml, const AnimationSet& a )
{
	SerializeSpriteBase(xml, a);
	xml->SetUInt("count", a.NumAnimations());

	for( size_t i(0); i < a.NumAnimations(); ++i )
	{
		xml->BeginNode("Animation");
		SerializeAnimation(xml, a.GetAnimation(i) );
		xml->EndNode();
	}
}


void RpgSerializer::SerializeAnimation( XmlWriter* xml, const Animation& a )
{
	fc::string textureName;
	Rect r1 = Rect::Zero;
	Rect r2 = Rect::Zero;
	Point offset = Point::Zero;

	const Texture* texture = a.GetTexture();
	if( !texture )
	{
		Log("SerializeAnimation error: null texture.");
	}
	else
	{
		textureName = texture->GetName();
		if( a.NumFrames() > 1 )
		{
			const Rectf* uv = a.GetUVArray();
			r1 = texture->GetSourceRect( uv[0] );
			r2 = texture->GetSourceRect( uv[1] );
			offset = r2.pos - r2.pos;
		}
		else
		{
			r1 = texture->GetSourceRect( a.GetUVRect(0) );
		}
	}

	xml->SetString("texture", textureName.c_str());
	xml->SetFloat("speed", a.GetAnimSpeed() );
	xml->SetBool("loop", a.IsLooping() );
	xml->SetBool("paused", a.IsPaused() );

	xml->BeginNode("Frame");
	xml->SetUInt("num_frames", a.NumFrames());
	SerializeRect(xml, r1);
	xml->SetInt("offset_x", offset.x);
	xml->SetInt("offset_y", offset.y);
	xml->EndNode();
}
*/


template <class T> 
void SerializeStringArray( XmlWriter* xml, const char* node, const T* stringArray, int n )
{
	xml->BeginNode(node);
	xml->SetInt("count", n);
	for( int i(0); i < n; ++i )
	{
		xml->BeginNode("String");
		xml->SetInt("id", i);
		xml->SetString("s", stringArray[i].c_str());
		xml->EndNode();
	}
	xml->EndNode();
}
