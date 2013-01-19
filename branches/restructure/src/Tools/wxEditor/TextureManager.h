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

#pragma once

#include <fc/vector_map.h>


// Class actually manages multiple texture atlas'
class TextureManager
{
public:
	static const uint TILE_SIZE = 16;


	typedef fc::pair<wxString, Image*> pair_type;
	typedef fc::vector_map<wxString, Image*> map_type;

	TextureManager();
	~TextureManager();

	int LoadImageFromFile( const wxString& file, uint wrapmode = GL_CLAMP, uint minfilter = GL_NEAREST, uint magfilter = GL_NEAREST, bool mipmaps = false );
	int LoadImageFromData( const wxString& name, const ubyte *const pixels, uint w, uint h );
	int LoadImageFromData( const wxString& name, const ubyte *const pixels, uint w, uint h, uint wrapmode, uint minfilter, uint magfilter, bool mipmaps );

	void AddTexture( const wxString& name, Image *image );


	GLuint GetTexture( const wxString& name ) const;
	Image* GetImage( const wxString& name );
	const Image* GetImage( const wxString& name ) const;


protected:
	map_type atlas;

};




