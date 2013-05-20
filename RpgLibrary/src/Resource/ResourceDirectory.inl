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


fc::string ResourceDirectory::GetDirectory( BaseDirectoryType type ) const
{
	ASSERT(type < BaseDir_Max);
	return m_root + m_baseDirectory[type];
}


fc::string ResourceDirectory::GetTextureDirectory() const
{
	return GetDirectory(BaseDir_Textures);
}


fc::string ResourceDirectory::GetFontDirectory() const
{
	return GetDirectory(BaseDir_Fonts);
}


fc::string ResourceDirectory::GetShaderDirectory() const
{
	return GetDirectory(BaseDir_Shaders);
}


fc::string ResourceDirectory::GetMapDirectory() const
{
	return GetDirectory(BaseDir_Maps);
}


fc::string ResourceDirectory::GetTilesetDirectory() const
{
	return GetDirectory(BaseDir_Tilesets);
}


fc::string ResourceDirectory::GetDataDirectory() const
{
	return GetDirectory(BaseDir_Data);
}

