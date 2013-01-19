
#pragma once

template <size_t N>
struct Flags
{
	typedef Flags<N> this_type;
	enum : size_t
	{
		MaxBits = N
	};

};


template <>
struct Flags<32>
{
	typedef Flags<32> this_type;
	enum
	{
		MaxBits = 32
	};

	int bits;

	Flags(int bitData = 0) : bits(bitData)
	{}

	bool GetBit(int flag)
	{
		return( (bits & (1 << flag)) != 0 );
	}

	void SetBit(int flag, bool value)
	{
		if(value)
			bits |= (1 << flag);
		else
			bits &= ~(1 << flag);
	}

	this_type& operator |=(const this_type& rhs)
	{
		bits |= rhs.bits;
		return *this;
	}

	this_type& operator &=(const this_type& rhs)
	{
		bits &= rhs.bits;
		return *this;
	}

	this_type& operator ^=(const this_type& rhs)
	{
		bits ^= rhs.bits;
		return *this;
	}

	this_type operator |(const this_type& rhs) const
	{
		return this_type(bits | rhs.bits);
	}

	this_type operator &(const this_type& rhs) const
	{
		return this_type(bits & rhs.bits);
	}

	this_type operator ^(const this_type& rhs) const
	{
		return this_type(bits ^ rhs.bits);
	}

};


typedef Flags<32>	Flags32;


