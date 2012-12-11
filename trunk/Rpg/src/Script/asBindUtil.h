
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


} //namespace script
