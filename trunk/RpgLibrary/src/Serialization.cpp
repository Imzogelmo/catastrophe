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
#include <Catastrophe/IO/XmlReader.h>
#include <Catastrophe/Math/Point.h>
#include <Catastrophe/Math/Rect.h>
#include <Catastrophe/Graphics/Animation.h>
#include <Catastrophe/Graphics/AnimationSet.h>
#include <Catastrophe/Graphics/Sprite.h>
#include <fc/math.h>

#include "Serialization.h"
#include "ResourceManager.h"



void RpgSerializer::SerializePoint( XmlWriter* xml, const Point& p )
{
	xml->SetInt("x", p.x);
	xml->SetInt("y", p.y);
}


void RpgSerializer::SerializeRect( XmlWriter* xml, const Rect& r )
{
	xml->SetInt("x", r.pos.x);
	xml->SetInt("y", r.pos.y);
	xml->SetInt("w", r.size.x);
	xml->SetInt("h", r.size.y);
}


void RpgSerializer::SerializeSpriteBase( XmlWriter* xml, const SpriteBase& s )
{
	xml->SetInt("width", fc::iround(s.size.x));
	xml->SetInt("height", fc::iround(s.size.y));
	xml->SetFloat("scale_x", s.scale.x);
	xml->SetFloat("scale_y", s.scale.y);
	xml->SetFloat("angle", s.angle);
	xml->SetUInt("color", s.tint.packed_value);
	xml->SetUInt("blendmode", s.blendmode.value);
}


void RpgSerializer::SerializeSprite( XmlWriter* xml, const Sprite& s )
{
	SerializeSpriteBase(xml, s);

	fc::string textureName;
	Rect sourceRect = Rect::Zero;

	const Texture* texture = s.GetTexture();
	if( !texture )
	{
		Log("SerializeSprite error: null texture.");
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


template <class T> 
void RpgSerializer::SerializeStringArray( XmlWriter* xml, const char* node, const T* stringArray, int n )
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




//
// Deserialize Functions
//

void RpgSerializer::DeserializePoint( XmlReader* xml, Point& p )
{
	p.x = xml->GetInt("x");
	p.y = xml->GetInt("y");
}


void RpgSerializer::DeserializeRect( XmlReader* xml, Rect& r )
{
	r.pos.x = xml->GetInt("x");
	r.pos.y = xml->GetInt("y");
	r.size.x = xml->GetInt("w");
	r.size.y = xml->GetInt("h");
}


void RpgSerializer::DeserializeSpriteBase( XmlReader* xml, SpriteBase& s )
{
	s.size.x = (float)xml->GetInt("width");
	s.size.y = (float)xml->GetInt("height");
	s.scale.x = xml->GetFloat("scale_x", 1.f);
	s.scale.y = xml->GetFloat("scale_y", 1.f);
	s.angle = xml->GetFloat("angle");
	s.tint.packed_value = xml->GetUInt("color", Color::White().packed_value);
	s.blendmode.value = xml->GetUInt("blendmode", BlendMode::Alpha.value);
}


void RpgSerializer::DeserializeSprite( XmlReader* xml, Sprite& s )
{
	DeserializeSpriteBase(xml, s);

	Texture* texture = 0;
	fc::string textureName = xml->GetString("texture");

	if( !textureName.empty() )
	{
		ResourceManager* resourceManager = GetResourceManager();
		ASSERT(resourceManager != 0);

		texture = resourceManager->GetTexture(textureName);
		if( !texture )
		{
			texture = resourceManager->LoadTexture(textureName.c_str());
		}
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
		ResourceManager* resourceManager = GetResourceManager();
		ASSERT(resourceManager != 0);

		texture = resourceManager->GetTexture(textureName);
		if( !texture )
		{
			texture = resourceManager->LoadTexture(textureName.c_str());
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

template <class T> 
void RpgSerializer::DeserializeStringArray( XmlReader* xml, const char* node, T* stringArray, int n )
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


