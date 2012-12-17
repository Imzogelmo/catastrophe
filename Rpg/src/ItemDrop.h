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

#include <fc/fixed_vector.h>
#include "Common.h"
#include "Item.h"


/**
 * Item Drop: describes the chance of an entity dropping n items
 * between min/max at a probability of rate out of maxRate. Ex;
 * a drop rate of 2 out of 50 would result in a 1 in 25 chance of drop.
 */
class ItemDrop
{
public:
	ItemDrop(int itemIndex = 0, int dropRate = 0, int maxRate = 100, int minAmount = 1, int maxAmount = 1) :
		m_itemIndex(itemIndex), m_dropRate(dropRate), m_maxRate(maxRate), m_min(minAmount), m_max(maxAmount)
	{
		Validate();
	}

	void SetItem( int index ) { m_itemIndex = index; }
	void SetRate( int rate );
	void SetMaxRate( int rate );
	void SetMinAmount( int min );
	void SetMaxAmount( int max );

	int GetMinAmount() const { return m_min; }
	int GetMaxAmount() const { return m_max; }
	int GetRate() const { return m_dropRate; }
	int GetMaxRate() const { return m_maxRate; }

	bool TestDrop( float modifier = 1.0f ) const;
	int TestAmount( float modifier = 1.0f ) const;

	void Validate();

	void SerializeXml(XmlWriter* xml);
	void DeserializeXml(XmlReader* xml);

	Item* item; //...remove me still.
protected:
	int		m_itemIndex;
	int		m_dropRate;
	int		m_maxRate;
	int		m_min;
	int		m_max;

};


class ItemDropSet
{
public:
	typedef fc::fixed_vector<ItemDrop, 8> vec_type;

	ItemDropSet( bool multiple_drops = false)
		: m_item_drops(), m_allow_multiple_drops(multiple_drops)
	{}

	virtual ~ItemDropSet()
	{}

	void Add( const ItemDrop& drop );
	void Remove( size_t index );
	void GetItemDrops( Inventory& out_drops );

	virtual void SerializeXml( XmlWriter* xml );
	virtual void DeserializeXml( XmlReader* xml );

protected:
	vec_type	m_item_drops;
	bool		m_allow_multiple_drops;

};


