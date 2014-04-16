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

#include <Catastrophe/Graphics/Texture.h>

#include "Script/MonoEngineBinding.h"


// @Texture
//
// This is a direct mapping of type Graphics.Texture to an unmanaged texture.
// The underlying texture is guaranteed to be valid (through reference counting)
// for the lifetime of the managed object.

Texture* MonoEngineBinding::Texture_LoadFromFile( MonoString* str )
{
	const char* filename = mono_string_to_utf8(str);
	Texture* texture = new Texture();
	if( !texture->LoadFromFile(filename) )
	{
		delete texture;
		return 0;
	}

	return texture;
}


Texture* MonoEngineBinding::Texture_Create( int width, int height )
{
	//texture = new Texture(width, height, );
	return 0;
}


void MonoEngineBinding::Texture_Dispose( Texture* texture )
{
	//if( texture )
	//	texture->ReleaseRef();
}


void MonoEngineBinding::Texture_AddRef( Texture* texture )
{
	//if( texture )
	//	texture->AddRef();
}


void MonoEngineBinding::Texture_ReleaseRef( Texture* texture )
{
	//if( texture )
	//	texture->ReleaseRef();
}


int MonoEngineBinding::Texture_GetTextureID( Texture* texture )
{
	return texture ? (int)texture->GetTextureID() : 0;
}


int MonoEngineBinding::Texture_GetWidth( Texture* texture )
{
	return texture ? texture->Width() : 0;
}


int MonoEngineBinding::Texture_GetHeight( Texture* texture )
{
	return texture ? texture->Height() : 0;
}


Vector2 MonoEngineBinding::Texture_CalculateUV( Texture* texture, Point* point )
{
	if( texture )
		texture->GetUV(*point);

	return Vector2::Zero;
}


Rectf MonoEngineBinding::Texture_CalculateUVRect( Texture* texture, Rect* rect )
{
	if( texture )
		texture->GetUVRect(*rect);

	return Rectf::Zero;
}


void MonoEngineBinding::BindTexture()
{
	SetNamespace("CatastropheEngine.Graphics.Texture::");

	AddInternalCall("LoadFromFile", Texture_LoadFromFile);
	AddInternalCall("Internal_CreateTexture", Texture_Create);
	AddInternalCall("InternalDisposeTexture", Texture_Dispose);
	//mono_add_internal_call("Internal_AddRef", Texture_AddRef);
	//mono_add_internal_call("Internal_ReleaseRef", Texture_ReleaseRef);
	AddInternalCall("InternalGetTextureID", Texture_GetTextureID);
	AddInternalCall("GetWidth", Texture_GetWidth);
	AddInternalCall("GetHeight", Texture_GetHeight);
	AddInternalCall("InternalGetUV", Texture_CalculateUV);
	AddInternalCall("InternalGetUVRect", Texture_CalculateUV);

}


