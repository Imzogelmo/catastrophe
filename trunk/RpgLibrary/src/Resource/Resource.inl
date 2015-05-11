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


void ResourceCache::SetResourceUsage( u32 maxCapacity )
{
	m_resources.Reserve(maxCapacity);
	m_freeStore.Reserve(maxCapacity);
}


void ResourceCache::DeleteResources()
{
	for( vec_type::Iterator it = m_resources.begin(); it != m_resources.end(); ++it )
	{
		DeleteResource(it);
	}

	m_resources.Clear();
	m_freeStore.Clear();
}


void ResourceCache::DeleteResource( Resource* resource )
{
	if( resource && m_resources.IteratorIsValid(resource) )
	{
		//dont delete previously deleted resources.
		if( resource->ptr )
		{
			m_parent->DisposeResource(resource->ptr);
			*resource = Resource();
			m_freeStore.Add( u32(resource - m_resources.begin()) );
		}
	}
}


Resource* ResourceCache::GetResource( const String& name )
{
	if( name.Empty() )
		return 0;

	Resource* res = 0;
	for( vec_type::Iterator it = m_resources.begin(); it != m_resources.end(); ++it )
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
	for( vec_type::Iterator it = m_resources.begin(); it != m_resources.end(); ++it )
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
	if( (u32)id < m_resources.Size() )
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
	if( !m_freeStore.Empty() )
	{
		id = (int)m_freeStore.Back();
		m_resources[ m_freeStore.Back() ] = resource;
		m_freeStore.PopBack();
	}
	else
	{
		ASSERT(!m_resources.Full());

		id = (int)m_resources.Size();
		m_resources.Add(resource);
	}

	return id;
}


int ResourceCache::GetResourceId( Resource* resource ) const
{
	int id = -1;
	if( resource && m_resources.IteratorIsValid(resource) )
	{
		id = int(resource - m_resources.begin());
	}

	return id;
}

