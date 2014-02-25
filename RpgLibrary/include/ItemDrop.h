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


/**
 * Item Drop: describes the chance of an entity dropping n items
 * between min/max at a probability of rate out of maxRate. Ex;
 * a drop rate of 2 out of 50 would result in a 1 in 25 chance of drop.
 */
class RPG_API ItemDrop
{
public:
	ItemDrop( int itemId = 0, int dropRate = 0, int maxRate = 100, int minAmount = 1, int maxAmount = 1 );

	void SetItem( int id ) { m_itemId = id; }
	void SetRate( int rate );
	void SetMaxRate( int rate );
	void SetMinAmount( int minAmount );
	void SetMaxAmount( int maxAmount );

	int GetMinAmount() const { return m_min; }
	int GetMaxAmount() const { return m_max; }
	int GetRate() const { return m_dropRate; }
	int GetMaxRate() const { return m_maxRate; }

	bool TestDrop( float modifier = 1.0f ) const;
	int TestAmount( float modifier = 1.0f ) const;

	void Validate();

	void SerializeXml( AttributeWriter* f );
	void DeserializeXml( AttributeReader* f );

protected:
	int		m_itemId;
	int		m_dropRate;
	int		m_maxRate;
	int		m_min;
	int		m_max;

};


