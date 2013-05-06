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
	ResourceDirectory();

	void SetRootDirectory( const fc::string& directory ) { m_root = directory; }
	const fc::string& GetRootDirectory( BaseDirectoryType type ) const { return m_root; }

	//void GetDirectory( BaseDirectoryType type ) const;
	fc::string GetDirectory( BaseDirectoryType type ) const;
	fc::string GetTextureDirectory() const;
	fc::string GetFontDirectory() const;
	fc::string GetShaderDirectory() const;
	fc::string GetMapDirectory() const;
	fc::string GetTilesetDirectory() const;

protected:
	fc::string m_root;
	fc::string m_baseDirectory[BaseDir_Max];

};


