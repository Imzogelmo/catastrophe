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

#include "ItemDrop.h"
#include "Inventory.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//               ItemDrop
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ItemDrop::SetRate( int rate )
{
	m_dropRate = fc::clamp(rate, 0, m_maxRate);
}


void ItemDrop::SetMaxRate( int rate )
{
	m_maxRate = fc::max(0, rate);
	m_dropRate = fc::clamp(m_dropRate, 0, m_maxRate);
}


void ItemDrop::SetMinAmount( int min )
{
	if( min > m_max )
		min = m_max;

	m_min = min;
}


void ItemDrop::SetMaxAmount( int max )
{
	if( max < m_min )
		m_min = max;

	m_max = max;
}


bool ItemDrop::TestDrop( float modifier ) const
{
	int n = m_dropRate;
	if( modifier != 1.0f )
		n = fc::clamp( (int)fc::round((float)m_dropRate * modifier), 0, m_maxRate );

	return fc::probability(n, m_maxRate);
}


int ItemDrop::TestAmount( float modifier ) const
{
	int n = fc::rand(GetMinAmount(), GetMaxAmount());
	if( modifier != 1.0f )
		n = (int)fc::round((float)n * modifier);

	return n;
}


void ItemDrop::Validate()
{
	m_dropRate = fc::clamp(m_dropRate, 0, m_maxRate);
	if( m_max < 0 )
		m_max = 0;
	m_min = fc::clamp(m_min, 0, m_max );
}


void ItemDrop::SerializeXml(XmlWriter* xml)
{
	Validate();
	xml->BeginNode("ItemDrop");
	xml->SetInt("index", m_itemIndex);
	xml->SetInt("rate", m_dropRate);
	xml->SetInt("max_rate", m_maxRate);
	xml->SetInt("min", m_min);
	xml->SetInt("max", m_max);
	xml->EndNode();
}


void ItemDrop::DeserializeXml(XmlReader* xml)
{
	m_itemIndex = xml->GetInt("index");
	m_dropRate = xml->GetInt("rate");
	m_maxRate = xml->GetInt("max_rate");
	m_min = xml->GetInt("min");
	m_max = xml->GetInt("max");
}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//             ItemDropSet
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ItemDropSet::Add( const ItemDrop& drop )
{
	m_item_drops.push_back(drop);
}


void ItemDropSet::Remove( size_t index )
{
	if( index < m_item_drops.size() )
	{
		m_item_drops.erase_at(index);
	}
}


void ItemDropSet::GetItemDrops( Inventory& out_drops )
{
	for( vec_type::iterator it = m_item_drops.begin(); it != m_item_drops.end(); ++it )
	{
		if( it->item != 0 && it->TestDrop() )
		{
			int n = it->TestAmount();
			if(n > 0)
			{
				InventoryItem item(it->item, n);
				out_drops.Add(item);

				if(!m_allow_multiple_drops)
					return;
			}
		}
	}
}


void ItemDropSet::SerializeXml( XmlWriter* xml )
{
	xml->BeginNode("ItemDropSet");
	xml->SetUInt("count", m_item_drops.size());
	xml->SetBool("multiple", m_allow_multiple_drops);

	for( vec_type::iterator it = m_item_drops.begin(); it != m_item_drops.end(); ++it )
	{
		it->SerializeXml(xml);
	}

	xml->EndNode();
}


void ItemDropSet::DeserializeXml( XmlReader* xml )
{
	size_t count = (size_t)fc::clamp( xml->GetInt("count"), 0, 8 );
	m_allow_multiple_drops = xml->GetBool("multiple");

	bool hasData = false;
	m_item_drops.resize(count);
	for( vec_type::iterator it = m_item_drops.begin(); it != m_item_drops.end(); ++it )
	{
		if( xml->NextChild("ItemDrop") )
		{
			it->DeserializeXml(xml);
			hasData = true;
		}
	}

	if( count > 0 && hasData )
		xml->SetToParent();
}


