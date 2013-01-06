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

	void SerializeAnimatedSprite( XmlWriter* xml, const AnimatedSprite& a )
	{
		// don't need to serialize the per-instance variables.
		xml->SetInt("width", fc::iround(a.size.x));
		xml->SetInt("height", fc::iround(a.size.y));
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
			Log("SerializeAnimationFrames: null texture warning.");
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

	void DeserializeAnimatedSprite( XmlReader* xml, AnimatedSprite& a )
	{
		// don't need to serialize the per-instance variables.
		a.size.x = (float)xml->GetInt("width");
		a.size.y = (float)xml->GetInt("height");
		a.tint.packed_value = xml->GetUInt("color");
		a.blendmode.value = xml->GetUInt("blendmode");

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
			ResourceManager* resourceManager = gGetActiveResourceManager();
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

