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

#include "Catastrophe/Core/Containers/String.h"


enum BaseDirectoryType
{
	BaseDirectoryType_Textures,
	BaseDirectoryType_Tiles,
	BaseDirectoryType_Backgrounds,
	BaseDirectoryType_Fonts,
	BaseDirectoryType_Shaders,
	BaseDirectoryType_Bgm,
	BaseDirectoryType_Sfx,
	BaseDirectoryType_Maps,
	BaseDirectoryType_Tilesets,
	BaseDirectoryType_Database,
	BaseDirectoryType_Scripts,
	BaseDirectoryType_ScriptDefs,
	BaseDirectoryType_Max
};

static const char* defaultBaseDirectoryStrings[BaseDirectoryType_Max] =
{
	"Textures/",
	"Tiles/",
	"Backgrounds/",
	"Fonts/",
	"Shaders/",
	"Bgm/",
	"Sfx/",
	"Maps/",
	"Tilesets/",
	"Database/",
	"Scripts/",
	"Scripts/defs/"
};


class ResourceDirectory
{
public:
	ResourceDirectory();

	void SetDirectory( BaseDirectoryType type, const String& directory );
	void SetRootDirectory( const String& directory );

	String GetRootDirectory() const { return m_root; }
	String GetDirectory( BaseDirectoryType type ) const;
	String GetTextureDirectory() const;
	String GetTileDirectory() const;
	String GetBackgroundDirectory() const;
	String GetFontDirectory() const;
	String GetShaderDirectory() const;
	String GetMapDirectory() const;
	String GetTilesetDirectory() const;
	String GetDataDirectory() const;
	String GetScriptDirectory() const;
	String GetScriptDefineDirectory() const;

	// Debugging
	void DebugSetAllBaseDirectoriesToSingleDirectory( const String& directory );

protected:
	String m_root;
	String m_baseDirectory[BaseDirectoryType_Max];

};


