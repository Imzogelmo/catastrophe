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

#include <fc/multi_array.h>
#include "Common.h"
#include "ScriptEngine.h"


template<class T>
class ScriptArray : public fc::multi_array<T>
{
public:
	typedef fc::multi_array<T>			base_type;
	typedef base_type					array_type;
	typedef ScriptArray<T>				this_type;

	ScriptArray() : base_type(), m_refCount(1), m_objType(0) {}
	ScriptArray( int x ) : base_type(x), m_refCount(1), m_objType(0) {}
	ScriptArray( int y, int x ) : base_type(y, x), m_refCount(1), m_objType(0) {}
	ScriptArray( int z, int y, int x ) : base_type(z, y, x), m_refCount(1), m_objType(0) {}
	ScriptArray( const ScriptArray<T>& other ) : base_type(), m_refCount(1), m_objType(0)
	{
		base_type::operator =(other);
	}

	~ScriptArray()
	{
		if( m_objType )
			m_objType->Release(); //...?? needed??
	}

	void AddTypeRef( asIObjectType *objType )
	{
		m_objType = objType;
		m_objType->AddRef();
	}

	ScriptArray<T>& operator = ( const ScriptArray<T>& rhs )
	{
		base_type::operator =(rhs);
		return *this;
	}

	//TODO: this should be a macro, or at least a global function.
	bool OutOfBounds( int index )
	{
		if( (size_t)index >= base_type::size() )
		{
			asIScriptContext* context = asGetActiveContext();
			if(context)
			{
				ScriptEngine* scriptEngine = (ScriptEngine*)context->GetEngine()->GetUserData();
				if(scriptEngine)
				{
					scriptEngine->SetException(context, "array index out of bounds.");
				}
			}
			return true;
		}

		return false;
	}

	T* At1( int x )
	{
		if( OutOfBounds(x) )
			return 0;

		return &base_type::operator[](x);
	}

	T* At2( int y, int x )
	{
		const size_t offset = base_type::offset(y, x);
		if( OutOfBounds(offset) )
			return 0;

		return &base_type::operator[](offset);
	}

	T* At3( int z, int y, int x )
	{
		const size_t offset = base_type::offset(z, y, x);
		if( OutOfBounds(offset) )
			return 0;

		return &base_type::operator[](offset);
	}


	//TODO: all these can be bound to the base class..
	int Size()
	{
		return (int)base_type::size();
	}

	void Resize1( int x )
	{
		base_type::resize(x);
	}

	void Resize2( int y, int x )
	{
		base_type::resize(y, x);
	}

	void Resize3( int z, int y, int x )
	{
		base_type::resize(z, y, x);
	}

	bool Empty()
	{
		return base_type::empty();
	}

	int Offset2( int y, int x )
	{
		return base_type::offset(y, x);
	}

	int Offset3( int z, int y, int x )
	{
		return base_type::offset(z, y, x);
	}

	void AssignAll( const T& value )
	{
		base_type::assign(value);
	}

	void Assign( int pos, int n, const T& value )
	{
		size_t last = size_t(pos + n);
		if( last > base_type::size() )
			return; //todo

		base_type::assign( base_type::begin() + pos, base_type::begin() + last, value );
	}

	void AddRef()
	{
		++m_refCount;
	}

	void Release()
	{
		if( --m_refCount == 0 )
		{
			delete this;
		}
	}

protected:
	int				m_refCount;
	asIObjectType*	m_objType;
};


