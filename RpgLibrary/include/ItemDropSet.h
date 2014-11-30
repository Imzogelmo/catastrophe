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
	ItemDropSet( bool multipleDrops = false );

	void Add( const ItemDrop& drop );
	void Remove();
	void Clear();
	u32 Size() { return m_size; }

	ItemDrop& operator []( u32 index );
	const ItemDrop& operator []( u32 index ) const;

	virtual void Serialize( AttributeWriter* f );
	virtual void Deserialize( AttributeReader* f );

protected:
	ItemDrop	m_itemDrops[MAX_ITEM_DROPS];
	u32			m_size;
	bool		m_allowMultipleDrops;

};


