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

#include <fc/vector.h>
#include <Catastrophe/Graphics/Texture.h>
#include <Catastrophe/Graphics/Font.h>

#include "Common.h"


class Resource
{
public:
	//we don't want a template type for simple pointers.
	typedef void* pointer;

	pointer			ptr;
	fc::string		name;

	Resource( pointer p = 0, const fc::string& filename = "" )
		: ptr(p), name(filename)
	{}

};



class ResourceManager
{
public:
	typedef	fc::vector<Resource>		texture_vec_type;
	typedef	fc::vector<Resource>		font_vec_type;

	ResourceManager();
	~ResourceManager();

	void SetBaseDirectory( const fc::string& directory );
	void SetTextureDirectory( const fc::string& directory );
	void SetFontDirectory( const fc::string& directory );

	const fc::string& GetBaseDirectory() const { return m_baseDirectory; };
	const fc::string& GetTextureDirectory() const { return m_textureDirectory; };
	const fc::string& GetFontDirectory() const { return m_fontDirectory; };


	Texture*	LoadTexture( const fc::string& filename );
	Font*		LoadFont( const fc::string& filename, int faceSize );


	// warning - this will invalidate all existing pointers to these resources!
	// use at your own risk.
	void DeleteResources();
	void DeleteTexture( Texture* texture );
	void DeleteFont();

	void DeleteTextures();
	void DeleteFonts();

	//get functions have a linear time cost.
	Texture* GetTexture( const fc::string& filename );
	Font* GetFont( const fc::string& filename );


	//when we lose OpenL context or switch video modes (ie; to-from fullscreen),
	//this invalidates all gpu data, so we must reload them.
	// *this will not invalidate any pointers*
	void ReloadGraphicsResources();

protected:
	texture_vec_type		m_textures;
	font_vec_type			m_fonts;

	fc::string				m_baseDirectory;
	fc::string				m_textureDirectory;
	fc::string				m_fontDirectory;

};


