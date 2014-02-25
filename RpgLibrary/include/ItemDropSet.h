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

#include "RpgCommon.h"
#include "ItemDrop.h"


class RPG_API ItemDropSet
{
public:
	ItemDropSet( bool multiple_drops = false );

	void Add( const ItemDrop& drop );
	void Remove();
	void Clear();
	size_t Size() { return m_size; }

	ItemDrop& operator []( size_t index );
	const ItemDrop& operator []( size_t index ) const;

	virtual void SerializeXml( AttributeWriter* f );
	virtual void DeserializeXml( AttributeReader* f );

protected:
	ItemDrop	m_item_drops[MAX_ITEM_DROPS];
	size_t		m_size;
	bool		m_allow_multiple_drops;

};


