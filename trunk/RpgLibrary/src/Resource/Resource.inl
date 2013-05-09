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

#include "Resource.h"
#include "ResourceManager.h"


ResourceCache::ResourceCache() 
	: m_parent(0)
{
}


ResourceCache::~ResourceCache()
{
	DeleteResources();
}


void ResourceCache::SetManager( ResourceManagerTypeBase* p )
{
	ASSERT(p != 0);
	m_parent = p;
}


void ResourceCache::SetResourceUsage( size_t maxCapacity )
{
	m_resources.reserve(maxCapacity);
	m_free_store.reserve(maxCapacity);
}


void ResourceCache::DeleteResources()
{
	for( vec_type::iterator it = m_resources.begin(); it != m_resources.end(); ++it )
	{
		DeleteResource(it);
	}

	m_resources.clear();
	m_free_store.clear();
}


void ResourceCache::DeleteResource( Resource* resource )
{
	if( resource && m_resources.iterator_is_valid(resource) )
	{
		//dont delete previously deleted resources.
		if( resource->ptr )
		{
			m_parent->DisposeResource(resource->ptr);
			*resource = Resource();
			m_free_store.push_back( size_t(resource - m_resources.begin()) );
		}
	}
}


Resource* ResourceCache::GetResource( const fc::string& name )
{
	if( name.empty() )
		return 0;

	Resource* res = 0;
	for( vec_type::iterator it = m_resources.begin(); it != m_resources.end(); ++it )
	{
		if( it->name == name )
		{
			res = &(*it);
			break;
		}
	}

	return res;
}


Resource* ResourceCache::GetResource( const void* ptr )
{
	if(!ptr)
		return 0;

	Resource* res = 0;
	for( vec_type::iterator it = m_resources.begin(); it != m_resources.end(); ++it )
	{
		if( it->ptr == ptr )
		{
			res = &(*it);
			break;
		}
	}

	return res;
}


Resource* ResourceCache::GetResource( int id )
{
	Resource* res = 0;
	if( (size_t)id < m_resources.size() )
	{
		res = &m_resources[id];
		if( !res->ptr )
			res = 0;
	}

	return res;
}


int ResourceCache::AddResource( const Resource& resource )
{
	int id = -1;
	if( !m_free_store.empty() )
	{
		id = (int)m_free_store.back();
		m_resources[ m_free_store.back() ] = resource;
		m_free_store.pop_back();
	}
	else
	{
		ASSERT(!m_resources.full());

		id = (int)m_resources.size();
		m_resources.push_back(resource);
	}

	return id;
}


int ResourceCache::GetResourceId( Resource* resource ) const
{
	int id = -1;
	if( resource && m_resources.iterator_is_valid(resource) )
	{
		id = int(resource - m_resources.begin());
	}

	return id;
}

