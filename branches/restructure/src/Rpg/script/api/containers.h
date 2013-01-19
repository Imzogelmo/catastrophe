
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


//----------------------------------
// * Vector
//----------------------------------
template<class T>
class vector
{
public:
	vector();
	vector( int size );
	vector( const vector<T>& );

	T& operator [] ( int index );
	const T& operator [] ( int index ) const;

	T& at( int index );
	const T& at( int index ) const;

	T& front();
	T& back();
	const T& front() const;
	const T& back() const;

	void push_back( const T& value );
	void push_front( const T& value );
	void pop_back();
	void pop_front();

	void insert( int loc, const T& value );
	void insert( int loc, int n, const T& value );
	void erase( int loc );
	void erase( int loc, int n );

	void resize( int new_size );
	void reserve( int capacity );

	void clear();
	bool empty() const;
	int size() const;

	vector& operator = ( const vector& );
};


//----------------------------------
// * String
//----------------------------------
class string
{
public:
	string();
	string( const string& );

	int size() const;
	int length() const;
	bool empty() const;
	void clear();
	void swap( string& str );
	void resize( int newSize );
	void push_back( uint8 _Char );
	void pop_back();

	uint8& operator [] ( int index );
	const uint8& operator [] ( int index ) const;

	string& append( const string &str );
	string& append( const string &str, int str_pos, int n );
	string& append( int amount, uint8 _Char );
	string& assign( const string &str );
	string& assign( const string &str, int str_pos, int n );
	string& assign( int amount, uint8 _Char );
	string& insert( int pos, const string &str );
	string& insert( int pos, const string &str, int str_pos, int n );
	string& erase( int pos );
	string& erase( int pos, int amount );
	string& replace( int pos, int amount, const string &str );
	string& replace( int pos, int amount, const string &str, int str_pos, int n );

	int find( const string &str ) const;
	int find( const string &str, int str_pos, int n ) const;
	int reverse_find( const string &str ) const;
	int reverse_find( const string &str, int str_pos, int n ) const;
	int find_first_of( const string &str ) const;
	int find_first_of( const string &str, int str_pos, int n ) const;
	int find_last_of( const string &str ) const;
	int find_last_of( const string &str,int str_pos, int n ) const;
	int find_first_not_of( const string &str ) const;
	int find_first_not_of( const string &str, int str_pos, int n ) const;
	int find_last_not_of( const string &str ) const;
	int find_last_not_of( const string &str, int str_pos, int n ) const;

	string substring( int pos, int amount ) const;

	bool operator == ( const string& ) const;
	bool operator != ( const string& ) const;

	string& operator = ( int val );
	string& operator = ( float val );
	string& operator = ( const string& );

	string& operator += ( int val );
	string& operator += ( float val );
	string& operator += ( const string& );

	string operator + ( int val ) const;
	string operator + ( float val ) const;
	string operator + ( const string& ) const;
	string operator + ( int val, const string& ) const;
	string operator + ( int val, const string& ) const;
	string operator + ( float val, const string& ) const;

	int		to_int() const;
	float	to_float() const;

	//void to_upper();
	//void to_lower();

};

