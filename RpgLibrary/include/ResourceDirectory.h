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
	BaseDir_Data,
	BaseDir_Scripts,
	BaseDir_ScriptDefs,
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
	"tilesets/",
	"data/",
	"scripts/",
	"scripts/defs/"
};


class ResourceDirectory
{
public:
	ResourceDirectory();

	void SetRootDirectory( const String& directory );
	const String& GetRootDirectory() const { return m_root; }

	String GetDirectory( BaseDirectoryType type ) const;
	String GetTextureDirectory() const;
	String GetFontDirectory() const;
	String GetShaderDirectory() const;
	String GetMapDirectory() const;
	String GetTilesetDirectory() const;
	String GetDataDirectory() const;
	String GetScriptDirectory() const;
	String GetScriptDefineDirectory() const;

	// Testing only
	void DebugSetAllBaseDirectoriesToSingleDirectory( const String& directory );

protected:
	String m_root;
	String m_baseDirectory[BaseDir_Max];

};


