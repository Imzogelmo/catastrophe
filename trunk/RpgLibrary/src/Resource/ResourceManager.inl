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

#include "ResourceManager.h"


ResourceManagerTypeBase::ResourceManagerTypeBase()
	: m_resourceCache()
{
}


void ResourceManagerTypeBase::DeleteResources()
{
	//releases all data and deletes all resources.
	m_resourceCache.DeleteResources();
}


void ResourceManagerTypeBase::Unload( const String& filename )
{
	ReleaseResource( m_resourceCache.GetResource(filename) );
}


void ResourceManagerTypeBase::Unload( void* p )
{
	ReleaseResource( m_resourceCache.GetResource(p) );
}


void ResourceManagerTypeBase::Unload( int id )
{
	ReleaseResource( m_resourceCache.GetResource(id) );
}


void ResourceManagerTypeBase::ReleaseResource( Resource* resource )
{
	if( resource )
	{
		resource->ReleaseRef();
		if( resource->GetRefCount() == 0 )
		{
			m_resourceCache.DeleteResource(resource);
		}
	}
}


void ResourceManagerTypeBase::AddResource( void* p, const String& filename, int* id )
{
	int resourceID = m_resourceCache.AddResource( Resource(p, filename) );
	if( id != 0 )
	{
		//the caller wants the resource id.
		*id = resourceID;
	}
}


void* ResourceManagerTypeBase::InternalGetResource( const String& filename, int* id )
{
	void* ptr = 0;
	Resource* resource = m_resourceCache.GetResource(filename);
	if( resource != 0 )
	{
		resource->AddRef();
		ptr = resource->ptr;

		if( id != 0 )
		{
			*id = m_resourceCache.GetResourceId(resource);
		}
	}

	return ptr;
}


void* ResourceManagerTypeBase::InternalGetResource( int id )
{
	void* ptr = 0;
	Resource* resource = m_resourceCache.GetResource(id);
	if( resource )
	{
		resource->AddRef();
		ptr = resource->ptr;
	}

	return ptr;
}












