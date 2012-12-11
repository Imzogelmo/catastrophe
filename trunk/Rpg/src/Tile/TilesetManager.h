
#pragma once

#include <fc/vector.h>
#include <fc/string.h>

#include "../Common.h"
#include "Tileset.h"


class TilesetManager
{
public:
	typedef fc::vector<Tileset*>		vec_type;

	~TilesetManager();

	void Dispose();
	bool AddTileset( Tileset* tileset );

	Tileset* operator [] ( size_t index ) const { return GetTileset(index); }
	Tileset* operator [] ( const fc::string& name ) const { return GetTileset(name); }
	Tileset* GetTileset( size_t index ) const;
	Tileset* GetTileset( const fc::string& name ) const;


protected:
	vec_type	m_tilesets;

};



