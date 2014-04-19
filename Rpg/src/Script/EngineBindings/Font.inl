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


#include <Catastrophe/Graphics/Texture.h>
#include <Catastrophe/Graphics/Font.h>

#include "Script/MonoEngineBinding.h"



Font* MonoEngineBinding::Font_LoadFromFile( MonoString* str )
{
	const char* filename = mono_string_to_utf8(str);
	Font* font = new Font();
	if( font->LoadFromFile(filename, 16) != CE_SUCCESS )
	{
		delete font;
		return 0;
	}

	return font;
}


void MonoEngineBinding::Font_Dispose( Font* font )
{
	delete font;
}


void MonoEngineBinding::Font_SetAdvance( Font* font, int advance )
{
	SAFE_CALL(font, SetAdvance(advance));
}


void MonoEngineBinding::Font_SetLineHeight( Font* font, int height )
{
	SAFE_CALL(font, SetLineHeight(height));
}


int MonoEngineBinding::Font_GetTextWidth( Font* font, MonoString* str )
{
	if( font && str )
	{
		const char* begin = mono_string_to_utf8(str);
		const char* end = begin + mono_string_length(str);

		return font->GetTextWidth(begin, end);
	}

	return 0;
}


int MonoEngineBinding::Font_GetStaticTextWidth( Font* font, const char* str )
{
	if( font && str )
	{
		size_t length = strlen(str);
		return font->GetTextWidth(str, str + length);
	}

	return 0;
}


Texture* MonoEngineBinding::Font_GetTexture( Font* font )
{
	SAFE_CALL_RETURN(font, GetTexture(), 0);
}


int MonoEngineBinding::Font_GetLineHeight( Font* font )
{
	SAFE_CALL_RETURN(font, GetLineHeight(), 0);
}


Glyph MonoEngineBinding::Font_GetGlyph( Font* font, byte i )
{
	SAFE_CALL_RETURN(font, GetGlyph(i), Glyph());
}


void MonoEngineBinding::Font_SetGlyph( Font* font, byte i, Glyph* glyph )
{
	SAFE_CALL(font, GetGlyph(i) = *glyph);
}



void MonoEngineBinding::BindFont()
{
	SetNamespace("CatastropheEngine.Graphics.Font::");

	AddInternalCall("LoadFromFile", Font_LoadFromFile);
	AddInternalCall("DisposeFont", Font_Dispose);
	AddInternalCall("SetAdvance", Font_SetAdvance);
	AddInternalCall("SetLineHeight", Font_SetLineHeight);
	AddInternalCall("GetTextWidth", Font_GetTextWidth);
	AddInternalCall("GetTexture", Font_GetTexture);
	AddInternalCall("GetLineHeight", Font_GetLineHeight);
	AddInternalCall("GetGlyph", Font_GetGlyph);
	AddInternalCall("SetGlyph", Font_SetGlyph);
}

