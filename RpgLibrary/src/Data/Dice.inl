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

#include "Catastrophe/Core/Containers/String.h"
#include "Dice.h"



Die::Die( int numSides = 6 ) :
	sides(numSides),
	value(numSides)
{
}


int Die::Roll()
{
	value = Random::Int(1, sides);
	return value;
}




// DiceSet

DiceSet::DiceSet( const Die& die = Die(), int numDice = 1 ) :
	m_die(die),
	m_numDice(numDice),
	m_lastRoll(0)
{
}

int DiceSet::Roll()
{
	m_lastRoll = 0;
	for( int i(0); i < m_numDice; ++i )
		m_lastRoll += m_die.Roll();

	return m_lastRoll;
}


void DiceSet::SetNumDice( int numDice )
{
	if(numDice < 0)
		numDice = 0;
	m_numDice = numDice;
}

void DiceSet::AddDie()
{
	++m_numDice;
}


void DiceSet::RemoveDie()
{
	if(m_numDice > 0)
		--m_numDice;
}




// DiceBag

DiceBag::DiceBag() :
	m_dice(),
	m_lastRoll(0)
{
}


int DiceBag::Roll()
{
	m_lastRoll = 0;
	for( vec_type::Iterator it = m_dice.begin(); it < m_dice.end(); ++it )
		m_lastRoll += it->Roll();

	return m_lastRoll;
}


void DiceBag::Add( const Die& die )
{
	m_dice.Add(die);
}


void DiceBag::Remove( u32 index )
{
	if(index < m_dice.size() )
		m_dice.erase_at(index);
}

