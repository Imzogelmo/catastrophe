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

#include <Catastrophe/IO/AttributeWriter.h>
#include <Catastrophe/Math/Point.h>
#include <Catastrophe/Math/Rect.h>
#include <Catastrophe/Graphics/Texture.h>
#include <Catastrophe/Graphics/SpriteAnimation.h>
#include <Catastrophe/Graphics/AnimatedSpriteSet.h>
#include <Catastrophe/Graphics/Sprite.h>
#include <fc/math.h>

#include "Serialization.h"



template <class T>
void SerializeObject<T>( const char* nodeName, AttributeWriter* f, const T& val )
{
	f->BeginNode(nodeName);
	SerializeObject<T>(f, val);
	f->EndNode();
}


template <>
void SerializeObject<Point>( AttributeWriter* f, const Point& val )
{
	f->SetInt("x", val.x);
	f->SetInt("y", val.y);
}


template <>
void SerializeObject<Rect>( AttributeWriter* f, const Rect& val )
{
	f->SetInt("x", val.pos.x);
	f->SetInt("y", val.pos.y);
	f->SetInt("w", val.size.x);
	f->SetInt("h", val.size.y);
}


template <>
void SerializeObject<SpriteBase>( AttributeWriter* f, const SpriteBase& s )
{
	f->SetInt("width", fc::iround(s.size.x));
	f->SetInt("height", fc::iround(s.size.y));
	f->SetFloat("scale_x", s.scale.x);
	f->SetFloat("scale_y", s.scale.y);
	f->SetFloat("angle", s.angle);
	f->SetUInt("color", s.color.packed_value);
	f->SetUInt("blendmode", s.blendmode.value);
}


template <>
void SerializeObject<SpriteAnimation>( AttributeWriter* f, const SpriteAnimation& a )
{
	//f->BeginNode("SpriteAnimation");

	SerializeObject<Rect>(f, a.GetSourceRect());
	f->SetUInt("frames", a.GetNumFrames());
	f->SetInt("offset_x", a.GetFrameOffsetX());
	f->SetInt("offset_y", a.GetFrameOffsetY());
	f->SetFloat("speed", a.GetAnimationSpeed());
	f->SetInt("flags", a.GetFlags());

	//f->EndNode();
}


template <>
void SerializeObject<AnimatedSpriteSet>( AttributeWriter* f, const AnimatedSpriteSet& s )
{
	//f->BeginNode("AnimatedSpriteSet");

	Texture* texture = s.GetTexture();
	fc::string texStr = texture ? texture->GetName() : "";
	size_t count = s.GetNumAnimations();

	f->SetString("texture", texStr.c_str());
	f->SetUInt("num_animations", count);
	SerializeObject<SpriteBase>("SpriteBase", f, s);

	for( size_t i(0); i < count; ++i )
	{
		SerializeObject<SpriteAnimation>(f, s.GetAnimation(i));
	}

	//f->EndNode();
}


/*
template <>
void SerializeObject<Sprite>( AttributeWriter* f, const Sprite& s )
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

	f->SetString("texture", textureName.c_str());
	SerializeRect(xml, sourceRect);
}


void RpgSerializer::SerializeAnimatedSprite( AttributeWriter* f, const AnimatedSprite& a )
{
	SerializeSpriteBase(xml, a);

	f->BeginNode("Animation");
	SerializeAnimation(xml, a);
	f->EndNode();
}


void RpgSerializer::SerializeAnimationSet( AttributeWriter* f, const AnimationSet& a )
{
	SerializeSpriteBase(xml, a);
	f->SetUInt("count", a.NumAnimations());

	for( size_t i(0); i < a.NumAnimations(); ++i )
	{
		f->BeginNode("Animation");
		SerializeAnimation(xml, a.GetAnimation(i) );
		f->EndNode();
	}
}


void RpgSerializer::SerializeAnimation( AttributeWriter* f, const Animation& a )
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

	f->SetString("texture", textureName.c_str());
	f->SetFloat("speed", a.GetAnimSpeed() );
	f->SetBool("loop", a.IsLooping() );
	f->SetBool("paused", a.IsPaused() );

	f->BeginNode("Frame");
	f->SetUInt("num_frames", a.NumFrames());
	SerializeRect(xml, r1);
	f->SetInt("offset_x", offset.x);
	f->SetInt("offset_y", offset.y);
	f->EndNode();
}
*/


template <class T> 
void SerializeStringArray( AttributeWriter* f, const char* node, const T* stringArray, int n )
{
	f->BeginNode(node);
	f->SetInt("count", n);
	for( int i(0); i < n; ++i )
	{
		f->BeginNode("String");
		f->SetInt("id", i);
		f->SetString("s", stringArray[i].c_str());
		f->EndNode();
	}
	f->EndNode();
}
