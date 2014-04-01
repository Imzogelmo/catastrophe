
#pragma once

#ifndef __DEFINED__


//----------------------------------
// * Array
//----------------------------------

template <class T>
class array
{
public:
	array();
	array( int x );
	array( int y, int x );
	array( int z, int y, int x );
	array( const array<T>& );

	T& at( int x );
	T& at( int y, int x );
	T& at( int z, int y, int x );

	void resize( int x );
	void resize( int y, int x );
	void resize( int z, int y, int x );

	void assign( const T& val );
	void assign( int begin, int n, const T& val );

	int offset( int y, int x ) const;
	int offset( int z, int y, int x ) const;

	bool empty() const;
	int size() const;

	array& operator = ( const array& );
	//bool operator == ( const array& ) const;
	//bool operator != ( const array& ) const;

};


#endif

