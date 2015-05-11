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

#include <Catastrophe/Core/PlatformMath.h>
#include <Catastrophe/Core/Random.h>
#include <Catastrophe/Core/IO/AttributeReader.h>
#include <Catastrophe/Core/IO/AttributeWriter.h>

#include "ItemDropSet.h"



ItemDropSet::ItemDropSet( bool multipleDrops ) :
	m_itemDrops(),
	m_size(0),
	m_allowMultipleDrops(multipleDrops)
{
}


void ItemDropSet::Add( const ItemDrop& drop )
{
	if( m_size < MAX_ITEM_DROPS )
	{
		m_itemDrops[m_size] = drop;
		m_size++;
	}
}


void ItemDropSet::Remove()
{
	if( m_size > 0 )
	{
		m_size--;
		m_itemDrops[m_size] = ItemDrop();
	}
}


void ItemDropSet::Clear()
{
	for( int i(m_size); i >= 0; --i )
		m_itemDrops[i] = ItemDrop();

	m_size = 0;
}


ItemDrop& ItemDropSet::operator []( u32 index )
{
	ASSERT(index < MAX_ITEM_DROPS);
	return m_itemDrops[index];
}


const ItemDrop& ItemDropSet::operator []( u32 index ) const
{
	ASSERT(index < MAX_ITEM_DROPS);
	return m_itemDrops[index];
}


void ItemDropSet::Serialize( AttributeWriter* f )
{
	f->BeginNode("ItemDropSet");
	f->SetAttribute("count", m_size);
	f->SetAttribute("multiple", m_allowMultipleDrops);

	for( u32 i(0); i < m_size; ++i )
	{
		m_itemDrops[i].Serialize(f);
	}

	f->EndNode();
}


void ItemDropSet::Deserialize( AttributeReader* f )
{
	u32 numDrops = 0;

	f->GetAttribute("count", numDrops);
	numDrops = (u32)Clamp<int>( numDrops, 0, MAX_ITEM_DROPS );
	f->GetAttribute("multiple", m_allowMultipleDrops);

	for( u32 i(0); i < numDrops; ++i )
	{
		if( f->NextChild("ItemDrop") )
		{
			m_itemDrops[i].Deserialize(f);
		}
	}

	if( f->GetCurrentNodeName() == "ItemDrop" )
		f->SetToParent();
}


