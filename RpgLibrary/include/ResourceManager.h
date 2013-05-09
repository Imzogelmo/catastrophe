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

#include "Resource.h"


class RPG_API ResourceManagerTypeBase
{
public:
	ResourceManagerTypeBase();
	virtual ~ResourceManagerTypeBase()
	{}

	ResourceDirectory* GetResourceDirectory() { return g_resourceDirectory; }
	ResourceCache* GetResourceCache() { return &m_resourceCache; }

	// destroys or removes a reference to a resource.
	void Unload( const fc::string& filename );
	void Unload( void* ptr );
	void Unload( int id );

	// called automatically by the destructor.
	void DeleteResources();

protected:
	friend class ResourceCache;

	// called when the resource will be deleted.
	virtual void DisposeResource( void* p ) = 0;

	void ReleaseResource( Resource* resource );
	void AddResource( void* p, const fc::string& filename, int* id = 0 );

	// calls to get will increase the resource reference count.
	void* InternalGetResource( const fc::string& filename, int* id = 0 );
	void* InternalGetResource( int id );

	ResourceCache	m_resourceCache;

private:
	//this cannot be allowed to share resources.
	ResourceManagerTypeBase( const ResourceManagerTypeBase& );
	ResourceManagerTypeBase& operator =( const ResourceManagerTypeBase& );
};



template <class T>
class ResourceManagerType : public ResourceManagerTypeBase
{
public:
	ResourceManagerType() {}
	virtual ~ResourceManagerType()
	{}

	//
	// Load and Get functions return null if the resource does not exist.
	// the id of the resource can optionally be aquired as well.
	// id's will be eventually be recycled by the resource cache 
	// after destroying the actual resource.
	//
	// Every call to Load or Get requires a call to Unload in
	// order to decrease the reference counter.
	//
	// example load function usage:
	// T* Load( const fc::string& filename, int* id = 0 )
	// {
	//     Resource* resource = GetResource(filename, id);
	//     if( resource )
	//         return (T*)resource->ptr;
	//
	//     // otherwise load the resource then add it to the cache.
	//     T* ptr = LoadFunction();
	//     AddResource(ptr, filename, id);
	//     return ptr;
	// }
	//


	// calls to get will increase the resource reference count.
	T* GetResource( const fc::string& filename, int* id = 0 ) { return (T*)InternalGetResource(filename, id); }
	T* GetResource( int id ) { return (T*)InternalGetResource(id); }

protected:
	// override this.
	virtual void DisposeResource( void* p ) = 0;

};



