
#pragma once

#include <fc/vector.h>
#include "../Common.h"


template<class T>
class ScriptVector : public fc::vector<T>
{
public:
	typedef fc::vector<T>			vec_type;
	typedef fc::vector<T>			base_type;
	typedef ScriptVector<T>			this_type;

	ScriptVector() : base_type(), ref_count(1), type(0) {}
	ScriptVector( int size ) : base_type(size), ref_count(1), type(0) {}
	ScriptVector( const this_type& other ) : base_type(), ref_count(1), type(0)
	{
		base_type::operator =(other);
	}

	~ScriptVector()
	{
		if( type )
			type->Release();
	}

	void AddTypeRef( asIObjectType *objType )
	{
		type = objType;
		type->AddRef();
	}

	this_type& operator = ( const this_type& rhs )
	{
		base_type::operator =(rhs);
		return *this;
	}

	bool OutOfBounds( int index )
	{
		if( (size_t)index >= base_type::size() )
		{
			asIScriptContext* context = asGetActiveContext();
			if( context )
				context->SetException("vector index out of bounds.");
			return false;
		}

		return true;
	}

	void PushBack( const T& val )
	{
		base_type::push_back( val );
	}

	void PopBack()
	{
		if( base_type::empty() )
			return;

		base_type::pop_back();
	}

	void PushFront( const T& val )
	{
		Insert1( 0, val );
	}

	void PopFront()
	{
		Erase1(0);
	}

	void Insert1( int loc, const T& val )
	{
		if( OutOfBounds(loc) )
			return;

		base_type::insert_at( (size_t)loc, val );
	}

	void Insert2( int loc, int amount, const T& val )
	{
		if( OutOfBounds(loc + amount) )
			return;

		base_type::insert_at( (size_t)loc, (size_t)amount, val );
	}

	void Erase1( int loc )
	{
		if( OutOfBounds(loc) )
			return;

		base_type::erase_at( (size_t)loc );
	}

	void Erase2( int loc, int amount )
	{
		if( OutOfBounds(loc) )
			return;

		base_type::erase_at( (size_t)loc, (size_t)amount );
	}

	T* At( int index )
	{
		if( OutOfBounds(index) )
			return 0;

		return &base_type::operator[](index);
	}

	T* Front()
	{
		if( OutOfBounds(1) )
			return 0;

		return &base_type::front();
	}

	T* Back()
	{
		if( OutOfBounds(1) )
			return 0;

		return &base_type::back();
	}

	void Reserve( int reserve )
	{
		base_type::reserve( (size_t)reserve );
	}

	void Resize( int newSize )
	{
		base_type::resize( (size_t)newSize );
	}

	void Clear()
	{
		base_type::clear();
	}

	bool Empty()
	{
		return base_type::empty();
	}

	int Size()
	{
		return base_type::size();
	}

	// GC behaviors
	void AddRef()
	{
		++ref_count;
	}

	void Release()
	{
		if( --ref_count == 0 )
		{
			delete this;
		}
	}

protected:
	int				ref_count;
	asIObjectType*	type;
};


