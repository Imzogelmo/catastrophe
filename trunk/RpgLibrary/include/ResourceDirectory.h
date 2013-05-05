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

#include <fc/string.h>


enum BaseDirectoryType
{
	BaseDir_Textures,
	BaseDir_Fonts,
	BaseDir_Shaders,
	BaseDir_Bgm,
	BaseDir_Sfx,
	BaseDir_Maps,
	BaseDir_Tilesets,
	BaseDir_Max
};

static const char* default_base_directories[BaseDir_Max] =
{
	"textures/",
	"fonts/",
	"shaders/",
	"bgm/",
	"sfx/",
	"maps/",
	"tilesets/"
};


class ResourceDirectory
{
public:

	ResourceDirectory()
	{
		m_root = "data/";

		for( int i(0); i < BaseDir_Max; ++i )
			m_baseDirectory[i] = default_base_directories[i];
	}

	void SetRootDirectory( const fc::string& directory ) { m_root = directory; }
	const fc::string& GetRootDirectory( BaseDirectoryType type ) const { return m_root; }

	void GetDirectory( BaseDirectoryType type, fc::string& outDir ) const
	{
		ASSERT(type < BaseDir_Max);
		outDir.clear();
		outDir.append(m_root).append(m_baseDirectory[type]);
	}

	void GetTextureDirectory( fc::string& outDir ) const
	{
		GetDirectory(BaseDir_Textures, outDir);
	}

	void GetFontDirectory( fc::string& outDir ) const
	{
		GetDirectory(BaseDir_Fonts, outDir);
	}

	void GetShaderDirectory( fc::string& outDir ) const
	{
		GetDirectory(BaseDir_Shaders, outDir);
	}

protected:
	fc::string m_root;
	fc::string m_baseDirectory[BaseDir_Max];

};


