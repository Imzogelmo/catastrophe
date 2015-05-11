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
#include <Catastrophe/Core/IO/AttributeWriter.h>
#include <Catastrophe/Core/Math/Point.h>
#include <Catastrophe/Core/Math/Rect.h>
#include <Catastrophe/Graphics/Texture.h>
#include <Catastrophe/Graphics/SpriteAnimation.h>
#include <Catastrophe/Graphics/AnimatedSpriteSet.h>
#include <Catastrophe/Graphics/Sprite.h>

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
	f->SetAttribute("x", val.x);
	f->SetAttribute("y", val.y);
}


template <>
void SerializeObject<Rect>( AttributeWriter* f, const Rect& val )
{
	f->SetAttribute("x", val.position.x);
	f->SetAttribute("y", val.position.y);
	f->SetAttribute("w", val.size.x);
	f->SetAttribute("h", val.size.y);
}


template <>
void SerializeObject<SpriteBase>( AttributeWriter* f, const SpriteBase& s )
{
	f->SetAttribute("width", Math::Round(s.size.x));
	f->SetAttribute("height", Math::Round(s.size.y));
	f->SetAttribute("scale_x", s.scale.x);
	f->SetAttribute("scale_y", s.scale.y);
	f->SetAttribute("angle", s.angle);
	f->SetAttribute("color", s.color.packed_value);
	f->SetAttribute("blendmode", s.blendmode.value);
}


template <>
void SerializeObject<SpriteAnimation>( AttributeWriter* f, const SpriteAnimation& a )
{
	//f->BeginNode("SpriteAnimation");

	SerializeObject<Rect>(f, a.GetSourceRect());
	f->SetAttribute("frames", a.GetNumFrames());
	f->SetAttribute("offset_x", a.GetFrameOffsetX());
	f->SetAttribute("offset_y", a.GetFrameOffsetY());
	f->SetAttribute("speed", a.GetAnimationSpeed());
	f->SetAttribute("flags", a.GetFlags());

	//f->EndNode();
}


template <>
void SerializeObject<AnimatedSpriteSet>( AttributeWriter* f, const AnimatedSpriteSet& s )
{
	//f->BeginNode("AnimatedSpriteSet");

	Texture* texture = s.GetTexture();
	String texStr = texture ? texture->GetResourceName() : "";
	u32 count = s.GetNumAnimations();

	f->SetString("texture", texStr.CString());
	f->SetAttribute("num_animations", count);
	SerializeObject<SpriteBase>("SpriteBase", f, s);

	for( u32 i(0); i < count; ++i )
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

	String textureName;
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

	f->SetString("texture", textureName.CString());
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

	for( u32 i(0); i < a.NumAnimations(); ++i )
	{
		f->BeginNode("Animation");
		SerializeAnimation(xml, a.GetAnimation(i) );
		f->EndNode();
	}
}


void RpgSerializer::SerializeAnimation( AttributeWriter* f, const Animation& a )
{
	String textureName;
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

	f->SetString("texture", textureName.CString());
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
	f->SetAttribute("count", n);
	for( int i(0); i < n; ++i )
	{
		f->BeginNode("String");
		f->SetAttribute("id", i);
		f->SetString("s", stringArray[i].CString());
		f->EndNode();
	}
	f->EndNode();
}


//template crap...
void removeme_()
{
	SerializeObject<Point>("", 0, Point());
	SerializeObject<Rect>("", 0, Rect());
	DeserializeObject<Point>("", 0, Point());
	DeserializeObject<Rect>("", 0, Rect());

}
