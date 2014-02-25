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

#include <Catastrophe/Math/Math.h>
#include <Catastrophe/FileIO.h>
#include <fc/rand.h>

#include "ItemDropSet.h"



ItemDropSet::ItemDropSet( bool multiple_drops ) :
	m_item_drops(),
	m_size(0),
	m_allow_multiple_drops(multiple_drops)
{
}


void ItemDropSet::Add( const ItemDrop& drop )
{
	if( m_size < MAX_ITEM_DROPS )
	{
		m_item_drops[m_size] = drop;
		m_size++;
	}
}


void ItemDropSet::Remove()
{
	if( m_size > 0 )
	{
		m_size--;
		m_item_drops[m_size] = ItemDrop();
	}
}


void ItemDropSet::Clear()
{
	for( int i(m_size); i >= 0; --i )
		m_item_drops[i] = ItemDrop();

	m_size = 0;
}


ItemDrop& ItemDropSet::operator []( size_t index )
{
	ASSERT(index < MAX_ITEM_DROPS);
	return m_item_drops[index];
}


const ItemDrop& ItemDropSet::operator []( size_t index ) const
{
	ASSERT(index < MAX_ITEM_DROPS);
	return m_item_drops[index];
}


void ItemDropSet::SerializeXml( AttributeWriter* f )
{
	f->BeginNode("ItemDropSet");
	f->SetUInt("count", m_size);
	f->SetBool("multiple", m_allow_multiple_drops);

	for( size_t i(0); i < m_size; ++i )
	{
		m_item_drops[i].SerializeXml(f);
	}

	f->EndNode();
}


void ItemDropSet::DeserializeXml( AttributeReader* f )
{
	size_t numDrops = (size_t)fc::clamp<int>( f->GetInt("count"), 0, MAX_ITEM_DROPS );
	m_allow_multiple_drops = f->GetBool("multiple");

	for( size_t i(0); i < numDrops; ++i )
	{
		if( f->NextChild("ItemDrop") )
		{
			m_item_drops[i].DeserializeXml(f);
		}
	}

	if( f->GetCurrentNodeName() == "ItemDrop" )
		f->SetToParent();
}


