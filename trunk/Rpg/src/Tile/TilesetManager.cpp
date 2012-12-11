
#include "TilesetManager.h"


TilesetManager::~TilesetManager()
{
	Dispose();
}


void TilesetManager::Dispose()
{
	for( vec_type::iterator it = m_tilesets.begin(); it != m_tilesets.end(); ++it )
		delete *it;

	m_tilesets.clear();
}


bool TilesetManager::AddTileset( Tileset* tileset )
{
	//doesn't support unnamed tilesets.
	if( !tileset || tileset->GetName().empty() )
		return false;

	//tileset with the same name already exists.
	if( GetTileset(tileset->GetName()) != 0 )
		return false;

	m_tilesets.push_back(tileset);
	return true;
}


Tileset* TilesetManager::GetTileset( size_t index ) const
{
	if( insex < m_tilesets.size() )
		return m_tilesets[i];

	return 0;
}


Tileset* TilesetManager::GetTileset( const fc::string& name ) const
{
	for( vec_type::iterator it = m_tilesets.begin(); it != m_tilesets.end(); ++it )
	{
		if( (*it)->GetName() == name )
			return *it;
	}

	return 0;
}



