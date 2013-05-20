
#pragma once


struct Die
{
	int sides;
	int value;

	Die( int numSides = 6 );

	int Roll();
};


class DiceSet
{
public:
	DiceSet( const Die& die = Die(), int numDice = 1 );

	int NumDice() const { return m_numDice; }
	int NumDiceSides() const { return m_die.sides; }
	int GetLastRoll() const { return m_lastRoll; }

	int Roll();
	void SetNumDice( int numDice );
	void AddDie();
	void RemoveDie();

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

	DiceBag();

	size_t NumDice() const { return m_dice.size(); }
	int GetLastRoll() const { return m_lastRoll; }

	int Roll();
	void Add( const Die& die );
	void Remove( size_t index );

	Die& GetDie( size_t index ) { return m_dice.at(index); }
	const Die& GetDie( size_t index ) const { return m_dice[index]; }

protected:
	vec_type	m_dice;
	int			m_lastRoll;

};

