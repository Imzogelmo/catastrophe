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



ItemDrop::ItemDrop( int itemId, int dropRate, int maxRate, int minAmount, int maxAmount ) :
	m_itemId(itemId),
	m_dropRate(dropRate), 
	m_maxRate(maxRate),
	m_min(minAmount),
	m_max(maxAmount)
{
	Validate();
}


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


void ItemDrop::SerializeXml( XmlWriter* xml )
{
	Validate();
	xml->BeginNode("ItemDrop");
	xml->SetInt("index", m_itemId);
	xml->SetInt("rate", m_dropRate);
	xml->SetInt("max_rate", m_maxRate);
	xml->SetInt("min", m_min);
	xml->SetInt("max", m_max);
	xml->EndNode();
}


void ItemDrop::DeserializeXml( XmlReader* xml )
{
	m_itemId = xml->GetInt("index");
	m_dropRate = xml->GetInt("rate");
	m_maxRate = xml->GetInt("max_rate");
	m_min = xml->GetInt("min");
	m_max = xml->GetInt("max");
}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//             ItemDropSet
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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


void ItemDropSet::SerializeXml( XmlWriter* xml )
{
	xml->BeginNode("ItemDropSet");
	xml->SetUInt("count", m_size);
	xml->SetBool("multiple", m_allow_multiple_drops);

	for( size_t i(0); i < m_size; ++i )
	{
		m_item_drops[i].SerializeXml(xml);
	}

	xml->EndNode();
}


void ItemDropSet::DeserializeXml( XmlReader* xml )
{
	size_t count = (size_t)fc::clamp<int>( xml->GetInt("count"), 0, MAX_ITEM_DROPS );
	m_allow_multiple_drops = xml->GetBool("multiple");

	bool needsSetToParent = false;
	for( size_t i(0); i < count; ++i )
	{
		if( xml->NextChild("ItemDrop") )
		{
			m_item_drops[i].DeserializeXml(xml);
			needsSetToParent = true;
		}
	}

	if( needsSetToParent )
		xml->SetToParent();
}


