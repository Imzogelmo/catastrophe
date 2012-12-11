
#pragma once


struct Die
{
	int sides;
	int value;

	Die( int numSides = 6 ) :
		sides(numSides), value(numSides)
	{
	}

	int Roll()
	{
		value = fc::rand(1, sides);
		return value;
	}
};


class DiceSet
{
public:
	DiceSet( const Die& die = Die(), int numDice = 1 ) :
		m_die(die), m_numDice(numDice), m_lastRoll(0);
	{}

	int NumDice() const { return m_numDice; }
	int NumDiceSides() const { return m_die.sides; }
	int GetLastRoll() const { return m_lastRoll; }

	int Roll()
	{
		m_lastRoll = 0;
		for( int i(0); i < m_numDice; ++i )
			m_lastRoll += m_die.Roll();

		return m_lastRoll;
	}

	void SetNumDice( int numDice )
	{
		if(numDice < 0)
			numDice = 0;
		m_numDice = numDice;
	}

	void AddDie() { ++m_numDice; }
	void RemoveDie()
	{
		if(m_numDice > 0)
			--m_numDice;
	}

	void SetDie( const Die& die ) { m_die = die; }
	Die& GetDie() { return m_die; }
	const Die& GetDie() const { return m_die; }

protected:
	Die		m_die;
	int		m_numDice;
	int		m_lastRoll;

};



class DiceBag
{
public:
	typedef fc::vector<Die> vec_type;

	DiceBag() :
		m_dice(), m_lastRoll(0);
	{}

	size_t NumDice() const { return m_dice.size(); }
	int GetLastRoll() const { return m_lastRoll; }

	int Roll()
	{
		m_lastRoll = 0;
		for( vec_type::iterator it = m_dice.begin(); it < m_dice.end(); ++it )
			m_lastRoll += it->Roll();

		return m_lastRoll;
	}

	void Add( const Die& die )
	{
		m_dice.push_back(die);
	}

	void Remove( size_t index )
	{
		if(index < m_dice.size() )
			m_dice.erase_at(index);
	}

	Die& GetDie( size_t index ) { return m_dice.at(index); }
	const Die& GetDie( size_t index ) const { return m_dice[index]; }

	vec_type& GetDice() { return m_dice; }
	const vec_type& GetDice() const { return m_dice; }

protected:
	vec_type	m_dice;
	int			m_lastRoll;

};

