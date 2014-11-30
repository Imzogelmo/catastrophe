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

#include "ResourceDirectory.h"


ResourceDirectory::ResourceDirectory()
{
	m_root = "data/";

	for( int i(0); i < BaseDir_Max; ++i )
		m_baseDirectory[i] = default_base_directories[i];
}


void ResourceDirectory::SetRootDirectory( const String& directory )
{
	m_root = directory;

	// Add trailing slash to the directory if it does not contain one.
	if( !m_root.empty() && (m_root.back() != '/' && m_root.back() != '\\') )
		m_root.push_back('/');
}


String ResourceDirectory::GetDirectory( BaseDirectoryType type ) const
{
	ASSERT(type < BaseDir_Max);
	return m_root + m_baseDirectory[type];
}


String ResourceDirectory::GetTextureDirectory() const
{
	return GetDirectory(BaseDir_Textures);
}


String ResourceDirectory::GetFontDirectory() const
{
	return GetDirectory(BaseDir_Fonts);
}


String ResourceDirectory::GetShaderDirectory() const
{
	return GetDirectory(BaseDir_Shaders);
}


String ResourceDirectory::GetMapDirectory() const
{
	return GetDirectory(BaseDir_Maps);
}


String ResourceDirectory::GetTilesetDirectory() const
{
	return GetDirectory(BaseDir_Tilesets);
}


String ResourceDirectory::GetDataDirectory() const
{
	return GetDirectory(BaseDir_Data);
}


String ResourceDirectory::GetScriptDirectory() const
{
	return GetDirectory(BaseDir_Scripts);
}


String ResourceDirectory::GetScriptDefineDirectory() const
{
	return GetDirectory(BaseDir_ScriptDefs);
}


void ResourceDirectory::DebugSetAllBaseDirectoriesToSingleDirectory( const String& directory )
{
	for( int i(0); i < BaseDir_Max; ++i )
		m_baseDirectory[i] = directory;
}
