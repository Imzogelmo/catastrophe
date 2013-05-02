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

#include "TilesetManager.h"


TilesetManager::~TilesetManager()
{
	DeleteTilesets();
}


void TilesetManager::DeleteTilesets()
{
	for( vec_type::iterator it = m_tilesets.begin(); it != m_tilesets.end(); ++it )
		delete *it;

	m_tilesets.clear();
}


bool TilesetManager::DeleteTileset( Tileset* tileset )
{
	for( vec_type::iterator it = m_tilesets.begin(); it != m_tilesets.end(); ++it )
	{
		if( tileset == *it )
		{
			delete *it;
			m_tilesets.erase(it);

			//decrement tileset id
			for( ; it != m_tilesets.end(); ++it )
			{
				(*it)->SetId( (*it)->GetId() - 1 );
			}

			return true;
		}
	}

	return false;
}


Tileset* TilesetManager::CreateTileset( const fc::string& name )
{
	Tileset* tileset = GetTileset(name);

	//check for empty or existing name
	if( name.empty() || tileset != 0 )
		return 0;

	tileset = new Tileset(this, name);
	tileset->SetId( (int)m_tilesets.size() );
	m_tilesets.push_back(tileset);

	return tileset;
}


Tileset* TilesetManager::GetTileset( size_t index ) const
{
	if( index < m_tilesets.size() )
		return m_tilesets[index];

	return 0;
}


Tileset* TilesetManager::GetTileset( const fc::string& name ) const
{
	for( vec_type::const_iterator it = m_tilesets.begin(); it != m_tilesets.end(); ++it )
	{
		if( (*it)->GetName() == name )
			return *it;
	}

	return 0;
}


void TilesetManager::SetDirectory( const fc::string& directory )
{
	//ASSERT(m_tilesets.empty());
	m_directory = directory;
}


bool TilesetManager::LoadTilesetXml( const fc::string& filename )
{
	Tileset* tileset = CreateTileset(filename);
	if( tileset )
	{
		if( tileset->DeserializeXml(m_directory, filename) )
			return true;
	}

	return false;
}


bool TilesetManager::SaveTilesetXml( Tileset* tileset )
{
	if( tileset->SerializeXml(m_directory) )
	{
		Log("Error saving tileset (%s)(%s).", m_directory.c_str(), tileset->GetName() );
		return false;
	}

	return false;
}


bool TilesetManager::SaveAllTilesetsXml()
{
	bool completeSuccess = true;
	for( vec_type::iterator it = m_tilesets.begin(); it != m_tilesets.end(); ++it )
	{
		if( !SaveTilesetXml(*it) )
			completeSuccess = false;
	}

	return completeSuccess;
}



