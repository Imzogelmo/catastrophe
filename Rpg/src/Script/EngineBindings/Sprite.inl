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


// @Sprite
//
// Non-animated sprite class.

Sprite* MonoEngineBinding::Sprite_Create()
{
	return new Sprite();
}


void MonoEngineBinding::Sprite_Dispose( Sprite* sprite )
{
	if( sprite )
	{
		delete sprite;
		sprite = 0;
	}
}


void MonoEngineBinding::Sprite_SetTexture( Sprite* sprite, Texture* texture )
{
	if( sprite && texture )
		sprite->SetTexture(texture);
}


Vector2 MonoEngineBinding::Sprite_GetSize( Sprite* sprite )
{
	return sprite ? sprite->size : Vector2::Zero;
}


void MonoEngineBinding::Sprite_SetSize( Sprite* sprite, Vector2 value )
{
	if( sprite )
		sprite->size = value;
}


Vector2 MonoEngineBinding::Sprite_GetScale( Sprite* sprite )
{
	return sprite ? sprite->scale : Vector2::Zero;
}


void MonoEngineBinding::Sprite_SetScale( Sprite* sprite, Vector2 value )
{
	if( sprite )
		sprite->scale = value;
}


Color MonoEngineBinding::Sprite_GetColor( Sprite* sprite )
{
	return sprite ? sprite->color : Color::White();
}


void MonoEngineBinding::Sprite_SetColor( Sprite* sprite, Color value )
{
	if( sprite )
		sprite->color = value;
}


BlendMode MonoEngineBinding::Sprite_GetBlendMode( Sprite* sprite )
{
	return sprite ? sprite->blendmode : BlendMode::Alpha;
}


void MonoEngineBinding::Sprite_SetBlendMode( Sprite* sprite, BlendMode value )
{
	if( sprite )
		sprite->blendmode = value;
}


float MonoEngineBinding::Sprite_GetAngle( Sprite* sprite )
{
	return sprite ? sprite->angle : 0.f;
}


void MonoEngineBinding::Sprite_SetAngle( Sprite* sprite, float value )
{
	if( sprite )
		sprite->angle = value;
}


Rectf MonoEngineBinding::Sprite_GetUVRect( Sprite* sprite )
{
	return sprite ? sprite->GetUVRect() : Rectf::Zero;
}


void MonoEngineBinding::Sprite_SetUVRect( Sprite* sprite, Rectf* value )
{
	if( sprite )
		sprite->SetUVRect(*value);
}


Rect MonoEngineBinding::Sprite_GetSourceRect( Sprite* sprite )
{
	if( sprite )
	{
		Texture* texture = sprite->GetTexture();
		if( texture )
			return texture->GetSourceRect(sprite->GetUVRect());
	}

	return Rect::Zero;
}


void MonoEngineBinding::Sprite_SetSourceRect( Sprite* sprite, Rect* value )
{
	if( sprite )
		sprite->SetSourceRect(*value);
}


void MonoEngineBinding::BindSprite()
{
	// Sprite
	SetNamespace("CatastropheEngine.Graphics.Sprite::");
	AddInternalCall("CreateSprite", Sprite_Create);
	AddInternalCall("DisposeSprite", Sprite_Dispose);
	AddInternalCall("SetTexture", Sprite_SetTexture);

	AddInternalCall("GetSize", Sprite_GetSize);
	AddInternalCall("SetSize", Sprite_SetSize);
	AddInternalCall("GetScale", Sprite_GetScale);
	AddInternalCall("SetScale", Sprite_SetScale);
	AddInternalCall("GetColor", Sprite_GetColor);
	AddInternalCall("SetColor", Sprite_SetColor);
	AddInternalCall("GetBlendMode", Sprite_GetBlendMode);
	AddInternalCall("SetBlendMode", Sprite_SetBlendMode);
	AddInternalCall("GetAngle", Sprite_GetAngle);
	AddInternalCall("SetAngle", Sprite_GetAngle);
	AddInternalCall("GetUVRect", Sprite_GetUVRect);
	AddInternalCall("SetUVRect", Sprite_SetUVRect);
	AddInternalCall("GetSourceRect", Sprite_GetSourceRect);
	AddInternalCall("SetSourceRect", Sprite_SetSourceRect);

	/*
	// NativeSpriteMethods
	SetNamespace("CatastropheEngine.Graphics.NativeSpriteMethods::");
	AddInternalCall("GetSize", Sprite_GetSize);
	AddInternalCall("SetSize", Sprite_SetSize);
	AddInternalCall("GetScale", Sprite_GetScale);
	AddInternalCall("SetScale", Sprite_SetScale);
	AddInternalCall("GetColor", Sprite_GetColor);
	AddInternalCall("SetColor", Sprite_SetColor);
	AddInternalCall("GetBlendMode", Sprite_GetBlendMode);
	AddInternalCall("SetBlendMode", Sprite_SetBlendMode);
	AddInternalCall("GetAngle", Sprite_GetAngle);
	AddInternalCall("SetAngle", Sprite_GetAngle);
	AddInternalCall("GetUVRect", Sprite_GetUVRect);
	AddInternalCall("SetUVRect", Sprite_SetUVRect);
	AddInternalCall("GetSourceRect", Sprite_GetSourceRect);
	AddInternalCall("SetSourceRect", Sprite_SetSourceRect);
	*/
}
