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
#include <fc/fixed_tiny_vector.h>
#include <fc/string.h>

#include "RpgCommon.h"


template <class T>
class DataArray : public fc::dynamic_array<T>
{
public:
	typedef fc::dynamic_array<T>	base_type;

	fc::string			filename;
	const char*			root_name;
	const char*			item_name;
	ResourceDirectory*	resource_directory;

	DataArray();

	/// Generate a unique id for each item in array.
	void GenerateIds();

	void SetResourceDirectory( ResourceDirectory* resourceDirectory )
	{
		resource_directory = resourceDirectory;
	}

	void SetNodeNames( const char* root, const char* item )
	{
		root_name = root;
		item_name = item;
	}

	void SetFilename( const fc::string& name )
	{
		filename = name;
	}

	NO_INLINE bool SerializeXml( const fc::string& filename = "" );
	NO_INLINE bool DeserializeXml( const fc::string& filename = "" );
};



class DatabaseArrayAnyProxyBase
{
public:
	virtual ~DatabaseArrayAnyProxyBase() {}

	virtual void Clear() = 0;
	virtual void GenerateIds() = 0;
	virtual void SetResourceDirectory( ResourceDirectory* resourceDirectory ) = 0;
	virtual void SetDefaultNodeNames() = 0;
	virtual bool SerializeXml( const fc::string& filename = "" ) = 0;
	virtual bool DeserializeXml( const fc::string& filename = "" ) = 0;
};


template<class T>
class DatabaseArrayAnyProxyType : public DatabaseArrayAnyProxyBase
{
public:
	DatabaseArrayAnyProxyType( T* ptr ) : p(ptr)
	{}

	void Clear() { p->clear(); }
	void GenerateIds() { p->GenerateIds(); }
	void SetResourceDirectory( ResourceDirectory* resourceDirectory ) { p->SetResourceDirectory(resourceDirectory); }
	void SetDefaultNodeNames()
	{
		T temp;
		p->SetNodeNames(temp.root_name, temp.item_name);
	}

	bool SerializeXml( const fc::string& filename = "" ) { return p->SerializeXml(filename); }
	bool DeserializeXml( const fc::string& filename = "" ) { return p->DeserializeXml(filename); }

private:
	T* p;
};


class DatabaseArrayAnyHolder
{
public:
	typedef fc::fixed_tiny_vector<DatabaseArrayAnyProxyBase*, 64>				vec_type;
	typedef fc::aligned_buffer<256, FC_ALIGNOF(DatabaseArrayAnyProxyBase*)>		buffer_type;

	DatabaseArrayAnyHolder() :
		m_bin(),
		m_buffer(),
		m_offset(0)
	{
	}

	template<class T> inline
	void Add( T& arr )
	{
		ASSERT(m_offset < 256);

		DatabaseArrayAnyProxyType<T>* p = new (&m_buffer + m_offset) DatabaseArrayAnyProxyType<T>(&arr);
		m_offset += sizeof(DatabaseArrayAnyProxyBase*);
		m_bin.push_back(p);
	}

	vec_type& GetVector() { return m_bin; }
	const vec_type& GetVector() const { return m_bin; }

private:
	vec_type		m_bin;
	buffer_type		m_buffer;
	size_t			m_offset;

};


