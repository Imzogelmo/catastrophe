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

#include <fc/vector.h>
#include <fc/string.h>

#include "RpgCommon.h"
#include "ResourceDirectory.h"


class Resource
{
public:
	//we don't need a template type for simple pointers.
	typedef void* pointer;

	pointer			ptr;
	fc::string		name;

	Resource( pointer p = 0, const fc::string& filename = "" )
		: ptr(p), name(filename), m_ref_count(1)
	{}

	void AddRef()
	{
		++m_ref_count;
	}

	void ReleaseRef()
	{
		--m_ref_count;
	}

	int GetRefCount()
	{
		return m_ref_count;
	}

protected:
	int m_ref_count;
};


class RPG_API ResourceCache
{
public:
	typedef	fc::vector<Resource>	vec_type;
	typedef	fc::vector<size_t>		store_type;

	ResourceCache( ResourceManagerTypeBase* p );

	// since the needs of a resource cache can largely vary,
	// it is required to call this. 
	void SetResourceUsage( size_t maxCapacity );

	// this will invalidate all existing pointers to these resources.
	void DeleteResources();
	void DeleteResource( Resource* ptr );

	// these get functions have a linear time cost.
	Resource* GetResource( const fc::string& name );
	Resource* GetResource( const void* ptr );

	// fast lookup of resource.
	Resource* GetResource( int id );

	// returns the id of the newly added resource
	int AddResource( const Resource& resource );

	// returns the id of the resource
	int GetResourceId( Resource* resource ) const;

protected:
	ResourceManagerTypeBase* m_parent;
	vec_type	m_resources;
	store_type	m_free_store;

};
