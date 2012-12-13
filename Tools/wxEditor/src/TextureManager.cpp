//////////////////////////////////////////////////////////////////////////
// This program is free software: you can redistribute it and/or modify //
// it under the terms of the GNU General Public License as published by //
// the Free Software Foundation, either version 3 of the License, or    //
// (at your option) any later version.                                  //
//                                                                      //
// This program is distributed in the hope that it will be useful,      //
// but WITHOUT ANY WARRANTY; without even the implied warranty of       //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        //
// GNU General Public License for more details.                         //
//////////////////////////////////////////////////////////////////////////

#include "Precompiled.h"

#include "TextureManager.h"
#include "ColorConverter.h"
#include "Dialogs.h"

#include <wx/image.h>



TextureManager::TextureManager() : atlas()
	{
	}


TextureManager::~TextureManager()
	{
		for( map_type_iter it = atlas.begin(); it != atlas.end(); ++it )
		{
			(*it).second->Dispose();
			delete (*it).second;
		}
	}


int TextureManager::LoadImageFromFile( const wxString& file, uint wrapmode, uint minfilter, uint magfilter, bool mipmaps )
	{
		wxImage image;
		if( !image.LoadFile( file.c_str() ) )
			return -1;

		ubyte *data = ColorConverter::ConvertImageToRGBA( &image );
		if( !data )
			return -2;

		const uint w = (uint)image.GetWidth();
		const uint h = (uint)image.GetHeight();
		const uint mip = (mipmaps ? 1 : 0);

		Image *image = new Image( wrapmode, minfilter, magfilter, mip, w, h, data );
		ColorConverter::DeleteData(data);
/*
		ColorConverter::RemoveTileSeparationLinesOldFormat(image->pixels);
		image->Update();

		wxImage* fileimage = ColorConverter::ConvertPixmapToImage(image);
		Dialog::SaveImageDialog( fileimage, wxString() );
		delete fileimage;
*/

		AddTexture( file, image );
		return 0;
	}


int TextureManager::LoadImageFromData( const wxString& name, const ubyte *const pixels, uint w, uint h )
	{
		return LoadImageFromData( name, pixels, w, h, GL_CLAMP, GL_NEAREST, GL_NEAREST, false );
	}


int TextureManager::LoadImageFromData( const wxString& name, const ubyte *const pixels, uint w, uint h, uint wrapmode, uint minfilter, uint magfilter, bool mipmaps )
	{
		uint mip = (mipmaps ? 1 : 0);
		Image *image = new Image( wrapmode, minfilter, magfilter, mip, w, h, pixels );

		AddTexture( name, image );
		return 0;
	}


void TextureManager::AddTexture( const wxString& name, Image *image )
	{
		atlas.insert( pair_type(name, image) );
		//atlas[ name ] = image;
	}


GLuint TextureManager::GetTexture( const wxString& name ) const
	{
		map_type_const_iter it = atlas.find( name );
		if( it == atlas.end() )
			return 0;

		return it->second->GetTexture();
	}


Image* TextureManager::GetImage( const wxString& name )
	{
		map_type_iter it = atlas.find( name );
		if( it == atlas.end() )
			return 0;

		return it->second;
	}


const Image* TextureManager::GetImage( const wxString& name ) const
	{
		map_type_const_iter it = atlas.find( name );
		if( it == atlas.end() )
			return 0;

		return it->second;
	}



