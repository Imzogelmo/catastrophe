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

#include <fc/dynamic_array.h>
#include <fc/fixed_vector.h>
#include <fc/string.h>

#include "RpgCommon.h"


template <class T>
class DataArray : public fc::dynamic_array<T>
{
public:
	typedef fc::dynamic_array<T>	base_type;
	typedef DataArray<T>			this_type;

	String				filename;
	const char*			rootName;
	const char*			itemName;
	ResourceDirectory*	resourceDirectory;

	DataArray();

	void InitializeType();

	/// Generate a unique id for each item in array.
	void GenerateIds();

	void Clear()
	{
		base_type::resize(0);
	}

	void SetResourceDirectory( ResourceDirectory* resourceDirectory )
	{
		this->resourceDirectory = resourceDirectory;
	}

	void SetNodeNames( const char* root, const char* item )
	{
		rootName = root;
		itemName = item;
	}

	void SetDefaultNodeNames()
	{
		this_type temp;
		SetNodeNames(temp.rootName, temp.itemName);
	}

	void SetFilename( const String& name )
	{
		filename = name;
	}

	int GetMemoryUsage() const
	{
		int memoryUsage = 0;
		for( u32 i(0); i < base_type::size(); ++i )
			memoryUsage += base_type::operator[](i).GetMemoryUsage();

		memoryUsage += (int)(base_type::size() * sizeof(T));
		memoryUsage += (int)filename.capacity();

		return memoryUsage;
	}

	NO_INLINE bool Serialize( const String& filename = "" );
	NO_INLINE bool Deserialize( const String& filename = "" );

};



class DatabaseArrayAnyProxyBase
{
public:
	virtual ~DatabaseArrayAnyProxyBase() {}

	virtual void Clear() = 0;
	virtual void GenerateIds() = 0;
	virtual void SetResourceDirectory( ResourceDirectory* resourceDirectory ) = 0;
	virtual void SetDefaultNodeNames() = 0;
	virtual bool Serialize( const String& filename = "" ) = 0;
	virtual bool Deserialize( const String& filename = "" ) = 0;
};


template <class T>
class DatabaseArrayAnyProxyType : public DatabaseArrayAnyProxyBase
{
public:
	DatabaseArrayAnyProxyType( T* ptr ) : p(ptr)
	{}

	void Clear() { }; //p->Clear(); }
	void GenerateIds() { p->GenerateIds(); }
	void SetResourceDirectory( ResourceDirectory* resourceDirectory ) { p->SetResourceDirectory(resourceDirectory); }
	void SetDefaultNodeNames()
	{
		T temp;
		p->SetNodeNames(temp.rootName, temp.itemName);
	}

	bool Serialize( const String& filename = "" ) { return p->Serialize(filename); }
	bool Deserialize( const String& filename = "" ) { return p->Deserialize(filename); }

private:
	T* p;
};


class DatabaseArrayAnyHolder
{
public:
	enum : u32
	{
		MaxBufferBytes = 256
	};

	typedef fc::fixed_vector<DatabaseArrayAnyProxyBase*, MaxBufferBytes / sizeof(DatabaseArrayAnyProxyBase*)> vec_type;
	typedef fc::aligned_buffer<MaxBufferBytes, FC_ALIGNOF(DatabaseArrayAnyProxyBase)> buffer_type;

	DatabaseArrayAnyHolder() :
		m_bin(),
		m_buffer(),
		m_offset(0)
	{
	}

	template <class T> inline
	void Add( T& arr )
	{
		ASSERT(m_offset < MaxBufferBytes);

		DatabaseArrayAnyProxyType<T>* p = new (m_buffer.data + m_offset) DatabaseArrayAnyProxyType<T>(&arr);
		m_offset += sizeof(DatabaseArrayAnyProxyType<T>);
		m_bin.push_back(p);
	}

	vec_type& GetVector() { return m_bin; }
	const vec_type& GetVector() const { return m_bin; }

private:
	vec_type		m_bin;
	buffer_type		m_buffer;
	u32				m_offset;

};


