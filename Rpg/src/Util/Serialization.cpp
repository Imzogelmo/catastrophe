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
#include <Catastrophe/Graphics/Sprite.h>
#include <fc/math.h>

#include "Serialization.h"
#include "../ResourceManager.h"


namespace Util
{
	// TODO
	// system needs the following types available:
	// -blank (dummy) texture, default shader, and system font.
	// this will allow me to optimize some low-level stuff further
	// and prevent potential crashes.


	void SerializePoint( XmlWriter* xml, const Point& p )
	{
		xml->SetInt("x", p.x);
		xml->SetInt("y", p.y);
	}

	void SerializeRect( XmlWriter* xml, const Rect& r )
	{
		xml->SetInt("x", r.pos.x);
		xml->SetInt("y", r.pos.y);
		xml->SetInt("w", r.size.x);
		xml->SetInt("h", r.size.y);
	}

	void SerializeSprite( XmlWriter* xml, const Sprite& s )
	{
		xml->SetInt("width", fc::iround(s.size.x));
		xml->SetInt("height", fc::iround(s.size.y));
		xml->SetFloat("scale_x", s.scale.x);
		xml->SetFloat("scale_y", s.scale.y);
		xml->SetFloat("angle", s.angle);
		xml->SetUInt("color", s.tint.packed_value);
		xml->SetUInt("blendmode", s.blendmode.value);

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

	void SerializeAnimatedSprite( XmlWriter* xml, const AnimatedSprite& a )
	{
		xml->SetInt("width", fc::iround(a.size.x));
		xml->SetInt("height", fc::iround(a.size.y));
		xml->SetFloat("scale_x", a.scale.x);
		xml->SetFloat("scale_y", a.scale.y);
		xml->SetFloat("angle", a.angle);
		xml->SetUInt("color", a.tint.packed_value);
		xml->SetUInt("blendmode", a.blendmode.value);

		xml->BeginNode("Animation");
		SerializeAnimation(xml, a);
		xml->EndNode();
	}

	void SerializeAnimation( XmlWriter* xml, const Animation& a )
	{
		xml->SetFloat("speed", a.GetAnimSpeed() );
		xml->SetBool("loop", a.IsLooping() );
		xml->SetBool("paused", a.IsPaused() );

		xml->BeginNode("Frame");
		SerializeAnimationFrames(xml, a);
		xml->EndNode();
	}

	void SerializeAnimationFrames( XmlWriter* xml, const AnimationFrames& a )
	{
		fc::string textureName;
		Rect r1 = Rect::Zero;
		Rect r2 = Rect::Zero;
		Point offset = Point::Zero;

		const Texture* texture = a.GetTexture();
		if( !texture )
		{
			Log("SerializeAnimationFrames error: null texture.");
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
		xml->SetUInt("num_frames", a.NumFrames());
		SerializeRect(xml, r1);
		xml->SetInt("offset_x", offset.x);
		xml->SetInt("offset_y", offset.y);
	}




	void DeserializePoint( XmlReader* xml, Point& p )
	{
		p.x = xml->GetInt("x");
		p.y = xml->GetInt("y");
	}

	void DeserializeRect( XmlReader* xml, Rect& r )
	{
		r.pos.x = xml->GetInt("x");
		r.pos.y = xml->GetInt("y");
		r.size.x = xml->GetInt("w");
		r.size.y = xml->GetInt("h");
	}

	void DeserializeSprite( XmlReader* xml, Sprite& s )
	{
		s.size.x = (float)xml->GetInt("width");
		s.size.y = (float)xml->GetInt("height");
		s.scale.x = xml->GetFloat("scale_x", 1.f);
		s.scale.y = xml->GetFloat("scale_y", 1.f);
		s.angle = xml->GetFloat("angle");
		s.tint.packed_value = xml->GetUInt("color", Color::White().packed_value);
		s.blendmode.value = xml->GetUInt("blendmode", BlendMode::Alpha.value);

		Texture* texture = 0;
		fc::string textureName = xml->GetString("texture");

		if( !textureName.empty() )
		{
			ResourceManager* resourceManager = gGetResourceManager();
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

	void DeserializeAnimatedSprite( XmlReader* xml, AnimatedSprite& a )
	{
		a.size.x = (float)xml->GetInt("width");
		a.size.y = (float)xml->GetInt("height");
		a.scale.x = xml->GetFloat("scale_x", 1.f);
		a.scale.y = xml->GetFloat("scale_y", 1.f);
		a.angle = xml->GetFloat("angle");
		a.tint.packed_value = xml->GetUInt("color", Color::White().packed_value);
		a.blendmode.value = xml->GetUInt("blendmode", BlendMode::Alpha.value);

		if( xml->NextChild("Animation") )
		{
			DeserializeAnimation(xml, a);
			xml->SetToParent();
		}
	}

	void DeserializeAnimation( XmlReader* xml, Animation& a )
	{
		float speed = xml->GetFloat("speed");
		bool loop = xml->GetBool("loop");
		bool paused = xml->GetBool("paused");

		a.SetAnimationSpeed(speed);
		a.SetLooping(loop);
		a.SetPaused(paused);

		if( xml->NextChild("Frame") )
		{
			DeserializeAnimationFrames(xml, a);
			xml->SetToParent();
		}
	}

	void DeserializeAnimationFrames( XmlReader* xml, AnimationFrames& a )
	{
		Rect sourceRect = Rect::Zero;
		Point offset = Point::Zero;

		Texture* texture = 0;
		fc::string textureName = xml->GetString("texture");
		if( !textureName.empty() )
		{
			ResourceManager* resourceManager = gGetResourceManager();
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
			int numFrames = xml->GetInt("num_frames");
			DeserializeRect(xml, sourceRect);
			offset.x = xml->GetInt("offset_x");
			offset.y = xml->GetInt("offset_y");
			a.SetTexture(texture);
			a.SetFrameData( sourceRect, numFrames, offset.x, offset.y );
		}
	}


} //namespace Util

