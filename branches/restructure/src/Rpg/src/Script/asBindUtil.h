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


namespace script
{

	//these are for uninstantiable reference classes.
	static void DummyAddRef(void *) {}
	static void DummyReleaseRef(void *) {}

	//////////////////////////////////////////
	// Value Type Constructors
	//////////////////////////////////////////

	template <class T> inline
	void ValueConstruct( T *self )
	{
		new (self) T();
	}

	template <class T> inline
	void ValueCopyConstruct( const T &other, T *self )
	{
		new (self) T(other);
	}

	template <class T> inline
	void ValueDestruct( T *self )
	{
		self->~T();
	}

	template <class T, class U> inline
	void ValueCopyConstruct( const U &other, T *self )
	{
		new (self) T(other);
	}

	template <class T, class BuiltInType> inline
	void ValueInitConstruct_1Arg( BuiltInType a, T *self )
	{
		new (self) T(a);
	}

	template <class T, class BuiltInType> inline
	void ValueInitConstruct_2Arg( BuiltInType a, BuiltInType b, T *self )
	{
		new (self) T(a, b);
	}

	template <class T, class BuiltInType> inline
	void ValueInitConstruct_3Arg( BuiltInType a, BuiltInType b, BuiltInType c, T *self )
	{
		new (self) T(a, b, c);
	}

	template <class T, class BuiltInType> inline
	void ValueInitConstruct_4Arg( BuiltInType a, BuiltInType b, BuiltInType c, BuiltInType d, T *self )
	{
		new (self) T(a, b, c, d);
	}

	template <class T, class U> inline
	T& ValueAssignment( const U &other, T *self )
	{
		*self = other;
		return *self;
	}



	//////////////////////////////////////////
	// Reference Counted Constructors
	//////////////////////////////////////////

	template <class T, class U> inline
	U* RefCast( T* self )
	{
		U* ret = dynamic_cast<U*>(self);
		if(!ret)
			return 0; //assert

		return ret;
	}

	template <class T> inline
	T* RefConstruct()
	{
		T* t = new T();
		return t;
	}

	template <class T> inline
	T* RefCopyConstruct( const T &other )
	{
		T* t = new T(other);
		return t;
	}

	template <class T, class U> inline
	T* RefCopyConstruct( const U &other )
	{
		T* t = new T(other);
		return t;
	}

	template <class T, class BuiltInType> inline
	T* RefInitConstruct_1Arg( BuiltInType a )
	{
		T* t = new T(a);
		return t;
	}

	template <class T, class BuiltInType> inline
	T* RefInitConstruct_2Arg( BuiltInType a, BuiltInType b)
	{
		T* t = new T(a, b);
		return t;
	}

	template <class T, class BuiltInType> inline
	T* RefInitConstruct_3Arg( BuiltInType a, BuiltInType b, BuiltInType c )
	{
		T* t = new T(a, b, c);
		return t;
	}

	template <class T, class BuiltInType> inline
	T* RefInitConstruct_4Arg( BuiltInType a, BuiltInType b, BuiltInType c, BuiltInType d )
	{
		T* t = new T(a, b, c, d);
		return t;
	}

	template <class T, class U> inline
	T& RefAssignment( const U &other, T *self )
	{
		*self = other;
		return *self;
	}



	//...
	template <class T, class U> inline
	T& ScopedAssignment( const U &other, T *self )
	{
		*self = other;
		return *self;
	}


} //namespace script
