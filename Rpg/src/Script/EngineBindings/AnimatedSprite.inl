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


#include <mono/metadata/object.h>
#include <mono/metadata/loader.h>

#include <Catastrophe/Graphics/Sprite.h>

#include "Script/MonoEngineBinding.h"


AnimatedSprite* MonoEngineBinding::AnimatedSprite_Create()
{
	AnimatedSprite* animatedSprite = new AnimatedSprite();
	return animatedSprite;
}


void MonoEngineBinding::AnimatedSprite_Dispose( AnimatedSprite* sprite )
{
	if( sprite )
	{
		delete sprite;
		sprite = 0;
	}
}


void MonoEngineBinding::AnimatedSprite_Update( AnimatedSprite* sprite )
{
	if( sprite )
		sprite->Update();
}


Rectf MonoEngineBinding::AnimatedSprite_GetUVRect( AnimatedSprite* sprite )
{
	return sprite ? sprite->GetUVRect() : Rectf::Zero;
}


void MonoEngineBinding::AnimatedSprite_SetUVRect( AnimatedSprite* sprite, Rectf* value )
{
	if( sprite )
	{
		Texture* texture = sprite->GetTexture();
		if( texture )
			sprite->SetSourceRect( texture->GetSourceRect(*value) );
	}
}


Rect MonoEngineBinding::AnimatedSprite_GetSourceRect( AnimatedSprite* sprite )
{
	return sprite ? sprite->GetSourceRect() : Rect::Zero;
}


void MonoEngineBinding::AnimatedSprite_SetSourceRect( AnimatedSprite* sprite, Rect* value )
{
	if( sprite )
		sprite->SetSourceRect(*value);
}


int MonoEngineBinding::AnimatedSprite_GetNumFrames( AnimatedSprite* sprite )
{
	return sprite ? sprite->GetNumFrames() : 0;
}


void MonoEngineBinding::AnimatedSprite_SetNumFrames( AnimatedSprite* sprite, int value )
{
	if( sprite )
		sprite->SetNumFrames(value);
}


int MonoEngineBinding::AnimatedSprite_GetCurrentFrame( AnimatedSprite* sprite )
{
	return sprite ? sprite->GetCurrentFrame() : 0;
}


void MonoEngineBinding::AnimatedSprite_SetCurrentFrame( AnimatedSprite* sprite, int value )
{
	if( sprite )
		sprite->SetCurrentFrame(value);
}


float MonoEngineBinding::AnimatedSprite_GetAnimationSpeed( AnimatedSprite* sprite )
{
	return sprite ? sprite->GetAnimationSpeed() : 0;
}


void MonoEngineBinding::AnimatedSprite_SetAnimationSpeed( AnimatedSprite* sprite, float value )
{
	if( sprite )
		sprite->SetAnimationSpeed(value);
}



void MonoEngineBinding::BindAnimatedSprite()
{
	SetNamespace("CatastropheEngine.Graphics.AnimatedSprite::");

	// AnimatedSprite : Sprite
	// Base class methods are inherited from Sprite

	AddInternalCall("CreateAnimatedSprite", AnimatedSprite_Create);
	AddInternalCall("DisposeAnimatedSprite", AnimatedSprite_Dispose);
	AddInternalCall("Update", AnimatedSprite_Update);
	AddInternalCall("GetUVRect", AnimatedSprite_GetUVRect);
	AddInternalCall("SetUVRect", AnimatedSprite_SetUVRect);
	AddInternalCall("GetSourceRect", AnimatedSprite_GetSourceRect);
	AddInternalCall("SetSourceRect", AnimatedSprite_SetSourceRect);
	AddInternalCall("GetNumFrames", AnimatedSprite_GetNumFrames);
	AddInternalCall("SetNumFrames", AnimatedSprite_SetNumFrames);
	AddInternalCall("GetCurrentFrame", AnimatedSprite_GetCurrentFrame);
	AddInternalCall("SetCurrentFrame", AnimatedSprite_SetCurrentFrame);
	AddInternalCall("GetAnimationSpeed", AnimatedSprite_GetAnimationSpeed);
	AddInternalCall("SetAnimationSpeed", AnimatedSprite_SetAnimationSpeed);



}

